/* 
 * File:   Gioco.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.31
 */

#include "../include/Domino.h"

Gioco::Gioco() : menu(this, &evento, LARGHEZZA_FIN, ALTEZZA_FIN) {// : domino_editor(this, &evento) {
    bpp = BPP_FIN;

    //    test_partita_allocata = false;
    fullscreen = false;
    stato = MENU;
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
    //esiste una funzione opengl glFinish(); che forse è meglio
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);


    /* get a SDL surface */
    bpp = videoInfo->vfmt->BitsPerPixel;

    //videoFlags |= SDL_FULLSCREEN;
    //setWindowLA(videoInfo->current_h, videoInfo->current_h);
    setWindowLA(LARGHEZZA_FIN, ALTEZZA_FIN);

    /* Enable Texture Mapping ( NEW ) */
    glEnable(GL_TEXTURE_2D);

    /* Enable smooth shading */
    glShadeModel(GL_SMOOTH);

    //        /* Set the background black */
    //        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //
    //        /* Depth buffer setup */
    //        glClearDepth(1.0f);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    //glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_DEPTH_TEST); //questa andrà attivata
    /* The Type Of Depth Test To Do */
    //glDepthFunc(GL_LEQUAL);
    glDepthFunc(GL_LESS);


    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    glEnable(GL_MULTISAMPLE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    GLuint fogMode[] = {GL_EXP, GL_EXP2, GL_LINEAR};
    GLfloat fogColor[4] = {37.0 / 255.0, 104.0 / 255.0, 246.0 / 255.0, 1.0f}; //{ 0.5f, 0.5f, 0.5f, 1.0f };

    /* Setup the Fog */
    glFogi(GL_FOG_MODE, fogMode[2]); /* Fog Mode */
    glFogfv(GL_FOG_COLOR, fogColor); /* Set Fog Color */
    glFogf(GL_FOG_DENSITY, 0.01f); /* How Dense Will The Fog Be */
    glHint(GL_FOG_HINT, GL_NICEST); /* Fog Hint Value */
    glFogf(GL_FOG_START, 5000.0f); /* Fog Start Depth */
    glFogf(GL_FOG_END, 11000.0f); /* Fog End Depth */
    glEnable(GL_FOG);

    //se lo attivo sparisce anche le faccie laterali
    //glEnable(GL_CULL_FACE); //disattuva le faccie posteriori

    int key_color[3] = {37, 104, 246};
    Textures::loadTextures("crate.bmp", TEX_PEZZO);
    Textures::loadTextures("nuvola1.bmp", TEX_NUVOLA1, key_color, true);
    Textures::loadTextures("nuvola2.bmp", TEX_NUVOLA2, key_color, true);


    giocatore_attuale = gestore_giocatori.getGiocatoreAttuale();
    giocatore_attuale->inizializza(this, &evento);
    //    domino = &domino_editor;
    //    domino->inizializza();
}

Gioco::~Gioco() {
    //    if (test_partita_allocata)
    //        delete domino;
}

void Gioco::loop() {
    Uint32 inizio, fine;
    int durata, aspetto;
    while (SDL_PollEvent(&evento)) {
    }
    while (alive) {
        if (cambia_stato) {
            if (stato == GIOCATORE) {
                giocatore_attuale->riconfiguraVideo();
            }
            cambia_stato = false;
        }
        //                if (cambia_stato) {
        //                    switch (stato) {
        //                        case MENU:
        //                            menu.setVisibile(true);
        //                            break;
        //                        case EDITOR_TEST:
        //                            if (test_partita_allocata) {
        //                                delete domino;
        //                                domino = new Partita(domino_editor);
        //                            } else {
        //                                test_partita_allocata = true;
        //                                domino = new Partita(domino_editor);
        //                            }
        //                            break;
        //                        case EDITOR_COSTRUISCI:
        //                            if (test_partita_allocata) {
        //                                delete domino;
        //                            }
        //                            test_partita_allocata = false;
        //                            domino = &domino_editor;
        //                            break;
        //                        default:
        //                            break;
        //                    }
        //                    cambia_stato = false;
        //                    domino->inizializza();
        //                }
        inizio = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        switch (stato) {
            case MENU:
                //                domino->configuraVisuale();
                //                domino->cicloGiocoStampa();
                giocatore_attuale->cicloGiocoStampa();
                menu.cicloGioco();
                break;
            case GIOCATORE:
                giocatore_attuale->cicloGioco();
                break;
        }
        //        if (menu.getVisibile()) {
        //            domino->configuraVisuale();
        //            domino->cicloGiocoStampa();
        //            //c'è bisogno di riaccendere le luci poi c'è bisogno di riconfigurare ogni volta la telecamera
        //            //magari bisogna scrivere una funzione
        //            menu.cicloGioco();
        //            //frame_ms = 50;
        //        } else {
        //            giocatore_attuale->cicloGioco();
        //            //domino->cicloGioco();
        //            //variare il frameRate quando sono nel menu
        //            //frame_ms = FRAMEMS;
        //        }
        SDL_GL_SwapBuffers();


        fine = SDL_GetTicks();
        durata = fine - inizio;
        aspetto = frame_ms - durata;
        if (aspetto > 0) {
            SDL_Delay(aspetto);
        } else {
            cout << "SCATTA" << '\n' << flush;
        }
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

void Gioco::setStato(Stato stato_aux) {
    if (stato_aux != stato) {
        cambia_stato = true;
        stato = stato_aux;
    }
}

Stato Gioco::getStato() const {
    return stato;
}

void Gioco::setStatoGiocatore(StatoGiocatore stato_aux) {
    giocatore_attuale->setStato(stato_aux);
}

StatoGiocatore Gioco::getStatoGiocatore() {
    return giocatore_attuale->getStato();
}

void Gioco::gameExit() {
    alive = false;
}

void Gioco::setFrames(int frame_aux) {
    frame_ms = frame_aux;
}

int Gioco::getFrames() const {
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

bool Gioco::getFullScreen() const {
    return fullscreen;
}

int Gioco::getWindowL() const {
    return larghezza_finestra;
}

int Gioco::getWindowA() const {
    return altezza_finestra;
}

int Gioco::getScreenL() const {
    return videoInfo->current_w;
}

int Gioco::getScreenA() const {
    return videoInfo->current_h;
}

GestoreGiocatori* Gioco::getGestoreGiocatori() {
    return &gestore_giocatori;
}


