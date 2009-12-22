/* 
 * File:   Livello.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 16.03
 */

#include "../include/Domino.h"


using namespace std;

Livello::Livello(StrutturaLivello *livello, TipoLivello tipo) {
    griglia_livello = livello->griglia_livello;
    tele_assio = new TelecameraAssionometrica(livello->posizione_telecamere.telecamera_assionometrica, griglia_livello->getDimGrigliaX(), griglia_livello->getDimGrigliaY());
    tele_prosp = new TelecameraProspettica(livello->posizione_telecamere.telecamera_prospettica, griglia_livello->getDimGrigliaX(), griglia_livello->getDimGrigliaY());
    tipo_proiezione = livello->tipo_proiezione;
    tipo_livello = tipo;
    bottone_destro = false;
    bottone_sinistro = false;
    bottone_centrale = false;
    caratteristiche_selezione = NIENTE;
    entrambi = false;
}

Livello::Livello(int num_x_colonne_aux, int num_y_righe_aux, TipoLivello tipo) {
    griglia_livello = new Griglia(num_x_colonne_aux, num_y_righe_aux);
    tele_assio = new TelecameraAssionometrica(num_x_colonne_aux, num_y_righe_aux);
    tele_prosp = new TelecameraProspettica(num_x_colonne_aux, num_y_righe_aux);
    tipo_livello = tipo;

    bottone_destro = false;
    bottone_sinistro = false;
    bottone_centrale = false;
    tipo_proiezione = PROSPETTICA;

    caratteristiche_selezione = NIENTE;
    entrambi = false;
}

Livello::Livello(const Livello& orig):Interfaccia((Interfaccia)orig) {
    griglia_livello = new Griglia(*orig.griglia_livello);
    tele_assio = new TelecameraAssionometrica(*orig.tele_assio);
    tele_prosp = new TelecameraProspettica(*orig.tele_prosp);
    tipo_livello = orig.tipo_livello;

    bottone_destro = orig.bottone_destro;
    bottone_sinistro = orig.bottone_sinistro;
    bottone_centrale = orig.bottone_centrale;
    tipo_proiezione = orig.tipo_proiezione;

    tele_assio = orig.tele_assio;
    tele_prosp = orig.tele_prosp;

    caratteristiche_selezione = NIENTE;
    entrambi = false;
    inizializza();
}

Livello::~Livello() {
    delete griglia_livello;
}

int Livello::inizializza() {
    //int aux_mx, aux_my;
    switch (tipo_proiezione) {
        case ASSIONOMETRICA:
            telecamera_attuale = tele_assio;
            break;
        case PROSPETTICA:
            telecamera_attuale = tele_prosp;
            break;
    }
    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
    //anche qui l'ho tolto ma serve per la selezione quando passo da editor a gioco
    //SDL_GetMouseState(&aux_mx, &aux_my);
    //telecamera_attuale->getMousePosGrigliaXY(aux_mx, aux_my);
    //mouseMotion(SDL_Event *evento);
    return 1;
}

void Livello::configuraVisuale() {
    telecamera_attuale->configuraVisuale();
}

void Livello::attivaSelezioni() {
}

void Livello::mouseButtonDown() {

}

void Livello::mouseMotion() {
}

void Livello::mouseButtonUp() {
}

void Livello::keyDownF5() {
    if (tipo_livello == LIVELLO_EDITOR) {
        if (gioco->getStatoGiocatore() == EDITOR_TEST) {
            gioco->setStatoGiocatore(EDITOR_COSTRUISCI);
        } else {
            gioco->setStatoGiocatore(EDITOR_TEST);
        }
    }
}

