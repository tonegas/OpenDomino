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
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Posizione.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Editor.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/basi/Base.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Griglia.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Textures.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Livello.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Telecamera.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraProspettica.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Gioco.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Partita.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Giocatore.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraAssionometrica.o \
	${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/pezzi/Pezzo.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/opendomino

dist/Debug/GNU-Linux-x86/opendomino: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} `pkg-config --libs sdl` -lGL -lGLU -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opendomino  ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Posizione.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Posizione.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Posizione.o /home/tonegas/workspace/Domino/OpenDomino/source/Posizione.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Editor.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Editor.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Editor.o /home/tonegas/workspace/Domino/OpenDomino/source/Editor.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/basi/Base.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/basi/Base.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/basi
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/basi/Base.o /home/tonegas/workspace/Domino/OpenDomino/source/basi/Base.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Griglia.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Griglia.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Griglia.o /home/tonegas/workspace/Domino/OpenDomino/source/Griglia.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Textures.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Textures.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Textures.o /home/tonegas/workspace/Domino/OpenDomino/source/Textures.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Livello.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Livello.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Livello.o /home/tonegas/workspace/Domino/OpenDomino/source/Livello.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Telecamera.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Telecamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Telecamera.o /home/tonegas/workspace/Domino/OpenDomino/source/Telecamera.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraProspettica.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/TelecameraProspettica.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraProspettica.o /home/tonegas/workspace/Domino/OpenDomino/source/TelecameraProspettica.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Gioco.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Gioco.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Gioco.o /home/tonegas/workspace/Domino/OpenDomino/source/Gioco.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Partita.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Partita.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Partita.o /home/tonegas/workspace/Domino/OpenDomino/source/Partita.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Giocatore.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/Giocatore.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/Giocatore.o /home/tonegas/workspace/Domino/OpenDomino/source/Giocatore.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraAssionometrica.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/TelecameraAssionometrica.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/TelecameraAssionometrica.o /home/tonegas/workspace/Domino/OpenDomino/source/TelecameraAssionometrica.cpp

${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/pezzi/Pezzo.o: nbproject/Makefile-${CND_CONF}.mk /home/tonegas/workspace/Domino/OpenDomino/source/pezzi/Pezzo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/pezzi
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/tonegas/workspace/Domino/OpenDomino/source/pezzi/Pezzo.o /home/tonegas/workspace/Domino/OpenDomino/source/pezzi/Pezzo.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/opendomino

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
