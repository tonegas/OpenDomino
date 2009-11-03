/* 
 * File:   Editor.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 23.37
 */

#include "../include/Editor.h"
#include "../include/Partita.h"
#include "../include/Gioco.h"

using namespace std;

GLfloat coloryellow[] = {1.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorblue [] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat colorgreen [] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat colorwhite [] = {1.0f, 1.0f, 1.0f, 1.0f};
//GLfloat lightpos[] = {0, 0, 0, 1};
GLfloat lightpos_ambient[] = {60, 120, 150, 0};

Editor::Editor(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux)
: Livello(gioco_aux, num_x_colonne_aux, num_y_righe_aux, FRAMERATE)
, test(gioco_aux, num_x_colonne_aux, num_y_righe_aux) {
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    posiziona_pezzi = true;
    azione_continua = 0;
    caratteristiche_selezione = 0;
    entrambi = false;

    cubo_selezione = new GLfloat*[num_x_colonne];
    for (int i = 0; i < num_x_colonne; i++)
        cubo_selezione[i] = new GLfloat[num_y_righe];
    for (int i = 0; i < num_x_colonne; i++)
        for (int j = 0; j < num_y_righe; j++)
            cubo_selezione[i][j] = 0;
}

Editor::~Editor() {
    for (int i = 0; i < num_y_righe; i++)
        delete []cubo_selezione[i];
    delete []cubo_selezione;
}

void Editor::inizializzaEditor() {
    //qui faccio così perchè se non sono diversi "tipo_proiezione=PROSPETTICA" e ASSIONOMETRICA non fa gli assegnamenti
    tipo_proiezione = PROSPETTICA;

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
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coloryellow);
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);
    if (wire) {
        glDisable(GL_LIGHTING);
        GLfloat grandezza = attivo;
        glTranslatef(SPESSORE_PEZZO * (1.0 - grandezza) / 2, ALTEZZA_PEZZO * (1.0 - grandezza) / 2, LARGHEZZA_PEZZO * (1.0 - grandezza) / 2);
        glScalef(grandezza, grandezza, grandezza);
    }
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
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorgreen);
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    if (wire) {
        glDisable(GL_LIGHTING);
        GLfloat grandezza = attivo;
        glTranslatef(SPESSORE_BASE * (1.0 - grandezza) / 2, ALTEZZA_BASE * (1.0 - grandezza) / 2, LARGHEZZA_BASE * (1.0 - grandezza) / 2);
        glScalef(grandezza, grandezza, grandezza);
    }
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

int Editor::aggiornaStato() {
    if(gioco->getStato() == EDITOR_TEST){
        return test.aggiornaStato();
    }else{
        return aggiornaStatoEditor();
    }
}

int Editor::aggiornaStatoEditor(){
    return Livello::aggiornaStato();
}

int Editor::video(){
    if(gioco->getStato() == EDITOR_TEST){
        return test.video();
    }else{
        return videoEditor();
    }
}

int Editor::videoEditor() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    Posizione* p_aux, *p_aux_pezzo, *p_aux_base;

    SDL_GetMouseState(&mouse_x_fin, &mouse_y_fin);
    if (azione_continua == 0 && getMousePosGrigliaXY(gioco->getWindowA())) {
        //cubo_selezione[pos_x_griglia][pos_y_griglia] = 1;
        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi)
            p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
        if (caratteristiche_selezione == DAVANTI_BASE || entrambi)
            p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
        if (caratteristiche_selezione == DAVANTI_PEZZO) {
            if (p_aux_pezzo->occupata) {
                if (p_aux_pezzo->tipo == ELEM_PEZZO)
                    p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            } else {
                p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
            }
        }
        if (caratteristiche_selezione == DAVANTI_BASE) {
            if (p_aux_base->occupata) {
                if (p_aux_base->tipo == ELEM_BASE)
                    p_aux_base->attivaSelezione(ELEM_BASE);
            } else {
                p_aux_base->attivaSelezione(ELEM_BASE);
            }
        }
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
            p_aux = griglia_livello.getPosizione(i, j);
            //            if (cubo_selezione[i][j] > 0) {
            //                stampaQuadrato(i, j, cubo_selezione[i][j]);
            //                cubo_selezione[i][j] -= 0.05;
            //            }
            if (p_aux->selezione_pezzo > 0) {
                stampaPezzo(true, i, j, p_aux->selezione_pezzo);
                p_aux->selezione_pezzo -= 0.05;
            }
            if (p_aux->selezione_base > 0) {
                stampaBase(true, i, j, p_aux->selezione_base);
                p_aux->selezione_base -= 0.05;
            }
            if (p_aux->occupata == 1 && p_aux->tipo == ELEM_PEZZO) {
                stampaPezzo(false, i, j, 0.0);
            }
            if (p_aux->occupata == 1 && p_aux->tipo == ELEM_BASE) {
                stampaBase(false, i, j, 0.0);
            }
        }
    }

    glPopMatrix();
    SDL_GL_SwapBuffers();

    return 1;
}