void Livello::gestisciInput() {
    if (evento->type == SDL_QUIT) {
        gioco->gameExit();
    }
    switch (evento->type) {
        case SDL_KEYDOWN:
            switch (evento->key.keysym.sym) {
                case SDLK_ESCAPE:
                    gioco->setStato(MENU);
                    switch (tipo_livello) {
                        case LIVELLO_PARTITA:
                            gioco->setStatoMenu(GL_GIOCA_LIVELLO);
                            break;
                        case LIVELLO_EDITOR://devo diversicare nel caso sia a fare i test!!!!!!!!!!!
                            if (gioco->getStatoGiocatore() == EDITOR_COSTRUISCI){
                                gioco->setStatoMenu(EL_EDITOR_LIVELLO);
                            }else{
                                gioco->setStatoMenu(ELP_EDITOR_LIVELLO_PROVA);
                            }
                            break;
                        case LIVELLO_PRESENTAZIONE:
                            gioco->setStatoMenu(PRINCIPALE);
                            break;
                    }
                    break;
                case SDLK_PAGEUP:
                    if (gioco->getFrames() > 1)
                        gioco->setFrames(gioco->getFrames() - 1);
                    break;
                case SDLK_F5:
                    keyDownF5();
                    break;
                case SDLK_PAGEDOWN:
                    gioco->setFrames(gioco->getFrames() + 1);
                    break;
                case SDLK_F1:
                    telecamera_attuale = tele_prosp;
                    tipo_proiezione = PROSPETTICA;
                    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
                    telecamera_attuale->mouseSelezione(this, griglia_livello);
                    attivaSelezioni();
                    //qui devo usare attiva selezioni e non mouseMotion()
                    //lo tolgo ma devo risolvere il problema delle selezioni
                    //telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    //mouseMotion();
                    break;
                case SDLK_F2:
                    telecamera_attuale = tele_assio;
                    tipo_proiezione = ASSIONOMETRICA;
                    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
                    telecamera_attuale->mouseSelezione(this, griglia_livello);
                    attivaSelezioni();
                    //telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    //mouseMotion();
                    break;
                case SDLK_p:
                    gioco->setStato(MENU);
                    gioco->setStatoMenu(PAUSA);
                    break;
                case SDLK_f:
                    if (gioco->getFullScreen()) {
                        gioco->resetFullScreen();
                        //setProiezione(tipo_proiezione, gioco->getWindowA(), gioco->getWindowL());
                    } else {
                        gioco->setFullScreen();
                        //setProiezione(tipo_proiezione, gioco->getScreenA(), gioco->getScreenL());
                    }
                    break;
                case SDLK_i:
                    //cout << tipo_proiezione << ' ' << griglia_livello.getGriglia().x << ' ' << griglia_livello.getGriglia().y << ' ' << griglia_livello.getGriglia().zoom << '\n' << flush;
                    break;
                default:
                    break;

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            telecamera_attuale->getMousePosGrigliaXY(evento->button.x, evento->button.y);
            switch (evento->button.button) {
                case SDL_BUTTON_RIGHT:
                    telecamera_attuale->registraPosizione();
                    bottone_destro = true;
                    break;
                case SDL_BUTTON_WHEELUP: case SDL_BUTTON_WHEELDOWN:
                    if (!bottone_destro) {
                        if (evento->button.button == SDL_BUTTON_WHEELUP) {
                            telecamera_attuale->registraZoomAvanti();
                        } else {
                            telecamera_attuale->registraZoomIndietro();

                        }
                    }
                    break;
                case SDL_BUTTON_MIDDLE:
                    if (tipo_proiezione == PROSPETTICA && !bottone_destro) {
                        telecamera_attuale->registraPosizione();
                        bottone_centrale = true;
                    }
                    break;
            }
            mouseButtonDown();
            break;
        case SDL_MOUSEMOTION:
            telecamera_attuale->getMousePosGrigliaXY(evento->button.x, evento->button.y);
            if (bottone_destro) {
                telecamera_attuale->cambiaXY();
            } else if (bottone_centrale) {
                telecamera_attuale->cambiaAngolazione();
            }
            mouseMotion();
            break;
        case SDL_MOUSEBUTTONUP:
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                bottone_destro = false;
            } else if (evento->button.button == SDL_BUTTON_MIDDLE) {
                bottone_centrale = false;
            }
            mouseButtonUp();
            break;
        case SDL_VIDEORESIZE:
            gioco->resize(evento->resize.w, evento->resize.h);
        default:
            break;
    }
}

void Livello::resize(unsigned dim_x, unsigned dim_y) {
    telecamera_attuale->setProiezioneTelecamera(dim_x, dim_y);
}

void Livello::cicloGioco() {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        gestisciInput();
    }
    telecamera_attuale->aggiorna(gioco->getFrames());
    attivaSelezioni();
    cicloGiocoAggiornaEStampa();
}

void Livello::cicloGiocoAggiornaEStampa() {
    glPushMatrix();
    stampaSfondo();
    telecamera_attuale->visualeOpenGL();
    stampaSuperficeBase();
    griglia_livello->aggiornaStatoEStampa();
    glPopMatrix();
}

void Livello::cicloGiocoStampa() {
    glPushMatrix();
    stampaSfondo();
    telecamera_attuale->visualeOpenGL();
    stampaSuperficeBase();
    griglia_livello->stampa();
    glPopMatrix();
}

