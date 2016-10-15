#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../os_app_hooks.c ../../BSP/bsp.c ../../BSP/bsp_a.S ../../BSP/crt0.S ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c ../../../../../../../uC-CPU/cpu_core.c ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c ../../../../../../../uC-LIB/lib_ascii.c ../../../../../../../uC-LIB/lib_str.c ../../../../../../../uC-LIB/lib_math.c ../../../../../../../uC-LIB/lib_mem.c ../../../../../../../uCOS-III/Source/os_cfg_app.c ../../../../../../../uCOS-III/Source/os_core.c ../../../../../../../uCOS-III/Source/os_dbg.c ../../../../../../../uCOS-III/Source/os_flag.c ../../../../../../../uCOS-III/Source/os_int.c ../../../../../../../uCOS-III/Source/os_mem.c ../../../../../../../uCOS-III/Source/os_msg.c ../../../../../../../uCOS-III/Source/os_mutex.c ../../../../../../../uCOS-III/Source/os_pend_multi.c ../../../../../../../uCOS-III/Source/os_prio.c ../../../../../../../uCOS-III/Source/os_q.c ../../../../../../../uCOS-III/Source/os_sem.c ../../../../../../../uCOS-III/Source/os_stat.c ../../../../../../../uCOS-III/Source/os_task.c ../../../../../../../uCOS-III/Source/os_tick.c ../../../../../../../uCOS-III/Source/os_time.c ../../../../../../../uCOS-III/Source/os_tmr.c ../../../../../../../uCOS-III/Source/os_var.c ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c ../../../../../../../CPU/Microchip/PIC32/UART1.c ../appFeltonSpicer6.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/os_app_hooks.o ${OBJECTDIR}/_ext/1445226623/bsp.o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ${OBJECTDIR}/_ext/1445226623/crt0.o ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o ${OBJECTDIR}/_ext/1742735352/cpu_core.o ${OBJECTDIR}/_ext/1967989920/cpu_a.o ${OBJECTDIR}/_ext/1967989920/cpu_c.o ${OBJECTDIR}/_ext/1742743765/lib_ascii.o ${OBJECTDIR}/_ext/1742743765/lib_str.o ${OBJECTDIR}/_ext/1742743765/lib_math.o ${OBJECTDIR}/_ext/1742743765/lib_mem.o ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o ${OBJECTDIR}/_ext/1474524083/os_core.o ${OBJECTDIR}/_ext/1474524083/os_dbg.o ${OBJECTDIR}/_ext/1474524083/os_flag.o ${OBJECTDIR}/_ext/1474524083/os_int.o ${OBJECTDIR}/_ext/1474524083/os_mem.o ${OBJECTDIR}/_ext/1474524083/os_msg.o ${OBJECTDIR}/_ext/1474524083/os_mutex.o ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o ${OBJECTDIR}/_ext/1474524083/os_prio.o ${OBJECTDIR}/_ext/1474524083/os_q.o ${OBJECTDIR}/_ext/1474524083/os_sem.o ${OBJECTDIR}/_ext/1474524083/os_stat.o ${OBJECTDIR}/_ext/1474524083/os_task.o ${OBJECTDIR}/_ext/1474524083/os_tick.o ${OBJECTDIR}/_ext/1474524083/os_time.o ${OBJECTDIR}/_ext/1474524083/os_tmr.o ${OBJECTDIR}/_ext/1474524083/os_var.o ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o ${OBJECTDIR}/_ext/1468133644/UART1.o ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/os_app_hooks.o.d ${OBJECTDIR}/_ext/1445226623/bsp.o.d ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d ${OBJECTDIR}/_ext/1445226623/crt0.o.d ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d ${OBJECTDIR}/_ext/1742735352/cpu_core.o.d ${OBJECTDIR}/_ext/1967989920/cpu_a.o.d ${OBJECTDIR}/_ext/1967989920/cpu_c.o.d ${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d ${OBJECTDIR}/_ext/1742743765/lib_str.o.d ${OBJECTDIR}/_ext/1742743765/lib_math.o.d ${OBJECTDIR}/_ext/1742743765/lib_mem.o.d ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d ${OBJECTDIR}/_ext/1474524083/os_core.o.d ${OBJECTDIR}/_ext/1474524083/os_dbg.o.d ${OBJECTDIR}/_ext/1474524083/os_flag.o.d ${OBJECTDIR}/_ext/1474524083/os_int.o.d ${OBJECTDIR}/_ext/1474524083/os_mem.o.d ${OBJECTDIR}/_ext/1474524083/os_msg.o.d ${OBJECTDIR}/_ext/1474524083/os_mutex.o.d ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d ${OBJECTDIR}/_ext/1474524083/os_prio.o.d ${OBJECTDIR}/_ext/1474524083/os_q.o.d ${OBJECTDIR}/_ext/1474524083/os_sem.o.d ${OBJECTDIR}/_ext/1474524083/os_stat.o.d ${OBJECTDIR}/_ext/1474524083/os_task.o.d ${OBJECTDIR}/_ext/1474524083/os_tick.o.d ${OBJECTDIR}/_ext/1474524083/os_time.o.d ${OBJECTDIR}/_ext/1474524083/os_tmr.o.d ${OBJECTDIR}/_ext/1474524083/os_var.o.d ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d ${OBJECTDIR}/_ext/1468133644/UART1.o.d ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/os_app_hooks.o ${OBJECTDIR}/_ext/1445226623/bsp.o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ${OBJECTDIR}/_ext/1445226623/crt0.o ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o ${OBJECTDIR}/_ext/1742735352/cpu_core.o ${OBJECTDIR}/_ext/1967989920/cpu_a.o ${OBJECTDIR}/_ext/1967989920/cpu_c.o ${OBJECTDIR}/_ext/1742743765/lib_ascii.o ${OBJECTDIR}/_ext/1742743765/lib_str.o ${OBJECTDIR}/_ext/1742743765/lib_math.o ${OBJECTDIR}/_ext/1742743765/lib_mem.o ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o ${OBJECTDIR}/_ext/1474524083/os_core.o ${OBJECTDIR}/_ext/1474524083/os_dbg.o ${OBJECTDIR}/_ext/1474524083/os_flag.o ${OBJECTDIR}/_ext/1474524083/os_int.o ${OBJECTDIR}/_ext/1474524083/os_mem.o ${OBJECTDIR}/_ext/1474524083/os_msg.o ${OBJECTDIR}/_ext/1474524083/os_mutex.o ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o ${OBJECTDIR}/_ext/1474524083/os_prio.o ${OBJECTDIR}/_ext/1474524083/os_q.o ${OBJECTDIR}/_ext/1474524083/os_sem.o ${OBJECTDIR}/_ext/1474524083/os_stat.o ${OBJECTDIR}/_ext/1474524083/os_task.o ${OBJECTDIR}/_ext/1474524083/os_tick.o ${OBJECTDIR}/_ext/1474524083/os_time.o ${OBJECTDIR}/_ext/1474524083/os_tmr.o ${OBJECTDIR}/_ext/1474524083/os_var.o ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o ${OBJECTDIR}/_ext/1468133644/UART1.o ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o

