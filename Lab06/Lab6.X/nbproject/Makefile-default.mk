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
FINAL_IMAGE=${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Ascii.c BOARD.c bounce_adc.c bounce_buttons.c bounce_ec.c bounce_switch.c bounce_timers.c ButtonsTest.c Oled.c OledDriver.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Ascii.o ${OBJECTDIR}/BOARD.o ${OBJECTDIR}/bounce_adc.o ${OBJECTDIR}/bounce_buttons.o ${OBJECTDIR}/bounce_ec.o ${OBJECTDIR}/bounce_switch.o ${OBJECTDIR}/bounce_timers.o ${OBJECTDIR}/ButtonsTest.o ${OBJECTDIR}/Oled.o ${OBJECTDIR}/OledDriver.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Ascii.o.d ${OBJECTDIR}/BOARD.o.d ${OBJECTDIR}/bounce_adc.o.d ${OBJECTDIR}/bounce_buttons.o.d ${OBJECTDIR}/bounce_ec.o.d ${OBJECTDIR}/bounce_switch.o.d ${OBJECTDIR}/bounce_timers.o.d ${OBJECTDIR}/ButtonsTest.o.d ${OBJECTDIR}/Oled.o.d ${OBJECTDIR}/OledDriver.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Ascii.o ${OBJECTDIR}/BOARD.o ${OBJECTDIR}/bounce_adc.o ${OBJECTDIR}/bounce_buttons.o ${OBJECTDIR}/bounce_ec.o ${OBJECTDIR}/bounce_switch.o ${OBJECTDIR}/bounce_timers.o ${OBJECTDIR}/ButtonsTest.o ${OBJECTDIR}/Oled.o ${OBJECTDIR}/OledDriver.o

# Source Files
SOURCEFILES=Ascii.c BOARD.c bounce_adc.c bounce_buttons.c bounce_ec.c bounce_switch.c bounce_timers.c ButtonsTest.c Oled.c OledDriver.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Ascii.o: Ascii.c  .generated_files/flags/default/a40202f2b2d7c345d477088fbf706ac36a45bbdd .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ascii.o.d 
	@${RM} ${OBJECTDIR}/Ascii.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Ascii.o.d" -o ${OBJECTDIR}/Ascii.o Ascii.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BOARD.o: BOARD.c  .generated_files/flags/default/5818ebc0ebcf63c11f5cf81dcae48206028feb3d .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BOARD.o.d 
	@${RM} ${OBJECTDIR}/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/BOARD.o.d" -o ${OBJECTDIR}/BOARD.o BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_adc.o: bounce_adc.c  .generated_files/flags/default/3084ef3254257a9fd6f27123dea25070ebb77e32 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_adc.o.d 
	@${RM} ${OBJECTDIR}/bounce_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_adc.o.d" -o ${OBJECTDIR}/bounce_adc.o bounce_adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_buttons.o: bounce_buttons.c  .generated_files/flags/default/a4c5a1642664f15492c4e158a15820d1bf4e9490 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_buttons.o.d 
	@${RM} ${OBJECTDIR}/bounce_buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_buttons.o.d" -o ${OBJECTDIR}/bounce_buttons.o bounce_buttons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_ec.o: bounce_ec.c  .generated_files/flags/default/60095df30dadc598cca183c0fadff6d0aa226846 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_ec.o.d 
	@${RM} ${OBJECTDIR}/bounce_ec.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_ec.o.d" -o ${OBJECTDIR}/bounce_ec.o bounce_ec.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_switch.o: bounce_switch.c  .generated_files/flags/default/9962bd44815d4e2bd414a1970c2cbcd4dab10fe6 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_switch.o.d 
	@${RM} ${OBJECTDIR}/bounce_switch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_switch.o.d" -o ${OBJECTDIR}/bounce_switch.o bounce_switch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_timers.o: bounce_timers.c  .generated_files/flags/default/9f08531c2d08140ef718b03d618f2c0704f07e55 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_timers.o.d 
	@${RM} ${OBJECTDIR}/bounce_timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_timers.o.d" -o ${OBJECTDIR}/bounce_timers.o bounce_timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ButtonsTest.o: ButtonsTest.c  .generated_files/flags/default/115b7b16d2186280fb30db0627062b12452582c8 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ButtonsTest.o.d 
	@${RM} ${OBJECTDIR}/ButtonsTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ButtonsTest.o.d" -o ${OBJECTDIR}/ButtonsTest.o ButtonsTest.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Oled.o: Oled.c  .generated_files/flags/default/c3e4c1b6dae8af2a70e472e3ad89edf2b0609377 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Oled.o.d 
	@${RM} ${OBJECTDIR}/Oled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Oled.o.d" -o ${OBJECTDIR}/Oled.o Oled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OledDriver.o: OledDriver.c  .generated_files/flags/default/93c40f40c81881f44dfa38844350b297d653a462 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/OledDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/OledDriver.o.d" -o ${OBJECTDIR}/OledDriver.o OledDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/Ascii.o: Ascii.c  .generated_files/flags/default/3959f3bfc75bb988cc316add9e2ddcef0e553af9 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Ascii.o.d 
	@${RM} ${OBJECTDIR}/Ascii.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Ascii.o.d" -o ${OBJECTDIR}/Ascii.o Ascii.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BOARD.o: BOARD.c  .generated_files/flags/default/74d282f4988caa8a3412e5212d546c5f6d984e74 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BOARD.o.d 
	@${RM} ${OBJECTDIR}/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/BOARD.o.d" -o ${OBJECTDIR}/BOARD.o BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_adc.o: bounce_adc.c  .generated_files/flags/default/a05e7b6047203b3f6f5933b29fca7dcfebec1a07 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_adc.o.d 
	@${RM} ${OBJECTDIR}/bounce_adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_adc.o.d" -o ${OBJECTDIR}/bounce_adc.o bounce_adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_buttons.o: bounce_buttons.c  .generated_files/flags/default/c393f87471f70ad7ac822a5a023f2bb885a0d3e2 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_buttons.o.d 
	@${RM} ${OBJECTDIR}/bounce_buttons.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_buttons.o.d" -o ${OBJECTDIR}/bounce_buttons.o bounce_buttons.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_ec.o: bounce_ec.c  .generated_files/flags/default/c1eecff3f0d0dc14d99c99bba91b5f18cef913e1 .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_ec.o.d 
	@${RM} ${OBJECTDIR}/bounce_ec.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_ec.o.d" -o ${OBJECTDIR}/bounce_ec.o bounce_ec.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_switch.o: bounce_switch.c  .generated_files/flags/default/d0b9f8f1615f115dc01506ded0cc226df02a0c7a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_switch.o.d 
	@${RM} ${OBJECTDIR}/bounce_switch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_switch.o.d" -o ${OBJECTDIR}/bounce_switch.o bounce_switch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/bounce_timers.o: bounce_timers.c  .generated_files/flags/default/68eb763097e47eab1031a1050fe4b5cb5e340b0c .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bounce_timers.o.d 
	@${RM} ${OBJECTDIR}/bounce_timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/bounce_timers.o.d" -o ${OBJECTDIR}/bounce_timers.o bounce_timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ButtonsTest.o: ButtonsTest.c  .generated_files/flags/default/24fd2c6a38875c9fd656cd242584e1cc4715f9a .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ButtonsTest.o.d 
	@${RM} ${OBJECTDIR}/ButtonsTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/ButtonsTest.o.d" -o ${OBJECTDIR}/ButtonsTest.o ButtonsTest.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Oled.o: Oled.c  .generated_files/flags/default/47c8dc70ac0d5b9f8b04be1f9345650b77672a9b .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Oled.o.d 
	@${RM} ${OBJECTDIR}/Oled.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/Oled.o.d" -o ${OBJECTDIR}/Oled.o Oled.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OledDriver.o: OledDriver.c  .generated_files/flags/default/b3e92e06a40949f169925b3d7c9ffb73bddf40af .generated_files/flags/default/af031a62ccc0c18b099f063c5edfd8e7f9b606f2
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OledDriver.o.d 
	@${RM} ${OBJECTDIR}/OledDriver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/OledDriver.o.d" -o ${OBJECTDIR}/OledDriver.o OledDriver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Lab6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
