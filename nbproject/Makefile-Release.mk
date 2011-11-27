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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
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
	${OBJECTDIR}/source/Livello.o \
	${OBJECTDIR}/source/Giocatore.o \
	${OBJECTDIR}/source/MenuAttivo.o \
	${OBJECTDIR}/source/ElementoAttivo.o \
	${OBJECTDIR}/source/Presentazione.o \
	${OBJECTDIR}/source/Partita.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/source/Elemento.o \
	${OBJECTDIR}/source/MenuLaterale.o \
	${OBJECTDIR}/source/Editor.o \
	${OBJECTDIR}/source/Gioco.o \
	${OBJECTDIR}/source/pezzi/Pezzo.o \
	${OBJECTDIR}/source/MenuCentrale.o \
	${OBJECTDIR}/source/Menu.o \
	${OBJECTDIR}/source/TelecameraAssionometrica.o \
	${OBJECTDIR}/source/Interfaccia.o \
	${OBJECTDIR}/source/GestoreLivelli.o \
	${OBJECTDIR}/source/GestoreGiocatori.o \
	${OBJECTDIR}/source/Telecamera.o \
	${OBJECTDIR}/source/Textures.o \
	${OBJECTDIR}/source/MenuVociDinamiche.o \
	${OBJECTDIR}/source/TelecameraProspettica.o \
	${OBJECTDIR}/source/Griglia.o \
	${OBJECTDIR}/source/PosTelecamere.o \
	${OBJECTDIR}/source/basi/Base.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/opendomino

dist/Release/GNU-Linux-x86/opendomino: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/opendomino ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/source/Livello.o: ./source/Livello.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Livello.o source/Livello.cpp

${OBJECTDIR}/source/Giocatore.o: ./source/Giocatore.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Giocatore.o source/Giocatore.cpp

${OBJECTDIR}/source/MenuAttivo.o: ./source/MenuAttivo.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/MenuAttivo.o source/MenuAttivo.cpp

${OBJECTDIR}/source/ElementoAttivo.o: ./source/ElementoAttivo.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/ElementoAttivo.o source/ElementoAttivo.cpp

${OBJECTDIR}/source/Presentazione.o: ./source/Presentazione.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Presentazione.o source/Presentazione.cpp

${OBJECTDIR}/source/Partita.o: ./source/Partita.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Partita.o source/Partita.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/source/Elemento.o: ./source/Elemento.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Elemento.o source/Elemento.cpp

${OBJECTDIR}/source/MenuLaterale.o: ./source/MenuLaterale.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/MenuLaterale.o source/MenuLaterale.cpp

${OBJECTDIR}/source/Editor.o: ./source/Editor.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Editor.o source/Editor.cpp

${OBJECTDIR}/source/Gioco.o: ./source/Gioco.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Gioco.o source/Gioco.cpp

${OBJECTDIR}/source/pezzi/Pezzo.o: ./source/pezzi/Pezzo.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/pezzi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/pezzi/Pezzo.o source/pezzi/Pezzo.cpp

${OBJECTDIR}/source/MenuCentrale.o: ./source/MenuCentrale.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/MenuCentrale.o source/MenuCentrale.cpp

${OBJECTDIR}/source/Menu.o: ./source/Menu.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Menu.o source/Menu.cpp

${OBJECTDIR}/source/TelecameraAssionometrica.o: ./source/TelecameraAssionometrica.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/TelecameraAssionometrica.o source/TelecameraAssionometrica.cpp

${OBJECTDIR}/source/Interfaccia.o: ./source/Interfaccia.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Interfaccia.o source/Interfaccia.cpp

${OBJECTDIR}/source/GestoreLivelli.o: ./source/GestoreLivelli.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/GestoreLivelli.o source/GestoreLivelli.cpp

${OBJECTDIR}/source/GestoreGiocatori.o: ./source/GestoreGiocatori.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/GestoreGiocatori.o source/GestoreGiocatori.cpp

${OBJECTDIR}/source/Telecamera.o: ./source/Telecamera.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Telecamera.o source/Telecamera.cpp

${OBJECTDIR}/source/Textures.o: ./source/Textures.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Textures.o source/Textures.cpp

${OBJECTDIR}/source/MenuVociDinamiche.o: ./source/MenuVociDinamiche.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/MenuVociDinamiche.o source/MenuVociDinamiche.cpp

${OBJECTDIR}/source/TelecameraProspettica.o: ./source/TelecameraProspettica.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/TelecameraProspettica.o source/TelecameraProspettica.cpp

${OBJECTDIR}/source/Griglia.o: ./source/Griglia.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/Griglia.o source/Griglia.cpp

${OBJECTDIR}/source/PosTelecamere.o: ./source/PosTelecamere.cpp 
	${MKDIR} -p ${OBJECTDIR}/source
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/PosTelecamere.o source/PosTelecamere.cpp

${OBJECTDIR}/source/basi/Base.o: ./source/basi/Base.cpp 
	${MKDIR} -p ${OBJECTDIR}/source/basi
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/source/basi/Base.o source/basi/Base.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/opendomino

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
