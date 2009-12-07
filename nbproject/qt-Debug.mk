#############################################################################
# Makefile for building: dist/Debug/GNU-Linux-x86/OpenDomino
# Generated by qmake (2.01a) (Qt 4.4.3) on: lun dic 7 17:36:54 2009
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: /usr/bin/qmake -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -D_GNU_SOURCE=1 -DQT_XML_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -Inbproject -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtXml -I/usr/include/qt4 -I/usr/include/SDL -I/usr/local/include -I/usr/local/include/FTGL -I/usr/include/freetype2 -Inbproject -Inbproject -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib `pkg-config --libs ftgl --libs sdl` -lGL -lGLU -lQtXml -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/Debug/GNU-Linux-x86/

####### Files

SOURCES       = source/GestoreGiocatori.cpp \
		source/GestoreLivelli.cpp \
		source/Editor.cpp \
		source/PosTelecamere.cpp \
		main.cpp \
		source/basi/Base.cpp \
		source/Menu.cpp \
		source/Griglia.cpp \
		source/Elemento.cpp \
		source/Textures.cpp \
		source/Livello.cpp \
		source/Telecamera.cpp \
		source/TelecameraProspettica.cpp \
		source/Gioco.cpp \
		source/ElementoAttivo.cpp \
		source/Interfaccia.cpp \
		source/Partita.cpp \
		source/Giocatore.cpp \
		source/TelecameraAssionometrica.cpp \
		source/pezzi/Pezzo.cpp 
OBJECTS       = build/Debug/GNU-Linux-x86/GestoreGiocatori.o \
		build/Debug/GNU-Linux-x86/GestoreLivelli.o \
		build/Debug/GNU-Linux-x86/Editor.o \
		build/Debug/GNU-Linux-x86/PosTelecamere.o \
		build/Debug/GNU-Linux-x86/main.o \
		build/Debug/GNU-Linux-x86/Base.o \
		build/Debug/GNU-Linux-x86/Menu.o \
		build/Debug/GNU-Linux-x86/Griglia.o \
		build/Debug/GNU-Linux-x86/Elemento.o \
		build/Debug/GNU-Linux-x86/Textures.o \
		build/Debug/GNU-Linux-x86/Livello.o \
		build/Debug/GNU-Linux-x86/Telecamera.o \
		build/Debug/GNU-Linux-x86/TelecameraProspettica.o \
		build/Debug/GNU-Linux-x86/Gioco.o \
		build/Debug/GNU-Linux-x86/ElementoAttivo.o \
		build/Debug/GNU-Linux-x86/Interfaccia.o \
		build/Debug/GNU-Linux-x86/Partita.o \
		build/Debug/GNU-Linux-x86/Giocatore.o \
		build/Debug/GNU-Linux-x86/TelecameraAssionometrica.o \
		build/Debug/GNU-Linux-x86/Pezzo.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		nbproject/qt-Debug.pro
QMAKE_TARGET  = OpenDomino
DESTDIR       = dist/Debug/GNU-Linux-x86/
TARGET        = dist/Debug/GNU-Linux-x86/OpenDomino

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: qttmp-Debug.mk $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/Debug/GNU-Linux-x86/ || $(MKDIR) dist/Debug/GNU-Linux-x86/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

qttmp-Debug.mk: nbproject/qt-Debug.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtXml.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist: 
	@$(CHK_DIR_EXISTS) nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0 || $(MKDIR) nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0/ && $(COPY_FILE) --parents include/Textures.h include/Menu.h include/pezzi/Pezzo.h include/Domino.h include/Partita.h include/Giocatore.h include/PosTelecamere.h include/ElementoAttivo.h include/Interfaccia.h include/Elemento.h include/Griglia.h include/TelecameraAssionometrica.h include/basi/Base.h include/Telecamera.h include/GestoreLivelli.h include/Livello.h include/GestoreGiocatori.h include/Gioco.h include/TelecameraProspettica.h include/Editor.h nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0/ && $(COPY_FILE) --parents source/GestoreGiocatori.cpp source/GestoreLivelli.cpp source/Editor.cpp source/PosTelecamere.cpp main.cpp source/basi/Base.cpp source/Menu.cpp source/Griglia.cpp source/Elemento.cpp source/Textures.cpp source/Livello.cpp source/Telecamera.cpp source/TelecameraProspettica.cpp source/Gioco.cpp source/ElementoAttivo.cpp source/Interfaccia.cpp source/Partita.cpp source/Giocatore.cpp source/TelecameraAssionometrica.cpp source/pezzi/Pezzo.cpp nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0/ && (cd `dirname nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0` && $(TAR) OpenDomino1.0.0.tar OpenDomino1.0.0 && $(COMPRESS) OpenDomino1.0.0.tar) && $(MOVE) `dirname nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0`/OpenDomino1.0.0.tar.gz . && $(DEL_FILE) -r nbproject/build/Debug/GNU-Linux-x86/OpenDomino1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) qttmp-Debug.mk


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

