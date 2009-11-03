/* 
 * File:   Gioco.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.31
 */

#include "../include/Gioco.h"

Gioco::Gioco():domino_editor(this){
    bpp = BPP_FIN;

    fullscreen = false;
    stato = EDITOR_COSTRUISCI;
    cambia_stato = false;
    alive = true;
    frame_ms = FRAMEMS;

    if ((SDL_Init(SDL_INIT_EVERYTHING) == -1)) {
        printf("ERRORE di inizializzazione SDL: %s.\n", SDL_GetError());
        exit(-1);
    }


    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo();

    if (!videoInfo) {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        exit(-1);
    }

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags = SDL_OPENGL; /* Enable OpenGL in SDL */
    //videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE; /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE; /* Enable window resizing */
    //videoFlags |= SDL_GL_SWAP_CONTROL;

    /* This checks to see if surfaces can be stored in memory */
    if (videoInfo->hw_available)
        videoFlags |= SDL_HWSURFACE;
    else
        videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if (videoInfo->blit_hw)
        videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


    /* get a SDL surface */
    bpp = videoInfo->vfmt->BitsPerPixel;

    //videoFlags |= SDL_FULLSCREEN;
    //setWindowLA(videoInfo->current_h, videoInfo->current_h);
    setWindowLA(LARGHEZZA_FIN, ALTEZZA_FIN);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glHint(GL_LINE_SMOOTH, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_DEPTH_TEST); //questa andrà attivata

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glEnable(GL_MULTISAMPLE);
    //se lo attivo sparisce anche le faccie laterali
    //glEnable(GL_CULL_FACE); //disattuva le faccie posteriori

    if(stato==EDITOR_COSTRUISCI){
        domino = &domino_editor;
        domino_editor.inizializzaEditor();
    }
}

void Gioco::loop() {
    Uint32 inizio, fine;
    int durata, aspetto;

    SDL_Event evento;
    while (SDL_PollEvent(&evento)) {
    }
    while (alive) {
        if(cambia_stato){
            switch(stato){
                case EDITOR_COSTRUISCI: case EDITOR_TEST:
                    domino = &domino_editor;
                    break;
                default:
                    break;
            }
            cambia_stato = false;
        }
        inizio = SDL_GetTicks();

        domino->gestisciInput(&evento);
        //cout<<"dopo Input!!\n"<<flush;
        domino->aggiornaStato();
        //cout<<"dopo Stato!!\n"<<flush;
        domino->video();
        //cout<<"dopo Video!!\n"<<flush;

        fine = SDL_GetTicks();
        durata = fine - inizio;
        aspetto = frame_ms - durata;
        if (aspetto > 0)
            SDL_Delay(aspetto);
        //            else
        //                cout << "H" << flush;

        //        if(SDL_GetTicks() - tempo > 1000){
        //            tempo = SDL_GetTicks();
        //            cout<<frame<<' '<<flush;
        //            frame=0;
        //        }
        //        frame++;
        //        input(&evento);
        //        stato();
        //        video();
    }
}

void Gioco::setStato(Stato stato_aux){
    cambia_stato = true;
    stato = stato_aux;
}

Stato Gioco::getStato(){
    return stato;
}

void Gioco::gameExit() {
    alive = false;
}

void Gioco::setFrames(GLfloat frame_aux) {
    frame_ms = frame_aux;
}

int Gioco::getFrames() {
    return frame_ms;
}

void Gioco::setWindowLA(int larghezza_finestra_aux, int altezza_finestra_aux) {
    larghezza_finestra = larghezza_finestra_aux;
    altezza_finestra = altezza_finestra_aux;
    screen = SDL_SetVideoMode(larghezza_finestra, altezza_finestra, bpp, videoFlags);
    if (!screen) {
        fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
        exit(-1);
    }
}

void Gioco::setFullScreen() {
    fullscreen = true;
    SDL_WM_ToggleFullScreen(screen);
    //        videoFlags |= SDL_FULLSCREEN;
    //        setWindowLA(videoInfo->current_w, videoInfo->current_h);
}

void Gioco::resetFullScreen() {
    fullscreen = false;
    SDL_WM_ToggleFullScreen(screen);
    //        videoFlags &= ~SDL_FULLSCREEN;
    //        setWindowLA(larghezza_finestra, altezza_finestra);
}

bool Gioco::getFullScreen() {
    return fullscreen;
}

int Gioco::getWindowL() {
    return larghezza_finestra;
}

int Gioco::getWindowA() {
    return altezza_finestra;
}

int Gioco::getScreenL() {
    return videoInfo->current_w;
}

int Gioco::getScreenA() {
    return videoInfo->current_h;
}


