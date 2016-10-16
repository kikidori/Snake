/**************************************************************************
* File:		PONG.c
* Date:		September 12, 2013
* Status:       Some bugs remaining but generally functions.
* Processor:	PIC32MX320F128H
* Toolchain:	MPLAB-X
* Board:	UNO32 from Digilent
* Programmer:	M.J. Batchelder
* Organization:	CENG 448/548, SDSMT
* RTOS:		uCOS-III from Micrium
*
* Description:	PONG game using TeraTerm or PuTTY as VT100 terminal for diaplay
*		Left and right players have up and down buttons as input
*               VT100 control codes move the cursor to position the paddles
*		and ball.  Each side has a score advanced when the ball hits
*		the opposite wall.
* Tasks:	Ball task, Left Paddle Task, Right Paddle Task, 
*               Start task with Blink LED Task, idle task, timer task,
*               Otional tasks enabled in os_cfg.h: statistics task, stack check task
*		
*
* Notes on VT100 emulation
* 	Clear Screen:	esc c			0x1B 0x63
*	Move Cursor:	esc [ row ; col H	0x1B 0x3B rr 0x1B cc 0x28
*        for example: 	move to row 12 col 13 -- rr = 0x31 0x32, cc = 0x31 0x33
*			move to row 2 col 3 -- rr = 0x30 0x32 or rr = 0x32
*                                              cc = 0x30 0x33 or cc = 0x33
* Note: baud rate is set in UART1.h
**************************************************************************/
#include <includes.h>

/*
*********************************************************************************************************
*                                                Task Stacks/TCB
*********************************************************************************************************
*/

#define TASK_STK_SIZE 256 

#define APP_CFG_TASK_BALL_STK_SIZE TASK_STK_SIZE
#define APP_CFG_TASK_FOOD_STK_SIZE TASK_STK_SIZE

#define APP_CFG_TASK_BALL_STK_SIZE_LIMIT TASK_STK_SIZE-32
#define APP_CFG_TASK_FOOD_STK_SIZE_LIMIT TASK_STK_SIZE-32

static  OS_TCB    App_TaskStartTCB;
static  CPU_STK   App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];

static  OS_TCB    App_TaskBallTCB;
static  CPU_STK   App_TaskBallStk[APP_CFG_TASK_BALL_STK_SIZE];

static  OS_TCB    App_TaskFoodTCB;
static  CPU_STK   App_TaskFoodStk[APP_CFG_TASK_FOOD_STK_SIZE];

/*
*********************************************************************************************************
*                                            Task PROTOTYPES
*********************************************************************************************************
*/

static  void        App_TaskStart(void *p_arg);
static  void        AppTaskCreate(void);

static void         App_TaskBall (void *data);
static void         App_TaskFood (void *data);
/*
*********************************************************************************************************
*                                            Pong Task Priorities
*********************************************************************************************************
*/

#define APP_CFG_TASK_BALL_PRIO 4
#define APP_CFG_TASK_FOOD_PRIO 5

// *********************************************************************
// GPIO defines     Switches on Digilent Basic Shield for UNO32
// *********************************************************************
#define RIGHT_UP_SW	_RF1    // Port F bit 1 switch
#define RIGHT_DOWN_SW   _RD5    // Port D bit 5 switch
#define LEFT_UP_SW	_RD6    // Port D bit 6 switch
#define LEFT_DOWN_SW	_RD7    // Port D bit 7 switch


// *********************************************************************
// Screen defines and function prototypes
// *********************************************************************
#define SCREEN_X_START      1
#define SCREEN_X_END        80
#define SCREEN_Y_START      1
#define SCREEN_Y_END        25

#define BALL_X_START	    ((SCREEN_X_END - SCREEN_X_START)/2)
#define BALL_Y_START	    ((SCREEN_Y_END - SCREEN_Y_START)/2)

void Screen_Init(void);
void Screen_Clear (void);
void Screen_MoveCursor (int Xpos, int Ypos);
int Screen_WriteChar(int x, int y, char c);
int Screen_WriteNumber(int x, int y, int number);
void Screen_OffCursor (void);
void Screen_OnCursor (void);