# Source Files
SOURCEFILES=../os_app_hooks.c ../../BSP/bsp.c ../../BSP/bsp_a.S ../../BSP/crt0.S ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c ../../../../../../../uC-CPU/cpu_core.c ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c ../../../../../../../uC-LIB/lib_ascii.c ../../../../../../../uC-LIB/lib_str.c ../../../../../../../uC-LIB/lib_math.c ../../../../../../../uC-LIB/lib_mem.c ../../../../../../../uCOS-III/Source/os_cfg_app.c ../../../../../../../uCOS-III/Source/os_core.c ../../../../../../../uCOS-III/Source/os_dbg.c ../../../../../../../uCOS-III/Source/os_flag.c ../../../../../../../uCOS-III/Source/os_int.c ../../../../../../../uCOS-III/Source/os_mem.c ../../../../../../../uCOS-III/Source/os_msg.c ../../../../../../../uCOS-III/Source/os_mutex.c ../../../../../../../uCOS-III/Source/os_pend_multi.c ../../../../../../../uCOS-III/Source/os_prio.c ../../../../../../../uCOS-III/Source/os_q.c ../../../../../../../uCOS-III/Source/os_sem.c ../../../../../../../uCOS-III/Source/os_stat.c ../../../../../../../uCOS-III/Source/os_task.c ../../../../../../../uCOS-III/Source/os_tick.c ../../../../../../../uCOS-III/Source/os_time.c ../../../../../../../uCOS-III/Source/os_tmr.c ../../../../../../../uCOS-III/Source/os_var.c ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c ../../../../../../../CPU/Microchip/PIC32/UART1.c ../appFeltonSpicer6.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1967989920/cpu_a.o: ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1967989920 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_a.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1967989920/cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG   -c -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/1967989920/cpu_a.o ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--gdwarf-2,-MD="${OBJECTDIR}/_ext/1967989920/cpu_a.o.d"
else
${OBJECTDIR}/_ext/1967989920/cpu_a.o: ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1967989920 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_a.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1967989920/cpu_a.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${OBJECTDIR}/_ext/1967989920/cpu_a.o ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_a.s  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),--gdwarf-2,-MD="${OBJECTDIR}/_ext/1967989920/cpu_a.o.d"
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1445226623/bsp_a.o: ../../BSP/bsp_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.ok ${OBJECTDIR}/_ext/1445226623/bsp_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d" "${OBJECTDIR}/_ext/1445226623/bsp_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d"  -o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ../../BSP/bsp_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1445226623/bsp_a.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
${OBJECTDIR}/_ext/1445226623/crt0.o: ../../BSP/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o.ok ${OBJECTDIR}/_ext/1445226623/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/crt0.o.d" "${OBJECTDIR}/_ext/1445226623/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/crt0.o.d"  -o ${OBJECTDIR}/_ext/1445226623/crt0.o ../../BSP/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1445226623/crt0.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
${OBJECTDIR}/_ext/1179361761/os_cpu_a.o: ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179361761 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.ok ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d" "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d"  -o ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.asm.d",--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1
	