void Livello::stampaSuperficeBase() {
    static GLfloat colorblue [] = {0.0f, 0.0f, 1.0f, 0.5f};
    static GLfloat colorblue2 [] = {0.3f, 0.3f, 0.5f, 0.8f};
    static GLfloat luce_posizione[] = {2.0f, 5.0f, 1.0f, 0.0};
    static GLfloat luce_diffusa [] = {1.0f, 1.0f, 1.0f, 1.0f};
    static GLfloat luce_ambiente [] = {0.3f, 0.3f, 0.3f, 1.0f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, luce_diffusa);
    glLightfv(GL_LIGHT1, GL_AMBIENT, luce_ambiente);
    glLightfv(GL_LIGHT1, GL_POSITION, luce_posizione);
    glPushMatrix();

    //glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, colorblue);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorblue);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, colorblue2);
    //glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, colorblue2);
    //glColor4fv(colorblue);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorblue);
    glTranslatef(0.0, 0.0, POSIZIONE_SUPERFICE);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello->getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello->getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);

        //        glNormal3f(0.0, 0.0, -1.0);
        //        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -25);
        //        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -25);
        //        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -25);
        //        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -25);

    }
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glPopMatrix();
}

struct Nuvola {
    unsigned int w, h;
    GLfloat x, y, vel, zoom;
    GLuint indice;
};

void Livello::stampaSfondo() {
    static bool prima = true;
    static Nuvola nuvole[NUMERO_NUVOLE];
    static GLfloat cieloAzzurro [] = {1.0f, 1.0f, 1.0f, 1.0f};
    if (prima) {
        glClearColor(37.0 / 255.0, 104.0 / 255.0, 246.0 / 255.0, 1.0f);
        for (int i = 0; i < NUMERO_NUVOLE; i++) {
            nuvole[i].zoom = (rand() % 10) / 4.0;
            nuvole[i].x = (rand() % 2000) / 2.0 - 1000.0;
            nuvole[i].y = (rand() % 400) / 2.0 - 500.0;
            nuvole[i].vel = (rand() % 1000) / 1000.0;
            switch (i % TIPI_DI_NUVOLE) {
                case 0:
                    nuvole[i].indice = indice_texture[TEX_NUVOLA1];
                    nuvole[i].h = struttura_texture[TEX_NUVOLA1].h;
                    nuvole[i].w = struttura_texture[TEX_NUVOLA1].w;
                    break;
                case 1:
                    nuvole[i].indice = indice_texture[TEX_NUVOLA2];
                    nuvole[i].h = struttura_texture[TEX_NUVOLA2].h;
                    nuvole[i].w = struttura_texture[TEX_NUVOLA2].w;
                    break;
                default:
                    break;
            }
        }
        prima = false;
    }

    glPushMatrix();
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cieloAzzurro);
    glColor4fv(cieloAzzurro);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glBlendFunc(GL_DST_COLOR, GL_CONSTANT_COLOR);
    for (int i = 0; i < NUMERO_NUVOLE; i++) {
        glPushMatrix();
        glTranslatef(nuvole[i].x, nuvole[i].y, 0.0);
        glScaled(nuvole[i].zoom, nuvole[i].zoom, nuvole[i].zoom);
        glBindTexture(GL_TEXTURE_2D, nuvole[i].indice);
        glBegin(GL_QUADS);
        {
            glNormal3f(0.0, 0.0, 1.0);
            glTexCoord2f(0.0f, 1.0f), glVertex3f(0.0, 0.0, 0.0);
            glTexCoord2f(0.0f, 0.0f), glVertex3f(0.0, nuvole[i].h, 0.0);
            glTexCoord2f(1.0f, 0.0f), glVertex3f(nuvole[i].w, nuvole[i].h, 0.0);
            glTexCoord2f(1.0f, 1.0f), glVertex3f(nuvole[i].w, 0.0, 0.0);

        }
        glEnd();
        glPopMatrix();
        nuvole[i].x = (nuvole[i].x + nuvole[i].vel) < 1000 ? (nuvole[i].x + nuvole[i].vel) : -4000;
    }

    //    glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_NUVOLA1]);
    //    glBegin(GL_QUADS);
    //    {
    //        glNormal3f(0.0, 0.0, 1.0);
    //        glTexCoord2f(0.0f, 0.0f), glVertex3f(-1.0, -1.0, 0.0);
    //        glTexCoord2f(0.0f, 1.0f), glVertex3f(-1.0, 1.0, 0.0);
    //        glTexCoord2f(1.0f, 1.0f), glVertex3f(1.0, 1.0, 0.0);
    //        glTexCoord2f(1.0f, 0.0f), glVertex3f(1.0, -1.0, 0.0);
    //
    //    }
    //    glEnd();
    //    glBlendFunc( GL_ONE, GL_ONE );
    //    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_NUVOLA2]);
    //    glBegin(GL_QUADS);
    //    {
    //        glNormal3f(0.0, 0.0, 1.0);
    //        glTexCoord2f(1.0f, 0.0f), glVertex3f(-100.0, -100.0, 0.0);
    //        glTexCoord2f(0.0f, 0.0f), glVertex3f(-100.0, 100.0, 0.0);
    //        glTexCoord2f(0.0f, 1.0f), glVertex3f(100.0, 100.0, 0.0);
    //        glTexCoord2f(1.0f, 1.0f), glVertex3f(100.0, -100.0, 0.0);
    //
    //    }
    //    glEnd();
    //    glTranslatef(50.0, 0.0, 0.0);
    //    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    //    glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_NUVOLA2_MASK]);
    //    glBegin(GL_QUADS);
    //    {
    //        glNormal3f(0.0, 0.0, 1.0);
    //        glTexCoord2f(1.0f, 0.0f), glVertex3f(-100.0, -100.0, 0.0);
    //        glTexCoord2f(0.0f, 0.0f), glVertex3f(-100.0, 100.0, 0.0);
    //        glTexCoord2f(0.0f, 1.0f), glVertex3f(100.0, 100.0, 0.0);
    //        glTexCoord2f(1.0f, 1.0f), glVertex3f(100.0, -100.0, 0.0);
    //
    //    }
    //    glEnd();
    //    glBlendFunc( GL_ONE, GL_ONE );
    //    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_NUVOLA2]);
    //    glBegin(GL_QUADS);
    //    {
    //        glNormal3f(0.0, 0.0, 1.0);
    //        glTexCoord2f(1.0f, 0.0f), glVertex3f(-100.0, -100.0, 0.0);
    //        glTexCoord2f(0.0f, 0.0f), glVertex3f(-100.0, 100.0, 0.0);
    //        glTexCoord2f(0.0f, 1.0f), glVertex3f(100.0, 100.0, 0.0);
    //        glTexCoord2f(1.0f, 1.0f), glVertex3f(100.0, -100.0, 0.0);
    //
    //    }
    //    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);

    glPopMatrix();
}

