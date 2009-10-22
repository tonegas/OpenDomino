#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Evento.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Heap_Eventi.o \
	${OBJECTDIR}/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=`pkg-config --cflags sdl` 
CXXFLAGS=`pkg-config --cflags sdl` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/opendomino

dist/Release/GNU-Linux-x86/opendomino: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} `pkg-config --libs sdl` -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opendomino  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Evento.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Evento.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio
	${RM} $@.d
	$(COMPILE.cc) -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Evento.o /home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Evento.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Heap_Eventi.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Heap_Eventi.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio
	${RM} $@.d
	$(COMPILE.cc) -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Heap_Eventi.o /home/tonegas/workspace/Domino-Net/OpenDomino/source/appoggio/Heap_Eventi.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/opendomino

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