else
${OBJECTDIR}/_ext/1445226623/bsp_a.o: ../../BSP/bsp_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp_a.o.ok ${OBJECTDIR}/_ext/1445226623/bsp_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d" "${OBJECTDIR}/_ext/1445226623/bsp_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp_a.o.d"  -o ${OBJECTDIR}/_ext/1445226623/bsp_a.o ../../BSP/bsp_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1445226623/bsp_a.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1445226623/crt0.o: ../../BSP/crt0.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o 
	@${RM} ${OBJECTDIR}/_ext/1445226623/crt0.o.ok ${OBJECTDIR}/_ext/1445226623/crt0.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/crt0.o.d" "${OBJECTDIR}/_ext/1445226623/crt0.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1445226623/crt0.o.d"  -o ${OBJECTDIR}/_ext/1445226623/crt0.o ../../BSP/crt0.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1445226623/crt0.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/_ext/1179361761/os_cpu_a.o: ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179361761 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.ok ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d" "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.d"  -o ${OBJECTDIR}/_ext/1179361761/os_cpu_a.o ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_a.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/1179361761/os_cpu_a.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/os_app_hooks.o: ../os_app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/os_app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/os_app_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/os_app_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/os_app_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/os_app_hooks.o ../os_app_hooks.c   
	
${OBJECTDIR}/_ext/1445226623/bsp.o: ../../BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp.o.d" -o ${OBJECTDIR}/_ext/1445226623/bsp.o ../../BSP/bsp.c   
	