build/Debug/GNU-Linux-x86/GestoreGiocatori.o: source/GestoreGiocatori.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/GestoreGiocatori.o source/GestoreGiocatori.cpp

build/Debug/GNU-Linux-x86/GestoreLivelli.o: source/GestoreLivelli.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/GestoreLivelli.o source/GestoreLivelli.cpp

build/Debug/GNU-Linux-x86/Editor.o: source/Editor.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Editor.o source/Editor.cpp

build/Debug/GNU-Linux-x86/PosTelecamere.o: source/PosTelecamere.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/PosTelecamere.o source/PosTelecamere.cpp

build/Debug/GNU-Linux-x86/main.o: main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/main.o main.cpp

build/Debug/GNU-Linux-x86/Base.o: source/basi/Base.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Base.o source/basi/Base.cpp

build/Debug/GNU-Linux-x86/Menu.o: source/Menu.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Menu.o source/Menu.cpp

build/Debug/GNU-Linux-x86/Griglia.o: source/Griglia.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Griglia.o source/Griglia.cpp

build/Debug/GNU-Linux-x86/Elemento.o: source/Elemento.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Elemento.o source/Elemento.cpp

build/Debug/GNU-Linux-x86/Textures.o: source/Textures.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Textures.o source/Textures.cpp

build/Debug/GNU-Linux-x86/Livello.o: source/Livello.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Livello.o source/Livello.cpp

build/Debug/GNU-Linux-x86/Telecamera.o: source/Telecamera.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Telecamera.o source/Telecamera.cpp

build/Debug/GNU-Linux-x86/TelecameraProspettica.o: source/TelecameraProspettica.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/TelecameraProspettica.o source/TelecameraProspettica.cpp

build/Debug/GNU-Linux-x86/Gioco.o: source/Gioco.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Gioco.o source/Gioco.cpp

build/Debug/GNU-Linux-x86/ElementoAttivo.o: source/ElementoAttivo.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/ElementoAttivo.o source/ElementoAttivo.cpp

build/Debug/GNU-Linux-x86/Interfaccia.o: source/Interfaccia.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Interfaccia.o source/Interfaccia.cpp

build/Debug/GNU-Linux-x86/Partita.o: source/Partita.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Partita.o source/Partita.cpp

build/Debug/GNU-Linux-x86/Giocatore.o: source/Giocatore.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Giocatore.o source/Giocatore.cpp

build/Debug/GNU-Linux-x86/TelecameraAssionometrica.o: source/TelecameraAssionometrica.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/TelecameraAssionometrica.o source/TelecameraAssionometrica.cpp

build/Debug/GNU-Linux-x86/Pezzo.o: source/pezzi/Pezzo.cpp include/Domino.h \
		include/Textures.h \
		include/Elemento.h \
		include/ElementoAttivo.h \
		include/basi/Base.h \
		include/pezzi/Pezzo.h \
		include/Griglia.h \
		include/PosTelecamere.h \
		include/Telecamera.h \
		include/TelecameraAssionometrica.h \
		include/TelecameraProspettica.h \
		include/Interfaccia.h \
		include/Livello.h \
		include/Partita.h \
		include/Editor.h \
		include/GestoreLivelli.h \
		include/Giocatore.h \
		include/GestoreGiocatori.h \
		include/Menu.h \
		include/Gioco.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/GNU-Linux-x86/Pezzo.o source/pezzi/Pezzo.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

