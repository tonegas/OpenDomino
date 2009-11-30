/* 
 * File:   Livello.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 16.03
 */

#include "../include/Domino.h"


using namespace std;

Livello::Livello(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux) :
griglia_livello(num_x_colonne_aux, num_y_righe_aux),
tele_assio(num_x_colonne_aux, num_y_righe_aux),
tele_prosp(num_x_colonne_aux, num_y_righe_aux) {
    gioco = gioco_aux;

    bottone_destro = false;
    bottone_sinistro = false;
    bottone_centrale = false;
    tipo_proiezione = PROSPETTICA;

    caratteristiche_selezione = NIENTE;
    entrambi = false;
}

Livello::Livello(const Livello& orig) :
griglia_livello(orig.griglia_livello),
tele_assio(orig.tele_assio),
tele_prosp(orig.tele_prosp) {
    gioco = orig.gioco;

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

int Livello::inizializza() {
    //int aux_mx, aux_my;
    switch (tipo_proiezione) {
        case ASSIONOMETRICA:
            telecamera_attuale = &tele_assio;
            break;
        case PROSPETTICA:
            telecamera_attuale = &tele_prosp;
            break;
    }
    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
    //anche qui l'ho tolto ma serve per la selezione quando passo da editor a gioco
    //SDL_GetMouseState(&aux_mx, &aux_my);
    //telecamera_attuale->getMousePosGrigliaXY(aux_mx, aux_my);
    //mouseMotion(SDL_Event *evento);
    return 1;
}

void Livello::attivaSelezioni() {
    }

void Livello::mouseButtonDown(SDL_Event *evento){

    }

void Livello::mouseMotion(SDL_Event *evento) {
    }

void Livello::mouseButtonUp(SDL_Event *evento) {
    }

void Livello::keyDownF5() {
    if (gioco->getStato() == EDITOR_TEST) {
        gioco->setStato(EDITOR_COSTRUISCI);
    } else {
        gioco->setStato(EDITOR_TEST);
    }
}

void Livello::gestisciInput(SDL_Event *evento) {
    if (evento->type == SDL_QUIT) {
        gioco->gameExit();
    }
    switch (evento->type) {
        case SDL_KEYDOWN:
            switch (evento->key.keysym.sym) {
                case SDLK_ESCAPE:
                    //gioco->setStato(MENU);
                    //------------------
                    gioco->gameExit();
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
                case SDLK_p:
                    telecamera_attuale = &tele_prosp;
                    tipo_proiezione = PROSPETTICA;
                    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
                    telecamera_attuale->mouseSelezione(this, &griglia_livello);
                    attivaSelezioni();
                    //qui devo usare attiva selezioni e non mouseMotion()
                    //lo tolgo ma devo risolvere il problema delle selezioni
                    //telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    //mouseMotion();
                    break;
                case SDLK_a:
                    telecamera_attuale = &tele_assio;
                    tipo_proiezione = ASSIONOMETRICA;
                    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
                    telecamera_attuale->mouseSelezione(this, &griglia_livello);
                    attivaSelezioni();
                    //telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    //mouseMotion();
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
            mouseButtonDown(evento);
            break;
        case SDL_MOUSEMOTION:
            telecamera_attuale->getMousePosGrigliaXY(evento->button.x, evento->button.y);
            if (bottone_destro) {
                telecamera_attuale->cambiaXY();
            } else if (bottone_centrale) {
                telecamera_attuale->cambiaAngolazione();
            }
            mouseMotion(evento);
            break;
        case SDL_MOUSEBUTTONUP:
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                bottone_destro = false;
            } else if (evento->button.button == SDL_BUTTON_MIDDLE) {
                bottone_centrale = false;
            }
            mouseButtonUp(evento);
            break;
        case SDL_VIDEORESIZE:
            gioco->setWindowLA(evento->resize.w, evento->resize.h);
            telecamera_attuale->setProiezioneTelecamera(evento->resize.w, evento->resize.h);
        default:
            break;
    }
}

void Livello::cicloGioco(SDL_Event *evento) {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        gestisciInput(evento);
    }

    telecamera_attuale->aggiorna(gioco->getFrames());

    attivaSelezioni();

    glPushMatrix();

    stampaSfondo();

    telecamera_attuale->visualeOpenGL();

    //    if (griglia_livello.in_partita) {
    //        GLUquadric *myQuad;
    //        GLint slices, stacks;
    //        glPushMatrix();
    //        glMaterialfv(GL_FRONT, GL_DIFFUSE, colorwhite);
    //        glTranslatef(pos_x_griglia, pos_y_griglia, pos_z_griglia + ALTEZZA_PEZZO / 2.0);
    //        slices = stacks = 50;
    //        myQuad = gluNewQuadric();
    //        gluSphere(myQuad, 3, slices, stacks);
    //        glPopMatrix();
    //    }

    stampaSuperficeBase();

    griglia_livello.aggiornaStatoEStampa();

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
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);
        glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -5);
        glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, -5);

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