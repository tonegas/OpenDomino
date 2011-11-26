# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = .
TARGET = OpenDomino
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
QT = core xml
SOURCES += ./source/Livello.cpp ./source/Giocatore.cpp ./source/MenuAttivo.cpp ./source/ElementoAttivo.cpp ./source/Presentazione.cpp ./source/Partita.cpp main.cpp ./source/Elemento.cpp ./source/MenuLaterale.cpp ./source/Editor.cpp ./source/Gioco.cpp ./source/pezzi/Pezzo.cpp ./source/Menu.cpp ./source/TelecameraAssionometrica.cpp ./source/MenuCentrale.cpp ./source/Interfaccia.cpp ./source/GestoreLivelli.cpp ./source/GestoreGiocatori.cpp ./source/Telecamera.cpp ./source/Textures.cpp ./source/MenuVociDinamiche.cpp ./source/TelecameraProspettica.cpp ./source/Griglia.cpp ./source/PosTelecamere.cpp ./source/basi/Base.cpp
HEADERS += ./include/Textures.h ./include/Domino.h ./include/MenuAttivo.h ./include/MenuLaterale.h ./include/Menu.h ./include/MenuCentrale.h ./include/Livello.h ./include/TelecameraProspettica.h ./include/Telecamera.h ./include/Interfaccia.h ./include/Presentazione.h ./include/GestoreLivelli.h ./include/PosTelecamere.h ./include/Giocatore.h ./include/GestoreGiocatori.h ./include/Elemento.h ./include/Griglia.h ./include/Partita.h ./include/TelecameraAssionometrica.h ./include/MenuVociDinamiche.h ./include/ElementoAttivo.h ./include/Editor.h ./include/Gioco.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
LIBS+=`pkg-config --libs ftgl --libs sdl` -lGL -lGLU
CXXFLAGS+=`pkg-config --cflags sdl`
INCPATH+=/usr/include/SDL
DEFINES+=_GNU_SOURCE=1
INCPATH+=/usr/local/include /usr/local/include/FTGL /usr/include/freetype2
