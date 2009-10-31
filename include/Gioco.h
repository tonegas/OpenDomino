/* 
 * File:   Gioco.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 23.31
 */

#ifndef _GIOCO_H
#define	_GIOCO_H

#include "Domino.h"

#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame

#define LARGHEZZA_FIN 1000
#define ALTEZZA_FIN  1000
#define BPP_FIN       32

enum Stato {
    MENU,
    PARTITA,
    EDITOR_COSTRUISCI,
    EDITOR_TEST
};

class Editor;

class Gioco {
    //parametri finestra
    int larghezza_finestra;
    int altezza_finestra;
    int bpp;
    bool fullscreen;

    /* Flags to pass to SDL_SetVideoMode */
    unsigned videoFlags;

    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;

    //superfice della finestra
    SDL_Surface *screen;

    //stato del gioco
    Stato stato;

    //variabile per la modifica della velocità di gioco
    int frame_ms;

    //giocatore
    //Giocatore giocatore;

    //Oggetto editor per la gestione della grafica della partita
    Editor domino_editor;

    //indica se il gioco deve smettere di ciclare
    bool alive;

public:

    Gioco();

    void loop();

    void gameExit();

    void setFrames(GLfloat frame_aux);

    int getFrames();

    void setWindowLA(int larghezza_finestra_aux, int altezza_finestra_aux);

    void setFullScreen();

    void resetFullScreen();

    bool getFullScreen();

    int getWindowL();

    int getWindowA();

    int getScreenL();

    int getScreenA();
};

#endif	/* _GIOCO_H */