void Livello::resettaSelezione() {
    caratteristiche_selezione = NIENTE;
    entrambi = false;
}

void Livello::selezioneDavantiPezzo(unsigned aux_x_pezzo_selezionato, unsigned aux_y_pezzo_selezionato) {
    if (caratteristiche_selezione == DAVANTI_BASE) {
        entrambi = true;
    }
    caratteristiche_selezione = DAVANTI_PEZZO;
    x_pezzo_selezionato = aux_x_pezzo_selezionato;
    y_pezzo_selezionato = aux_y_pezzo_selezionato;
}

void Livello::selezioneDavantiBase(unsigned aux_x_base_selezionata, unsigned aux_y_base_selezionata) {
    if (caratteristiche_selezione == DAVANTI_PEZZO) {
        entrambi = true;
    }
    caratteristiche_selezione = DAVANTI_BASE;
    x_base_selezionata = aux_x_base_selezionata;
    y_base_selezionata = aux_y_base_selezionata;
}

void Livello::getStrutturaLivello(StrutturaLivello *livello) {
    livello->griglia_livello = griglia_livello;
    livello->posizione_telecamere.telecamera_assionometrica = (*tele_assio->getPosTeleAssio());
    livello->posizione_telecamere.telecamera_prospettica = (*tele_prosp->getPosTeleProsp());
    livello->tipo_proiezione = tipo_proiezione;
}

void Livello::setStrutturaLivello(StrutturaLivello *livello) {
    livello->griglia_livello = griglia_livello;
    livello->posizione_telecamere.telecamera_assionometrica = (*tele_assio->getPosTeleAssio());
    livello->posizione_telecamere.telecamera_prospettica = (*tele_prosp->getPosTeleProsp());
    livello->tipo_proiezione = tipo_proiezione;
}

TipoLivello Livello::getTipoLivello() {
    return tipo_livello;
}

//void Livello::setInPartita(bool aux_in_partita) {
//    griglia_livello->setInPartita(aux_in_partita);
//}
//
//bool Livello::getInPartita() {
//    return griglia_livello->getInPartita();
//}