int Editor::gestisciInput(SDL_Event *evento){
    if(gioco->getStato() == EDITOR_TEST){
        return test.gestisciInput(evento);
    }else{
        return gestisciInputEditor(evento);
    }
}

int Editor::gestisciInputEditor(SDL_Event *evento) {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        if (Livello::gestisciInput(evento)) {
            switch (evento->type) {
                case SDL_KEYDOWN:
                    switch (evento->key.keysym.sym) {
                        case SDLK_1:
                            posiziona_pezzi = true;
                            posiziona_basi = false;
                            azione_continua = 0;
                            break;
                        case SDLK_2:
                            posiziona_pezzi = false;
                            posiziona_basi = true;
                            azione_continua = 0;
                            break;
                        case SDLK_F5:
                            gioco->setStato(EDITOR_TEST);
                            break;
                        default:
                            break;

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
                    if (evento->button.button == SDL_BUTTON_LEFT) {
                        if (pos_griglia_ok) {
                            mouseSelezione(gioco->getWindowA());
                            Posizione *p_aux_pezzo, *p_aux_base;
                            if (caratteristiche_selezione == DAVANTI_PEZZO) {
                                p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
                                if (p_aux_pezzo->occupata) {
                                    if (p_aux_pezzo->tipo == ELEM_PEZZO) {
                                        p_aux_pezzo->liberaPosizione();
                                        azione_continua = ELIMINA_PEZZI;
                                    }
                                } else {
                                    p_aux_pezzo->occupaPosizione(new Pezzo, ELEM_PEZZO);
                                    azione_continua = POSIZIONA_PEZZI;
                                }
                            }
                            if (caratteristiche_selezione == DAVANTI_BASE) {
                                p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
                                if (p_aux_base->occupata) {
                                    if (p_aux_base->tipo == ELEM_BASE) {
                                        p_aux_base->liberaPosizione();
                                        azione_continua = ELIMINA_BASI;
                                    }
                                } else {
                                    p_aux_base->occupaPosizione(new Base, ELEM_BASE);
                                    azione_continua = POSIZIONA_BASI;
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y)) {
                        mouseSelezione(gioco->getWindowA());
                        Posizione *p_aux_pezzo, *p_aux_base;
                        if (caratteristiche_selezione == DAVANTI_PEZZO || entrambi)
                            p_aux_pezzo = griglia_livello.getPosizione(x_pezzo_selezionato, y_pezzo_selezionato);
                        if (caratteristiche_selezione == DAVANTI_BASE || entrambi)
                            p_aux_base = griglia_livello.getPosizione(x_base_selezionata, y_base_selezionata);
                        switch (azione_continua) {
                            case POSIZIONA_PEZZI:
                                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && !p_aux_pezzo->occupata) {
                                    p_aux_pezzo->occupaPosizione(new Pezzo, ELEM_PEZZO);
                                    p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
                                }
                                break;
                            case POSIZIONA_BASI:
                                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && !p_aux_base->occupata) {
                                    p_aux_base->occupaPosizione(new Base, ELEM_BASE);
                                    p_aux_base->attivaSelezione(ELEM_BASE);
                                }
                                break;
                            case ELIMINA_PEZZI:
                                if ((caratteristiche_selezione == DAVANTI_PEZZO || entrambi) && p_aux_pezzo->occupata && p_aux_pezzo->tipo == ELEM_PEZZO) {
                                    p_aux_pezzo->liberaPosizione();
                                    p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
                                }
                                break;
                            case ELIMINA_BASI:
                                if ((caratteristiche_selezione == DAVANTI_BASE || entrambi) && p_aux_base->occupata && p_aux_base->tipo == ELEM_BASE) {
                                    p_aux_base->liberaPosizione();
                                    p_aux_base->attivaSelezione(ELEM_BASE);
                                }
                                break;
                            default:
                                if (caratteristiche_selezione == DAVANTI_PEZZO) {
                                    if (p_aux_pezzo->occupata) {
                                        if (p_aux_pezzo->tipo == ELEM_PEZZO)
                                            p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
                                    } else {
                                        p_aux_pezzo->attivaSelezione(ELEM_PEZZO);
                                    }
                                }
                                if (caratteristiche_selezione == DAVANTI_BASE) {
                                    if (p_aux_base->occupata) {
                                        if (p_aux_base->tipo == ELEM_BASE)
                                            p_aux_base->attivaSelezione(ELEM_BASE);
                                    } else {
                                        p_aux_base->attivaSelezione(ELEM_BASE);
                                    }
                                }
                                break;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (evento->button.button == SDL_BUTTON_LEFT) {
                        azione_continua = 0;
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
            glOrtho(0, (GLfloat) (matrice_view[2] - matrice_view[0]), 0, (GLfloat) altezza_fin, ZNEAR, ZFAR);
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
            int indice = 1;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if ((int) pos_x_griglia + i > 0 && (int) pos_x_griglia + i < num_x_colonne && (int) pos_y_griglia + j > 0 && (int) pos_y_griglia + j < num_y_righe) {
                        if (griglia_livello.getPosizione(pos_x_griglia + i, pos_y_griglia + j)->occupata) {
                            if (griglia_livello.getPosizione(pos_x_griglia + i, pos_y_griglia + j)->tipo == ELEM_PEZZO) {
                                glLoadName((i + 1) * 3 + (j + 1) + 1);
                                stampaPezzo(false, pos_x_griglia + i, pos_y_griglia + j, 0.0);
                            } else {
                                glLoadName(11 + (i + 1) * 3 + (j + 1));
                                stampaBase(false, pos_x_griglia + i, pos_y_griglia + j, 0.0);
                            }
                        } else {
                            glLoadName((i + 1) * 3 + (j + 1) + 1);
                            stampaPezzo(false, pos_x_griglia + i, pos_y_griglia + j, 0.0);
                            glLoadName(11 + (i + 1) * 3 + (j + 1));
                            stampaBase(false, pos_x_griglia + i, pos_y_griglia + j, 0.0);
                        }
                        indice++;
                    }
                }
            }
        }
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
    }
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    hits = glRenderMode(GL_RENDER);
    caratteristiche_selezione = 0;
    if (hits > 0) // If There Were More Than 0 Hits
    {
        unsigned distanza = -1;
        entrambi = false;
        for (int loop = 0; loop < hits; loop++) {
            if (buffer[loop * 4 + 3] < 10) {
                if (distanza > buffer[loop * 4 + 1]) {
                    if (caratteristiche_selezione == DAVANTI_BASE) {
                        entrambi = true;
                    }
                    caratteristiche_selezione = DAVANTI_PEZZO;
                    distanza = buffer[loop * 4 + 1];
                    x_pezzo_selezionato = pos_x_griglia + ((buffer[loop * 4 + 3] - 1) / 3 - 1);
                    y_pezzo_selezionato = pos_y_griglia + ((buffer[loop * 4 + 3] - 1) % 3 - 1);
                }
            } else {
                if (distanza > buffer[loop * 4 + 1]) {
                    if (caratteristiche_selezione == DAVANTI_PEZZO) {
                        entrambi = true;
                    }
                    caratteristiche_selezione = DAVANTI_BASE;
                    distanza = buffer[loop * 4 + 1];
                    x_base_selezionata = pos_x_griglia + ((buffer[loop * 4 + 3] - 11) / 3 - 1);
                    y_base_selezionata = pos_y_griglia + ((buffer[loop * 4 + 3] - 11) % 3 - 1);
                }
            }
        }
    }
    return 0;
}

