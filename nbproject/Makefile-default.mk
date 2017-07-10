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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/anChevrons.cpp src/anClassicHorizSA.cpp src/anColorFlowSA.cpp src/anColorRaceSA.cpp src/anComets.cpp src/anFadeMiddle.cpp src/anPulseFadeSA.cpp src/anRain.cpp src/anRainbowChaser.cpp src/anSplatterSA.cpp src/counter.cpp src/fft.cpp src/io.cpp src/main.cpp src/Neopixel.cpp src/npAnimation.cpp src/npDisplay.cpp src/pixel.cpp src/rgbColor.cpp src/sprite.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/anChevrons.o ${OBJECTDIR}/src/anClassicHorizSA.o ${OBJECTDIR}/src/anColorFlowSA.o ${OBJECTDIR}/src/anColorRaceSA.o ${OBJECTDIR}/src/anComets.o ${OBJECTDIR}/src/anFadeMiddle.o ${OBJECTDIR}/src/anPulseFadeSA.o ${OBJECTDIR}/src/anRain.o ${OBJECTDIR}/src/anRainbowChaser.o ${OBJECTDIR}/src/anSplatterSA.o ${OBJECTDIR}/src/counter.o ${OBJECTDIR}/src/fft.o ${OBJECTDIR}/src/io.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/Neopixel.o ${OBJECTDIR}/src/npAnimation.o ${OBJECTDIR}/src/npDisplay.o ${OBJECTDIR}/src/pixel.o ${OBJECTDIR}/src/rgbColor.o ${OBJECTDIR}/src/sprite.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/anChevrons.o.d ${OBJECTDIR}/src/anClassicHorizSA.o.d ${OBJECTDIR}/src/anColorFlowSA.o.d ${OBJECTDIR}/src/anColorRaceSA.o.d ${OBJECTDIR}/src/anComets.o.d ${OBJECTDIR}/src/anFadeMiddle.o.d ${OBJECTDIR}/src/anPulseFadeSA.o.d ${OBJECTDIR}/src/anRain.o.d ${OBJECTDIR}/src/anRainbowChaser.o.d ${OBJECTDIR}/src/anSplatterSA.o.d ${OBJECTDIR}/src/counter.o.d ${OBJECTDIR}/src/fft.o.d ${OBJECTDIR}/src/io.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/Neopixel.o.d ${OBJECTDIR}/src/npAnimation.o.d ${OBJECTDIR}/src/npDisplay.o.d ${OBJECTDIR}/src/pixel.o.d ${OBJECTDIR}/src/rgbColor.o.d ${OBJECTDIR}/src/sprite.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/anChevrons.o ${OBJECTDIR}/src/anClassicHorizSA.o ${OBJECTDIR}/src/anColorFlowSA.o ${OBJECTDIR}/src/anColorRaceSA.o ${OBJECTDIR}/src/anComets.o ${OBJECTDIR}/src/anFadeMiddle.o ${OBJECTDIR}/src/anPulseFadeSA.o ${OBJECTDIR}/src/anRain.o ${OBJECTDIR}/src/anRainbowChaser.o ${OBJECTDIR}/src/anSplatterSA.o ${OBJECTDIR}/src/counter.o ${OBJECTDIR}/src/fft.o ${OBJECTDIR}/src/io.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/Neopixel.o ${OBJECTDIR}/src/npAnimation.o ${OBJECTDIR}/src/npDisplay.o ${OBJECTDIR}/src/pixel.o ${OBJECTDIR}/src/rgbColor.o ${OBJECTDIR}/src/sprite.o