${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o: ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1468133644 
	@${RM} ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d" -o ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c   
	
${OBJECTDIR}/_ext/1742735352/cpu_core.o: ../../../../../../../uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742735352 
	@${RM} ${OBJECTDIR}/_ext/1742735352/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742735352/cpu_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742735352/cpu_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742735352/cpu_core.o.d" -o ${OBJECTDIR}/_ext/1742735352/cpu_core.o ../../../../../../../uC-CPU/cpu_core.c   
	
${OBJECTDIR}/_ext/1967989920/cpu_c.o: ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1967989920 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1967989920/cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1967989920/cpu_c.o.d" -o ${OBJECTDIR}/_ext/1967989920/cpu_c.o ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c   
	
${OBJECTDIR}/_ext/1742743765/lib_ascii.o: ../../../../../../../uC-LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_ascii.o ../../../../../../../uC-LIB/lib_ascii.c   
	
${OBJECTDIR}/_ext/1742743765/lib_str.o: ../../../../../../../uC-LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_str.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_str.o ../../../../../../../uC-LIB/lib_str.c   
	
${OBJECTDIR}/_ext/1742743765/lib_math.o: ../../../../../../../uC-LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_math.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_math.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_math.o ../../../../../../../uC-LIB/lib_math.c   
	
${OBJECTDIR}/_ext/1742743765/lib_mem.o: ../../../../../../../uC-LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_mem.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_mem.o ../../../../../../../uC-LIB/lib_mem.c   
	
${OBJECTDIR}/_ext/1474524083/os_cfg_app.o: ../../../../../../../uCOS-III/Source/os_cfg_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o ../../../../../../../uCOS-III/Source/os_cfg_app.c   
	
${OBJECTDIR}/_ext/1474524083/os_core.o: ../../../../../../../uCOS-III/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_core.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_core.o ../../../../../../../uCOS-III/Source/os_core.c   
	
${OBJECTDIR}/_ext/1474524083/os_dbg.o: ../../../../../../../uCOS-III/Source/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_dbg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_dbg.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_dbg.o ../../../../../../../uCOS-III/Source/os_dbg.c   
	
${OBJECTDIR}/_ext/1474524083/os_flag.o: ../../../../../../../uCOS-III/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_flag.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_flag.o ../../../../../../../uCOS-III/Source/os_flag.c   
	
${OBJECTDIR}/_ext/1474524083/os_int.o: ../../../../../../../uCOS-III/Source/os_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_int.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_int.o ../../../../../../../uCOS-III/Source/os_int.c   
	
${OBJECTDIR}/_ext/1474524083/os_mem.o: ../../../../../../../uCOS-III/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_mem.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_mem.o ../../../../../../../uCOS-III/Source/os_mem.c   
	
${OBJECTDIR}/_ext/1474524083/os_msg.o: ../../../../../../../uCOS-III/Source/os_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_msg.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_msg.o ../../../../../../../uCOS-III/Source/os_msg.c   
	
${OBJECTDIR}/_ext/1474524083/os_mutex.o: ../../../../../../../uCOS-III/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_mutex.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_mutex.o ../../../../../../../uCOS-III/Source/os_mutex.c   
	
${OBJECTDIR}/_ext/1474524083/os_pend_multi.o: ../../../../../../../uCOS-III/Source/os_pend_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o ../../../../../../../uCOS-III/Source/os_pend_multi.c   
	
${OBJECTDIR}/_ext/1474524083/os_prio.o: ../../../../../../../uCOS-III/Source/os_prio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_prio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_prio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_prio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_prio.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_prio.o ../../../../../../../uCOS-III/Source/os_prio.c   
	
${OBJECTDIR}/_ext/1474524083/os_q.o: ../../../../../../../uCOS-III/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_q.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_q.o ../../../../../../../uCOS-III/Source/os_q.c   
	
${OBJECTDIR}/_ext/1474524083/os_sem.o: ../../../../../../../uCOS-III/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_sem.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_sem.o ../../../../../../../uCOS-III/Source/os_sem.c   
	
${OBJECTDIR}/_ext/1474524083/os_stat.o: ../../../../../../../uCOS-III/Source/os_stat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_stat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_stat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_stat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_stat.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_stat.o ../../../../../../../uCOS-III/Source/os_stat.c   
	
${OBJECTDIR}/_ext/1474524083/os_task.o: ../../../../../../../uCOS-III/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_task.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_task.o ../../../../../../../uCOS-III/Source/os_task.c   
	
${OBJECTDIR}/_ext/1474524083/os_tick.o: ../../../../../../../uCOS-III/Source/os_tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_tick.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_tick.o ../../../../../../../uCOS-III/Source/os_tick.c   
	
${OBJECTDIR}/_ext/1474524083/os_time.o: ../../../../../../../uCOS-III/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_time.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_time.o ../../../../../../../uCOS-III/Source/os_time.c   
	
${OBJECTDIR}/_ext/1474524083/os_tmr.o: ../../../../../../../uCOS-III/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_tmr.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_tmr.o ../../../../../../../uCOS-III/Source/os_tmr.c   
	
${OBJECTDIR}/_ext/1474524083/os_var.o: ../../../../../../../uCOS-III/Source/os_var.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_var.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_var.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_var.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_var.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_var.o ../../../../../../../uCOS-III/Source/os_var.c   
	
${OBJECTDIR}/_ext/1179361761/os_cpu_c.o: ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179361761 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c   
	
${OBJECTDIR}/_ext/1468133644/UART1.o: ../../../../../../../CPU/Microchip/PIC32/UART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1468133644 
	@${RM} ${OBJECTDIR}/_ext/1468133644/UART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1468133644/UART1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1468133644/UART1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1468133644/UART1.o.d" -o ${OBJECTDIR}/_ext/1468133644/UART1.o ../../../../../../../CPU/Microchip/PIC32/UART1.c   
	
${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o: ../appFeltonSpicer6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d" -o ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o ../appFeltonSpicer6.c   
	
else
${OBJECTDIR}/_ext/1472/os_app_hooks.o: ../os_app_hooks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/os_app_hooks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/os_app_hooks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/os_app_hooks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/os_app_hooks.o.d" -o ${OBJECTDIR}/_ext/1472/os_app_hooks.o ../os_app_hooks.c   
	
${OBJECTDIR}/_ext/1445226623/bsp.o: ../../BSP/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1445226623 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445226623/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1445226623/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1445226623/bsp.o.d" -o ${OBJECTDIR}/_ext/1445226623/bsp.o ../../BSP/bsp.c   
	
${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o: ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1468133644 
	@${RM} ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o.d" -o ${OBJECTDIR}/_ext/1468133644/PIC32INTlib.o ../../../../../../../CPU/Microchip/PIC32/PIC32INTlib.c   
	
${OBJECTDIR}/_ext/1742735352/cpu_core.o: ../../../../../../../uC-CPU/cpu_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742735352 
	@${RM} ${OBJECTDIR}/_ext/1742735352/cpu_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742735352/cpu_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742735352/cpu_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742735352/cpu_core.o.d" -o ${OBJECTDIR}/_ext/1742735352/cpu_core.o ../../../../../../../uC-CPU/cpu_core.c   
	
${OBJECTDIR}/_ext/1967989920/cpu_c.o: ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1967989920 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1967989920/cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1967989920/cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1967989920/cpu_c.o.d" -o ${OBJECTDIR}/_ext/1967989920/cpu_c.o ../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC/cpu_c.c   
	
${OBJECTDIR}/_ext/1742743765/lib_ascii.o: ../../../../../../../uC-LIB/lib_ascii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_ascii.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_ascii.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_ascii.o ../../../../../../../uC-LIB/lib_ascii.c   
	
${OBJECTDIR}/_ext/1742743765/lib_str.o: ../../../../../../../uC-LIB/lib_str.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_str.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_str.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_str.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_str.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_str.o ../../../../../../../uC-LIB/lib_str.c   
	
${OBJECTDIR}/_ext/1742743765/lib_math.o: ../../../../../../../uC-LIB/lib_math.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_math.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_math.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_math.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_math.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_math.o ../../../../../../../uC-LIB/lib_math.c   
	
${OBJECTDIR}/_ext/1742743765/lib_mem.o: ../../../../../../../uC-LIB/lib_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1742743765 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1742743765/lib_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1742743765/lib_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1742743765/lib_mem.o.d" -o ${OBJECTDIR}/_ext/1742743765/lib_mem.o ../../../../../../../uC-LIB/lib_mem.c   
	
${OBJECTDIR}/_ext/1474524083/os_cfg_app.o: ../../../../../../../uCOS-III/Source/os_cfg_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_cfg_app.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_cfg_app.o ../../../../../../../uCOS-III/Source/os_cfg_app.c   
	
${OBJECTDIR}/_ext/1474524083/os_core.o: ../../../../../../../uCOS-III/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_core.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_core.o ../../../../../../../uCOS-III/Source/os_core.c   
	
${OBJECTDIR}/_ext/1474524083/os_dbg.o: ../../../../../../../uCOS-III/Source/os_dbg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_dbg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_dbg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_dbg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_dbg.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_dbg.o ../../../../../../../uCOS-III/Source/os_dbg.c   
	
${OBJECTDIR}/_ext/1474524083/os_flag.o: ../../../../../../../uCOS-III/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_flag.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_flag.o ../../../../../../../uCOS-III/Source/os_flag.c   
	
${OBJECTDIR}/_ext/1474524083/os_int.o: ../../../../../../../uCOS-III/Source/os_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_int.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_int.o ../../../../../../../uCOS-III/Source/os_int.c   
	
${OBJECTDIR}/_ext/1474524083/os_mem.o: ../../../../../../../uCOS-III/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_mem.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_mem.o ../../../../../../../uCOS-III/Source/os_mem.c   
	
${OBJECTDIR}/_ext/1474524083/os_msg.o: ../../../../../../../uCOS-III/Source/os_msg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_msg.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_msg.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_msg.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_msg.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_msg.o ../../../../../../../uCOS-III/Source/os_msg.c   
	
${OBJECTDIR}/_ext/1474524083/os_mutex.o: ../../../../../../../uCOS-III/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_mutex.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_mutex.o ../../../../../../../uCOS-III/Source/os_mutex.c   
	
${OBJECTDIR}/_ext/1474524083/os_pend_multi.o: ../../../../../../../uCOS-III/Source/os_pend_multi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_pend_multi.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_pend_multi.o ../../../../../../../uCOS-III/Source/os_pend_multi.c   
	
${OBJECTDIR}/_ext/1474524083/os_prio.o: ../../../../../../../uCOS-III/Source/os_prio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_prio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_prio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_prio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_prio.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_prio.o ../../../../../../../uCOS-III/Source/os_prio.c   
	
${OBJECTDIR}/_ext/1474524083/os_q.o: ../../../../../../../uCOS-III/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_q.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_q.o ../../../../../../../uCOS-III/Source/os_q.c   
	
${OBJECTDIR}/_ext/1474524083/os_sem.o: ../../../../../../../uCOS-III/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_sem.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_sem.o ../../../../../../../uCOS-III/Source/os_sem.c   
	
${OBJECTDIR}/_ext/1474524083/os_stat.o: ../../../../../../../uCOS-III/Source/os_stat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_stat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_stat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_stat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_stat.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_stat.o ../../../../../../../uCOS-III/Source/os_stat.c   
	
${OBJECTDIR}/_ext/1474524083/os_task.o: ../../../../../../../uCOS-III/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_task.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_task.o ../../../../../../../uCOS-III/Source/os_task.c   
	
${OBJECTDIR}/_ext/1474524083/os_tick.o: ../../../../../../../uCOS-III/Source/os_tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_tick.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_tick.o ../../../../../../../uCOS-III/Source/os_tick.c   
	
${OBJECTDIR}/_ext/1474524083/os_time.o: ../../../../../../../uCOS-III/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_time.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_time.o ../../../../../../../uCOS-III/Source/os_time.c   
	
${OBJECTDIR}/_ext/1474524083/os_tmr.o: ../../../../../../../uCOS-III/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_tmr.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_tmr.o ../../../../../../../uCOS-III/Source/os_tmr.c   
	
${OBJECTDIR}/_ext/1474524083/os_var.o: ../../../../../../../uCOS-III/Source/os_var.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1474524083 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_var.o.d 
	@${RM} ${OBJECTDIR}/_ext/1474524083/os_var.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1474524083/os_var.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1474524083/os_var.o.d" -o ${OBJECTDIR}/_ext/1474524083/os_var.o ../../../../../../../uCOS-III/Source/os_var.c   
	
${OBJECTDIR}/_ext/1179361761/os_cpu_c.o: ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1179361761 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1179361761/os_cpu_c.o.d" -o ${OBJECTDIR}/_ext/1179361761/os_cpu_c.o ../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC/os_cpu_c.c   
	
${OBJECTDIR}/_ext/1468133644/UART1.o: ../../../../../../../CPU/Microchip/PIC32/UART1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1468133644 
	@${RM} ${OBJECTDIR}/_ext/1468133644/UART1.o.d 
	@${RM} ${OBJECTDIR}/_ext/1468133644/UART1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1468133644/UART1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1468133644/UART1.o.d" -o ${OBJECTDIR}/_ext/1468133644/UART1.o ../../../../../../../CPU/Microchip/PIC32/UART1.c   
	
${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o: ../appFeltonSpicer6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"../../../../../../../uCOS-III/Source" -I"../../../../../../../uCOS-III/Ports/MIPS32-4K/Vectored-Interrupt/MPLAB-PIC32-GCC" -I"../../../../../../../uC-CPU" -I"../../../../../../../uC-LIB" -I"../../../../../../../uC-CPU/MIPS32-4K/MPLAB-PIC32-GCC" -I"../../../../../../../CPU/Microchip/PIC32" -I"../../BSP" -I"../" -MMD -MF "${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o.d" -o ${OBJECTDIR}/_ext/1472/appFeltonSpicer6.o ../appFeltonSpicer6.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-Map="MapFile"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -nostartfiles -o dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="MapFile"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Lab4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