// ********************************************************************* */
// Global Variables
// *********************************************************************
int x_delta, y_delta, size = 1, food_x, food_y, need_food = 1;
int snake_x[SCREEN_X_END*SCREEN_Y_END];
int snake_y[SCREEN_X_END*SCREEN_Y_END];
int map[SCREEN_X_END][SCREEN_Y_END];

/*
 *********************************************************************************************************
 *                                                main()
 *
 * Description : This is the standard entry point for C code.
 *
 * Arguments   : none
 *********************************************************************************************************
 */

int main(void) {

    OS_ERR os_err;

    CPU_Init(); /* Initialize the uC/CPU services  */

    BSP_IntDisAll();

    OSInit(&os_err); /* Init uC/OS-III.                  */

    // app_cfg.h holds priority, stack size, and limit for start task
    OSTaskCreate((OS_TCB *) & App_TaskStartTCB, /* Create the start task            */
            (CPU_CHAR *) "Start",
            (OS_TASK_PTR) App_TaskStart,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_START_PRIO,
            (CPU_STK *) & App_TaskStartStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_START_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    OSStart(&os_err); /* Start multitasking (i.e. give control to uC/OS-III). */
    /* Should not return here as RTOS takes control */
    (void) &os_err;

    return (0);
}

/*$PAGE*/

/*
 *********************************************************************************************************
 *                                          STARTUP TASK
 *
 * Description : This is an example of a startup task.  
 * Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
 *********************************************************************************************************
 */

static void App_TaskStart(void *p_arg) {
#if CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL // maybe not needed for uCOS-III
    CPU_SR cpu_sr;
#endif
    CPU_INT08U i;
    CPU_INT08U j;

    (void) p_arg;
    OS_ERR err;

    BSP_InitIO(); /* Initialize BSP functions                                 */

#if OS_CFG_STAT_TASK_EN > 0  // Set in os_cfg.h
    OSStatTaskCPUUsageInit(&err);
    if (err != OS_ERR_NONE) {
        putsU1("Error starting OSStatTaskCPUUsageInit ");
    }
#endif

    initU1(); // Initialize UART1

    AppTaskCreate(); /* Create application tasks                                 */

    // ----- Task continues executing as infinite loop -----------
    // ----- writing statistics to screen and blinking LEDs ------
    while (DEF_TRUE) { /* Task body, always written as an infinite loop.            */

// If enabled writes:  CPU usage, number of tasks, stack free, stack used
#if OS_CFG_STAT_TASK_EN > 0 // Set in os_cfg.h
        OSSchedLock(&err); // Don't let another task run as it might change cursor position
        Screen_MoveCursor(40, 2); // before  writing to the screen
        UART_PrintNum(OSStatTaskCPUUsage);
        Screen_MoveCursor(40, 3); // before  writing to the screen
        UART_PrintNum(OSTaskQty);
        Screen_MoveCursor(40, 4); // before  writing to the screen
        UART_PrintNum3(App_TaskStartTCB.StkFree);
        Screen_MoveCursor(40, 5); // before  writing to the screen
        UART_PrintNum3(App_TaskStartTCB.StkUsed);
        OSSchedUnlock(&err); // Ok for other tasks to run
#endif

        for (i = 1; i < 9; i++) {
            LED_Toggle(i);
            OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
        }

    }
}

/*$PAGE*/

/*
 ******************************************************************************
 *                                        CREATE APPLICATION TASKS
 *
 * Description: This function creates the application tasks.
 *
 * Arguments  : none.
 *
 * Note(s)    : none.
 ******************************************************************************
 */

static void AppTaskCreate(void) {

    OS_ERR os_err, err;
    unsigned char i;
    char key;

    Screen_Init();

    OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_HMSM_STRICT, &err); /* Wait two seconds */
    if (err != OS_ERR_NONE) {
        putsU1("Error OSTimeDlyHMSM ");
    }

    Screen_MoveCursor(8, 8);
    putsU1("uC/OS-III, The Real-Time Kernel PIC32 \n"
            " PONG\n");

    OSTimeDlyHMSM(0, 0, 2, 0, OS_OPT_TIME_HMSM_STRICT, &err); /* Wait two seconds */
    if (err != OS_ERR_NONE) {
        putsU1("Error OSTimeDlyHMSM ");
    }
    Screen_Init();
    Screen_OffCursor();

    OSTaskCreate((OS_TCB *) & App_TaskBallTCB, /* Create the ball task       */
            (CPU_CHAR *) "Ball",
            (OS_TASK_PTR) App_TaskBall,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_BALL_PRIO,
            (CPU_STK *) & App_TaskBallStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_BALL_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_BALL_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting Ball task: ");
    }
    OSTaskCreate((OS_TCB *) & App_TaskFoodTCB, /* Create the ball task       */
            (CPU_CHAR *) "Food",
            (OS_TASK_PTR) App_TaskFood,
            (void *) 0,
            (OS_PRIO) APP_CFG_TASK_FOOD_PRIO,
            (CPU_STK *) & App_TaskFoodStk[0],
            (CPU_STK_SIZE) APP_CFG_TASK_FOOD_STK_SIZE_LIMIT,
            (CPU_STK_SIZE) APP_CFG_TASK_FOOD_STK_SIZE,
            (OS_MSG_QTY) 0u,
            (OS_TICK) 0u,
            (void *) 0,
            (OS_OPT) (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
            (OS_ERR *) & os_err);

    if (os_err != OS_ERR_NONE) {
        putsU1("Error starting Food task: ");
    }

}


/*$PAGE*/


/* ********************************************************************* */
/* Local functions */
// *********************************************************************

// Prints a 2 digit base 10 number

void UART_PrintNum(int i) {
    putU1(i / 10u + '0');
    putU1(i % 10u + '0');
}

// Prints a 3 digit base 10 number

void UART_PrintNum3(int i) {
    putU1(i / 100u + '0');
    putU1((i % 100) / 10u + '0');
    putU1(((i % 100) % 10) + '0');
}

void Screen_Clear(void) {
    putU1(0x1B);
    putU1('c');
}

void Screen_OffCursor(void) // Does seem to work
{
    putU1(0x1B);
    putU1('[');
    putU1('?');
    putU1('2');
    putU1('5');
    putU1('l');
}

void Screen_OnCursor(void) {
    putU1(0x1B);
    putU1('[');
    putU1('?');
    putU1('2');
    putU1('5');
    putU1('h');
}

void Screen_MoveCursor(int Xpos, int Ypos) {
    putU1(0x1B);
    putU1('[');
    UART_PrintNum(Ypos);
    putU1(';');
    UART_PrintNum(Xpos);
    putU1('H');
}

int Screen_WriteChar(int x, int y, char c) {
    OS_ERR err;
    if ((x > SCREEN_X_END) || (x < SCREEN_X_START) ||
            (y > SCREEN_Y_END) || (y < SCREEN_Y_START)) {
        return 1; // Error
    }
    OSSchedLock(&err); // Don't let another task run as it might change cursor position
    Screen_MoveCursor(x, y); // before the character is written to the screen
    putU1(c);
    OSSchedUnlock(&err); // Ok for other tasks to run
}

int Screen_WriteNumber(int x, int y, int number) {
    OS_ERR err;
    if ((x > SCREEN_X_END) || (x < SCREEN_X_START) ||
            (y > SCREEN_Y_END) || (y < SCREEN_Y_START)) {
        return 1; // Error
    }
    OSSchedLock(&err); // Don't let another task run as it might change cursor position
    Screen_MoveCursor(x, y); // before writing the value to the screen
    UART_PrintNum(number);
    OSSchedUnlock(&err); // Ok for other tasks to run
}

void Screen_Init(void) {
    int i;
    Screen_OffCursor();
    Screen_Clear();
    Screen_OffCursor();
}



/* ********************************************************************* */
/* Application Tasks*/
// *********************************************************************

void App_TaskFood (void *data)
{
    int x, y;
    //int Ls, Rs, Left_Score = 0, Right_Score = 0;
    OS_ERR err;

    //Screen_WriteNumber(SCORE_LEFT_X_START, SCORE_Y, Left_Score);
    //Screen_WriteNumber(SCORE_RIGHT_X_START, SCORE_Y, Right_Score);
    while (DEF_TRUE) {
        OSTimeDlyHMSM(0, 0, 0, 75, OS_OPT_TIME_HMSM_STRICT, &err);
        if (need_food == 1)
        {
            x = rand()%SCREEN_X_END;
            y = rand()%SCREEN_Y_END;
            while (isOccupied(x, y) == 1)
            {
                x = rand()%SCREEN_X_END;;
                y = rand()%SCREEN_Y_END;
            }
            need_food = 0;
        }
    }
}

void App_TaskBall(void *data) {
    int x, y, x_tail, y_tail, count;
    x_delta = 1;
    y_delta = 0;
    //int Ls, Rs, Left_Score = 0, Right_Score = 0;
    OS_ERR err;

    //Screen_WriteNumber(SCORE_LEFT_X_START, SCORE_Y, Left_Score);
    //Screen_WriteNumber(SCORE_RIGHT_X_START, SCORE_Y, Right_Score);
    
    x = BALL_X_START;
    y = BALL_Y_START;
    Screen_WriteChar(x, y, '*');
    while (DEF_TRUE) {
        OSTimeDlyHMSM(0, 0, 0, 75, OS_OPT_TIME_HMSM_STRICT, &err); // Wait -- give another task a chance to run
         // Erase old position

        if (((x > SCREEN_X_END)) || ((x < SCREEN_X_START))) x_delta = 0; //Provides collisions should end game
        if ((y > SCREEN_Y_END) || (y < SCREEN_Y_START)) y_delta = 0; //Provides collisions should end game
        if (Ball_Up())
        {
            x_delta = 0;
            y_delta = 1;
        } else if (Ball_Down())
        {
            x_delta = 0;
            y_delta = -1;
        } else if (Ball_Right())
        {
            x_delta = -1;
            y_delta = 0;
        } else if (Ball_Left())
        {
            x_delta = 1;
            y_delta = 0;
        }

        x += x_delta; // Move to new position
        y += y_delta;
        map[x][y] = 1;
        if (x == food_x && y == food_y)
        {
            size++;
            Screen_WriteChar(x, y, '*');
            need_food = 1;
        } else if (isOccupied(x, y) == 1)
        {
            //end game ran into self
        }
        else if(size == 1)
        {
            Screen_WriteChar(snake_x[0], snake_y[0], ' ');
            map[snake_x[0]][snake_y[0]] = 0;
            snake_x[0] = x;
            snake_y[0] = y;
            Screen_WriteChar(x, y, '*');
        } else 
        {
            Screen_WriteChar(snake_x[size-1], snake_y[size-1], ' ');
            map[snake_x[size-1]][snake_y[size-1]] = 0;
            for (count = size-1; count > 0; count--)
            {
                snake_x[count] = snake_x[count-1];
                snake_y[count] = snake_y[count-1];
            }
            snake_x[0] = x;
            snake_y[0] = y;
            Screen_WriteChar(x, y, '*');
        }
        
    }
}

int Ball_Up() {
    if (RIGHT_UP_SW)
        return 1;
    else
        return 0;
}

int Ball_Down(void) {
    if (RIGHT_DOWN_SW)
        return 1;
    else
        return 0;
}

int Ball_Left() {
    if (LEFT_UP_SW)
        return 1;
    else
        return 0;
}

int Ball_Right() {
    if (LEFT_DOWN_SW)
        return 1;
    else
        return 0;
}

int isOccupied(int x, int y)
{
    if(map[x][y] == 1)
    {
        return 1;
    } else
    {
        return 0;
    }
}