# Source Files
SOURCEFILES=src/anChevrons.cpp src/anClassicHorizSA.cpp src/anColorFlowSA.cpp src/anColorRaceSA.cpp src/anComets.cpp src/anFadeMiddle.cpp src/anPulseFadeSA.cpp src/anRain.cpp src/anRainbowChaser.cpp src/anSplatterSA.cpp src/counter.cpp src/fft.cpp src/io.cpp src/main.cpp src/Neopixel.cpp src/npAnimation.cpp src/npDisplay.cpp src/pixel.cpp src/rgbColor.cpp src/sprite.cpp


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
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
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/anChevrons.o: src/anChevrons.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anChevrons.o.d 
	@${RM} ${OBJECTDIR}/src/anChevrons.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anChevrons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anChevrons.o.d" -o ${OBJECTDIR}/src/anChevrons.o src/anChevrons.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anClassicHorizSA.o: src/anClassicHorizSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anClassicHorizSA.o.d 
	@${RM} ${OBJECTDIR}/src/anClassicHorizSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anClassicHorizSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anClassicHorizSA.o.d" -o ${OBJECTDIR}/src/anClassicHorizSA.o src/anClassicHorizSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anColorFlowSA.o: src/anColorFlowSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anColorFlowSA.o.d 
	@${RM} ${OBJECTDIR}/src/anColorFlowSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anColorFlowSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anColorFlowSA.o.d" -o ${OBJECTDIR}/src/anColorFlowSA.o src/anColorFlowSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anColorRaceSA.o: src/anColorRaceSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anColorRaceSA.o.d 
	@${RM} ${OBJECTDIR}/src/anColorRaceSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anColorRaceSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anColorRaceSA.o.d" -o ${OBJECTDIR}/src/anColorRaceSA.o src/anColorRaceSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anComets.o: src/anComets.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anComets.o.d 
	@${RM} ${OBJECTDIR}/src/anComets.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anComets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anComets.o.d" -o ${OBJECTDIR}/src/anComets.o src/anComets.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anFadeMiddle.o: src/anFadeMiddle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anFadeMiddle.o.d 
	@${RM} ${OBJECTDIR}/src/anFadeMiddle.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anFadeMiddle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anFadeMiddle.o.d" -o ${OBJECTDIR}/src/anFadeMiddle.o src/anFadeMiddle.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anPulseFadeSA.o: src/anPulseFadeSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anPulseFadeSA.o.d 
	@${RM} ${OBJECTDIR}/src/anPulseFadeSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anPulseFadeSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anPulseFadeSA.o.d" -o ${OBJECTDIR}/src/anPulseFadeSA.o src/anPulseFadeSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anRain.o: src/anRain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anRain.o.d 
	@${RM} ${OBJECTDIR}/src/anRain.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anRain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anRain.o.d" -o ${OBJECTDIR}/src/anRain.o src/anRain.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anRainbowChaser.o: src/anRainbowChaser.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anRainbowChaser.o.d 
	@${RM} ${OBJECTDIR}/src/anRainbowChaser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anRainbowChaser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anRainbowChaser.o.d" -o ${OBJECTDIR}/src/anRainbowChaser.o src/anRainbowChaser.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anSplatterSA.o: src/anSplatterSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anSplatterSA.o.d 
	@${RM} ${OBJECTDIR}/src/anSplatterSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anSplatterSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anSplatterSA.o.d" -o ${OBJECTDIR}/src/anSplatterSA.o src/anSplatterSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/counter.o: src/counter.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/counter.o.d 
	@${RM} ${OBJECTDIR}/src/counter.o 
	@${FIXDEPS} "${OBJECTDIR}/src/counter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/counter.o.d" -o ${OBJECTDIR}/src/counter.o src/counter.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fft.o: src/fft.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fft.o.d 
	@${RM} ${OBJECTDIR}/src/fft.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fft.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/fft.o.d" -o ${OBJECTDIR}/src/fft.o src/fft.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/io.o: src/io.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/io.o.d 
	@${RM} ${OBJECTDIR}/src/io.o 
	@${FIXDEPS} "${OBJECTDIR}/src/io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/io.o.d" -o ${OBJECTDIR}/src/io.o src/io.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/main.o: src/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Neopixel.o: src/Neopixel.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Neopixel.o.d 
	@${RM} ${OBJECTDIR}/src/Neopixel.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Neopixel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/Neopixel.o.d" -o ${OBJECTDIR}/src/Neopixel.o src/Neopixel.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/npAnimation.o: src/npAnimation.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/npAnimation.o.d 
	@${RM} ${OBJECTDIR}/src/npAnimation.o 
	@${FIXDEPS} "${OBJECTDIR}/src/npAnimation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/npAnimation.o.d" -o ${OBJECTDIR}/src/npAnimation.o src/npAnimation.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/npDisplay.o: src/npDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/npDisplay.o.d 
	@${RM} ${OBJECTDIR}/src/npDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/npDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/npDisplay.o.d" -o ${OBJECTDIR}/src/npDisplay.o src/npDisplay.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/pixel.o: src/pixel.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pixel.o.d 
	@${RM} ${OBJECTDIR}/src/pixel.o 
	@${FIXDEPS} "${OBJECTDIR}/src/pixel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/pixel.o.d" -o ${OBJECTDIR}/src/pixel.o src/pixel.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/rgbColor.o: src/rgbColor.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rgbColor.o.d 
	@${RM} ${OBJECTDIR}/src/rgbColor.o 
	@${FIXDEPS} "${OBJECTDIR}/src/rgbColor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/rgbColor.o.d" -o ${OBJECTDIR}/src/rgbColor.o src/rgbColor.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/sprite.o: src/sprite.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sprite.o.d 
	@${RM} ${OBJECTDIR}/src/sprite.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sprite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/sprite.o.d" -o ${OBJECTDIR}/src/sprite.o src/sprite.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/anChevrons.o: src/anChevrons.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anChevrons.o.d 
	@${RM} ${OBJECTDIR}/src/anChevrons.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anChevrons.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anChevrons.o.d" -o ${OBJECTDIR}/src/anChevrons.o src/anChevrons.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anClassicHorizSA.o: src/anClassicHorizSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anClassicHorizSA.o.d 
	@${RM} ${OBJECTDIR}/src/anClassicHorizSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anClassicHorizSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anClassicHorizSA.o.d" -o ${OBJECTDIR}/src/anClassicHorizSA.o src/anClassicHorizSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anColorFlowSA.o: src/anColorFlowSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anColorFlowSA.o.d 
	@${RM} ${OBJECTDIR}/src/anColorFlowSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anColorFlowSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anColorFlowSA.o.d" -o ${OBJECTDIR}/src/anColorFlowSA.o src/anColorFlowSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anColorRaceSA.o: src/anColorRaceSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anColorRaceSA.o.d 
	@${RM} ${OBJECTDIR}/src/anColorRaceSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anColorRaceSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anColorRaceSA.o.d" -o ${OBJECTDIR}/src/anColorRaceSA.o src/anColorRaceSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anComets.o: src/anComets.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anComets.o.d 
	@${RM} ${OBJECTDIR}/src/anComets.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anComets.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anComets.o.d" -o ${OBJECTDIR}/src/anComets.o src/anComets.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anFadeMiddle.o: src/anFadeMiddle.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anFadeMiddle.o.d 
	@${RM} ${OBJECTDIR}/src/anFadeMiddle.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anFadeMiddle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anFadeMiddle.o.d" -o ${OBJECTDIR}/src/anFadeMiddle.o src/anFadeMiddle.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anPulseFadeSA.o: src/anPulseFadeSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anPulseFadeSA.o.d 
	@${RM} ${OBJECTDIR}/src/anPulseFadeSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anPulseFadeSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anPulseFadeSA.o.d" -o ${OBJECTDIR}/src/anPulseFadeSA.o src/anPulseFadeSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anRain.o: src/anRain.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anRain.o.d 
	@${RM} ${OBJECTDIR}/src/anRain.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anRain.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anRain.o.d" -o ${OBJECTDIR}/src/anRain.o src/anRain.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anRainbowChaser.o: src/anRainbowChaser.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anRainbowChaser.o.d 
	@${RM} ${OBJECTDIR}/src/anRainbowChaser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anRainbowChaser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anRainbowChaser.o.d" -o ${OBJECTDIR}/src/anRainbowChaser.o src/anRainbowChaser.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/anSplatterSA.o: src/anSplatterSA.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/anSplatterSA.o.d 
	@${RM} ${OBJECTDIR}/src/anSplatterSA.o 
	@${FIXDEPS} "${OBJECTDIR}/src/anSplatterSA.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/anSplatterSA.o.d" -o ${OBJECTDIR}/src/anSplatterSA.o src/anSplatterSA.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/counter.o: src/counter.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/counter.o.d 
	@${RM} ${OBJECTDIR}/src/counter.o 
	@${FIXDEPS} "${OBJECTDIR}/src/counter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/counter.o.d" -o ${OBJECTDIR}/src/counter.o src/counter.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/fft.o: src/fft.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/fft.o.d 
	@${RM} ${OBJECTDIR}/src/fft.o 
	@${FIXDEPS} "${OBJECTDIR}/src/fft.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/fft.o.d" -o ${OBJECTDIR}/src/fft.o src/fft.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/io.o: src/io.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/io.o.d 
	@${RM} ${OBJECTDIR}/src/io.o 
	@${FIXDEPS} "${OBJECTDIR}/src/io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/io.o.d" -o ${OBJECTDIR}/src/io.o src/io.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/main.o: src/main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/Neopixel.o: src/Neopixel.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/Neopixel.o.d 
	@${RM} ${OBJECTDIR}/src/Neopixel.o 
	@${FIXDEPS} "${OBJECTDIR}/src/Neopixel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/Neopixel.o.d" -o ${OBJECTDIR}/src/Neopixel.o src/Neopixel.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/npAnimation.o: src/npAnimation.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/npAnimation.o.d 
	@${RM} ${OBJECTDIR}/src/npAnimation.o 
	@${FIXDEPS} "${OBJECTDIR}/src/npAnimation.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/npAnimation.o.d" -o ${OBJECTDIR}/src/npAnimation.o src/npAnimation.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/npDisplay.o: src/npDisplay.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/npDisplay.o.d 
	@${RM} ${OBJECTDIR}/src/npDisplay.o 
	@${FIXDEPS} "${OBJECTDIR}/src/npDisplay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/npDisplay.o.d" -o ${OBJECTDIR}/src/npDisplay.o src/npDisplay.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/pixel.o: src/pixel.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pixel.o.d 
	@${RM} ${OBJECTDIR}/src/pixel.o 
	@${FIXDEPS} "${OBJECTDIR}/src/pixel.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/pixel.o.d" -o ${OBJECTDIR}/src/pixel.o src/pixel.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/rgbColor.o: src/rgbColor.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/rgbColor.o.d 
	@${RM} ${OBJECTDIR}/src/rgbColor.o 
	@${FIXDEPS} "${OBJECTDIR}/src/rgbColor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/rgbColor.o.d" -o ${OBJECTDIR}/src/rgbColor.o src/rgbColor.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/src/sprite.o: src/sprite.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/sprite.o.d 
	@${RM} ${OBJECTDIR}/src/sprite.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sprite.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fno-enforce-eh-specs -O1 -MMD -MF "${OBJECTDIR}/src/sprite.o.d" -o ${OBJECTDIR}/src/sprite.o src/sprite.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=16384,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -O1 -o dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=16384,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/LEDCanvas.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
