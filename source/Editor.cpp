/* 
 * File:   Editor.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.37
 */

#include "../include/Domino.h"

using namespace std;

GLfloat coloryellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorblue [] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat colorgreen [] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorwhite [] = {1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat lightpos[] = {0, 0, 0, 1};
GLfloat lightpos_ambient[] = {60, 120, 150, 0};

Editor::Editor(int num_y_righe_aux, int num_x_colonne_aux) : Livello(num_x_colonne_aux, num_y_righe_aux, FRAMERATE) {
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    posiziona_pezzi = true;
    posiziona_continua = 0;
    cubo_selezione = new GLfloat*[num_x_colonne];
    for (int i = 0; i < num_x_colonne; i++)
        cubo_selezione[i] = new GLfloat[num_y_righe];
    for (int i = 0; i < num_x_colonne; i++)
        for (int j = 0; j < num_y_righe; j++)
            cubo_selezione[i][j] = 0;
}

Editor::~Editor() {
    for (int i = 0; i < num_y_righe; i++)
        delete cubo_selezione[i];
    delete cubo_selezione;
}

int Editor::aggiornaStato() {
    Livello::aggiornaStato();
    return 1;
}

void Editor::inizializzaEditor(Gioco *gioco_aux) {
    //qui faccio così perchè se non sono diversi "tipo_proiezione=PROSPETTICA" e ASSIONOMETRICA non fa gli assegnamenti
    tipo_proiezione = PROSPETTICA;
    gioco = gioco_aux;

    setProiezione(ASSIONOMETRICA, LARGHEZZA_FIN_EDITOR, ALTEZZA_FIN_EDITOR);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

void Editor::stampaSuperficeBase() {
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorblue);
    glTranslatef(0.0, 0.0, POSIZIONE_SUPERFICE);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
    glVertex3f(num_x_colonne * ALTEZZA_PEZZO + ALTEZZA_PEZZO, num_y_righe * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
    glVertex3f(-ALTEZZA_PEZZO, num_y_righe * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
    glEnd();

    glPopMatrix();
}

void Editor::stampaPezzo(bool wire, int x, int y, GLfloat attivo) {

    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    if (wire)glDisable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coloryellow);
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);
    glColor4f(1.0f, 1.0f, 0.0f, attivo);
    glLineWidth(1.5);
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    if (wire)glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Editor::stampaBase(bool wire, int x, int y, GLfloat attivo) {


    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    if (wire)glDisable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    glColor4f(0.0f, 1.0f, 0.0f, attivo);
    glLineWidth(1.5);
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(wire ? GL_LINE_STRIP : GL_QUADS);
    {
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    if (wire)glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Editor::stampaQuadrato(int x, int y, GLfloat attivo) {
    GLfloat xf = (GLfloat) x;
    GLfloat yf = (GLfloat) y;

    GLfloat sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    GLfloat sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glDisable(GL_LIGHTING);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y, 0.0);
    glScalef(0.97, 0.97, 0.97);
    glTranslatef(ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015, ALTEZZA_PEZZO * 0.015);
    glColor4f(0.0f, 1.0f, 0.0f, attivo);
    glLineWidth(2.5);
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, -1.0);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, 1.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 0.0, 1.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(-1.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, 0.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, ALTEZZA_PEZZO, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(0.0, -1.0, 1.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(0.0, 0.0, ALTEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINES);
    {
        glNormal3f(1.0, -1.0, 0.0);
        glVertex3f(ALTEZZA_PEZZO, 0.0, ALTEZZA_PEZZO);
        glVertex3f(ALTEZZA_PEZZO, 0.0, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
    //    /* double buffering! */
}

int Editor::video() {

    //SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );
    //    if (cambio_zoom) {
    //        h_finestra = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI);
    //        l_finestra = ((GLfloat)ALTEZZA_FIN/(GLfloat)LARGHEZZA_FIN)*h_finestra;
    //
    //        da_2d_a_3d = 2.0*h_telecamera*tan(fovy/2.0/180.0*M_PI) / (GLfloat)ALTEZZA_FIN;
    //        glMatrixMode(GL_MODELVIEW);
    //        glLoadIdentity();
    //        gluLookAt(
    //                0, 0, h_telecamera, /* eye  */
    //                0, 0, 0.0, /* center  */
    //                0.0, 1.0, 0.0); /* up is in positive Y direction */
    //        cambio_zoom=false;
    //    }

    /*
     * GL_COLOR_BUFFER_BIT      Color buffers 		: Viene resa l’immagine (almeno 2, anche di piu’ per il rendering stereo.
     * GL_DEPTH_BUFFER_BIT      Depth buffer		: Usato per eliminare le parti nascoste.
     * GL_STENCIL_BUFFER_BIT    Stencil buffer 		: Usato per “ritagliare” aree dello schermo.
     * GL_ACCUM_BUFFER_BIT      Accumulation buffer	: Accumula i risultati per effetti speciali come  Motion Blur, simulare il fuoco, ombre, ...
     */


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
    if (getMousePosGrigliaXY(gioco->getWindowA())) {
        //cubo_selezione[pos_x_griglia][pos_y_griglia] = 1;
        int sopra = mouseSelezione(gioco->getWindowA());
        if (sopra == 1 && posiziona_continua != -2 && posiziona_continua != 2)
            griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setSelezione(1);
        if (sopra == 2 && posiziona_continua != -1 && posiziona_continua != 1)
            griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setSelezione(1);

    }

    glPushMatrix();
    if (tipo_proiezione == PROSPETTICA) {
        glRotatef(angolo_telecamera_y, 1, 0, 0);
        glRotatef(-angolo_telecamera_x, 0, 1, 0);
    }
    glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
    glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model_griglia);

    //glLightfv(GL_LIGHT0, GL_DIFFUSE, colorwhite);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, colorwhite);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos_ambient);

    stampaSuperficeBase();
    for (int i = 0; i < num_x_colonne; i++) {
        for (int j = 0; j < num_y_righe; j++) {
            if (cubo_selezione[i][j] > 0) {
                stampaQuadrato(i, j, cubo_selezione[i][j]);
                cubo_selezione[i][j] -= 0.05;
            }
            if (griglia_livello.getPezzo(i, j).getSelezione() > 0) {
                stampaPezzo(true, i, j, griglia_livello.getPezzo(i, j).getSelezione());
                griglia_livello.getPezzo(i, j).setSelezione(griglia_livello.getPezzo(i, j).getSelezione() - 0.05);
            }
            if (griglia_livello.getBase(i, j).getSelezione() > 0) {
                stampaBase(true, i, j, griglia_livello.getBase(i, j).getSelezione());
                griglia_livello.getBase(i, j).setSelezione(griglia_livello.getBase(i, j).getSelezione() - 0.05);
            }
            if (griglia_livello.getPezzo(i, j).getAlive() == 1) {
                stampaPezzo(false, i, j, 0.0);
                griglia_livello.getPezzo(i, j).setSelezione(0);
            }
            if (griglia_livello.getBase(i, j).getAlive() == 1) {
                stampaBase(false, i, j, 0.0);
                griglia_livello.getBase(i, j).setSelezione(0);
            }
        }
    }

    glPopMatrix();
    SDL_GL_SwapBuffers();

    return 1;
}

int Editor::gestisciInput(SDL_Event *evento) {
    SDL_PumpEvents();
    int sopra;
    while (SDL_PollEvent(evento)) {
        if (Livello::gestisciInput(evento)) {
            switch (evento->type) {
                case SDL_KEYDOWN:
                    switch (evento->key.keysym.sym) {
                        case SDLK_1:
                            posiziona_pezzi = true;
                            posiziona_basi = false;
                            posiziona_continua = 0;
                            break;
                        case SDLK_2:
                            posiziona_pezzi = false;
                            posiziona_basi = true;
                            posiziona_continua = 0;
                            break;
                        default:
                            break;

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
                    if (evento->button.button == SDL_BUTTON_LEFT) {
                        if (pos_griglia_ok) {
                            sopra = mouseSelezione(gioco->getWindowA());
                            if (sopra == 1) {
                                if (griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).getAlive()) {
                                    griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(false);
                                    posiziona_continua = -1;
                                } else {
                                    griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(true);
                                    posiziona_continua = 1;
                                }
                            }
                            if (sopra == 2) {
                                if (griglia_livello.getBase(pos_x_griglia, pos_y_griglia).getAlive()) {
                                    griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setAlive(false);
                                    posiziona_continua = -2;
                                } else {
                                    griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setAlive(true);
                                    posiziona_continua = 2;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        sopra = mouseSelezione(gioco->getWindowA());
                        if (sopra == 1 && posiziona_continua != -2 && posiziona_continua != 2)
                            griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setSelezione(1);
                        if (sopra == 2 && posiziona_continua != -1 && posiziona_continua != 1)
                            griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setSelezione(1);

                        if (posiziona_continua == -1 && sopra == 1)
                            griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(false);
                        if (posiziona_continua == -2 && sopra == 2)
                            griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setAlive(false);

                        if (posiziona_continua == 1 && sopra == 1)
                            griglia_livello.getPezzo(pos_x_griglia, pos_y_griglia).setAlive(true);
                        if (posiziona_continua == 2 && sopra == 2)
                            griglia_livello.getBase(pos_x_griglia, pos_y_griglia).setAlive(true);

                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (evento->button.button == SDL_BUTTON_LEFT) {

                        posiziona_continua = 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 1;
}

int Editor::mouseSelezione(int altezza_fin) {
    GLuint buffer[512]; // Set Up A Selection Buffer
    GLint hits = 0;
    glSelectBuffer(512, buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (altezza_fin - mouse_y_fin), 1.0f, 1.0f, matrice_view);
        if (tipo_proiezione == PROSPETTICA) {
            gluPerspective(FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), ZNEAR, ZFAR);
        } else {
            glOrtho(0, (GLfloat)  (matrice_view[2] - matrice_view[0]), 0, (GLfloat) altezza_fin, ZNEAR, ZFAR);
            glMultMatrixf(cavalier);
        }
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        {

            if (tipo_proiezione == PROSPETTICA) {
                glRotatef(angolo_telecamera_y, 1, 0, 0);
                glRotatef(-angolo_telecamera_x, 0, 1, 0);
            }
            glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
            glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
            glLoadName(1);
            stampaPezzo(false, pos_x_griglia, pos_y_griglia, 0.0);
            glLoadName(2);
            stampaBase(false, pos_x_griglia, pos_y_griglia, 0.0);
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
    if (hits > 0) // If There Were More Than 0 Hits
    {
        for (int loop = 0; loop < hits; loop++) {
            if (buffer[loop * 4 + 3] == 2 && posiziona_continua != -1 && posiziona_continua != 1) {
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

