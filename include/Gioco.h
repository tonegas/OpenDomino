/* 
 * File:   Gioco.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 23.31
 */

#ifndef _GIOCO_H
#define	_GIOCO_H

#define FRAMERATE   50                  //frame per secondo massimi
#define FRAMEMS     1000/FRAMERATE      //millisecondi per frame

#define LARGHEZZA_FIN 1000
#define ALTEZZA_FIN  1000
#define BPP_FIN       32

enum Stato {
    MENU,
    GIOCATORE
    //    PARTITA,
    //    EDITOR_COSTRUISCI,
    //    EDITOR_TEST
};

class Editor;
class Partita;
class Livello;
class Menu;

#include "Domino.h"

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
    SDL_Event evento;

    //stato del gioco
    Stato stato;
    //flag che indica il cambiamento dello stato
    bool cambia_stato;

    //variabile per la modifica della velocità di gioco
    int frame_ms;

    //questa voce deve stare prima delle altre altrimenti non inizializza variabili statiche servono al giocatore
    //---------------
    Interfaccia variabili;
    //---------------
    GestoreGiocatori gestore_giocatori;
    Menu menu;
    Giocatore **giocatore_attuale;
    //   Interfaccia *video;

    //indica se il gioco deve smettere di ciclare
    bool alive;

    void setWindowLA(int larghezza_finestra_aux, int altezza_finestra_aux);

public:


    Gioco();

    ~Gioco();

    void loop();

    void gameExit();

    void setFrames(int frame_aux);

    int getFrames() const;

    void setStato(Stato stato_aux);

    Stato getStato() const;

    void setStatoGiocatore(StatoGiocatore stato_aux);

    StatoGiocatore getStatoGiocatore();

    void setStatoMenu(StatoMenu stato_aux);

    StatoMenu getStatoMenu();

    void resize(unsigned dim_x, unsigned dim_y);

    void setFullScreen();

    void resetFullScreen();

    bool getFullScreen() const;

    int getWindowL() const;

    int getWindowA() const;

    int getScreenL() const;

    int getScreenA() const;

    GestoreGiocatori* getGestoreGiocatori();
};

#endif	/* _GIOCO_H */

