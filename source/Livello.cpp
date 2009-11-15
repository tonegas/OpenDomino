/* 
 * File:   Livello.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 16.03
 */

#include "../include/Domino.h"


using namespace std;

Livello::Livello(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux) :
griglia_livello(num_x_colonne_aux, num_y_righe_aux) {
    gioco = gioco_aux;

    bottone_destro = false;
    bottone_sinistro = false;
    bottone_centrale = false;
    tipo_proiezione = ASSIONOMETRICA;

    caratteristiche_selezione = NIENTE;
    entrambi = false;

    //---------------------- da togliere
    //    angolo_telecamera_x = 0;
    //    angolo_telecamera_y = 0;
    //    delta_zoom = DELTA_ZOOM;
    //    tempo_reset_delta_zoom = 0;
    //    mouvi_zoom = false;
}

Livello::Livello(const Livello& orig) :
griglia_livello(orig.griglia_livello) {
    gioco = orig.gioco;

    bottone_destro = orig.bottone_destro;
    bottone_sinistro = orig.bottone_sinistro;
    bottone_centrale = orig.bottone_centrale;
    tipo_proiezione = orig.tipo_proiezione;

    //!!!!!!!!!!!!!!!!!!!!!!!
    tele_assio = orig.tele_assio;
    tele_prosp = orig.tele_prosp;
    //!!!!!!!!!!!!!!!!!!!!!!!!!

    caratteristiche_selezione = NIENTE;
    entrambi = false;
    inizializza();

    //??????????????????????? da togliere
    //    angolo_telecamera_x = orig.angolo_telecamera_x;
    //    angolo_telecamera_y = orig.angolo_telecamera_y;
    //
    //    delta_zoom = DELTA_ZOOM;
    //    tempo_reset_delta_zoom = 0;
    //    mouvi_zoom = false;
    //
    //    aux_griglia = orig.aux_griglia;
    //    griglia_assionometrica = orig.griglia_assionometrica;
    //    griglia_prospettica = orig.griglia_prospettica;
    //?????????????????????????
}

int Livello::inizializza() {
    //!!!!!!!!!!!!!!!!!!!!!!!!
    int aux_mx, aux_my;
    switch (tipo_proiezione) {
        case ASSIONOMETRICA:
            telecamera_attuale = &tele_assio;
            break;
        case PROSPETTICA:
            telecamera_attuale = &tele_prosp;
            break;
    }
    //qui c'è il problema che il puntatore è constante
    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
    SDL_GetMouseState(&aux_mx, &aux_my);
    telecamera_attuale->getMousePosGrigliaXY(aux_mx, aux_my, griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
    mouseMotion();
    //!!!!!!!!!!!!!!!!!!!!!!!!1
    //?????????????????????????????
    //    setProiezione(tipo_proiezione, gioco->getWindowL(), gioco->getWindowA(), true);
    //?????????????????????????????
    return 1;
}

//void Livello::setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin, bool reset) {
//    glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
//    switch (tipo) {
//        case ASSIONOMETRICA:
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            glOrtho(0, (GLfloat) larghezza_fin,
//                    0, (GLfloat) altezza_fin,
//                    ZNEAR, ZFAR); //misure rispetto alla posizione dell'occhio
//            glMultMatrixf(cavalier);
//
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
//            gluLookAt(
//                    -400.0, -400.0, H_TELECAMERA, /* eye  */
//                    -400.0, -400.0, 0.0, /* center  */
//                    0.0, 1.0, 0.0); /* up is in positive Y direction */
//            if (reset) {
//                max_zoom = MAX_ZOOM_ASSIONOMETRIA;
//                min_zoom = MIN_ZOOM_ASSIONOMETRIA;
//                tipo_proiezione = tipo;
//            }
//            if (tipo_proiezione != tipo) {
//                griglia_prospettica = griglia_livello.getGriglia();
//                griglia_livello.setGrigliaXY(griglia_assionometrica.x, griglia_assionometrica.y);
//                griglia_livello.setGrigliaZoom(griglia_assionometrica.zoom);
//                max_zoom = MAX_ZOOM_ASSIONOMETRIA;
//                min_zoom = MIN_ZOOM_ASSIONOMETRIA;
//                tipo_proiezione = tipo;
//            }
//            break;
//        case PROSPETTICA:
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
//            gluPerspective(FOVY, (GLfloat) larghezza_fin / (GLfloat) altezza_fin, ZNEAR, ZFAR);
//
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();
//            gluLookAt(
//                    0.0, 0.0, H_TELECAMERA, /* eye  */
//                    0.0, 0.0, 0.0, /* center  */
//                    0.0, 1.0, 0.0); /* up is in positive Y direction */
//            if (reset) {
//                max_zoom = MAX_ZOOM_PROSPETTICA;
//                min_zoom = MIN_ZOOM_PROSPETTICA;
//                tipo_proiezione = tipo;
//            }
//            if (tipo_proiezione != tipo) {
//                griglia_assionometrica = griglia_livello.getGriglia();
//                griglia_livello.setGrigliaXY(griglia_prospettica.x, griglia_prospettica.y);
//                griglia_livello.setGrigliaZoom(griglia_prospettica.zoom);
//                max_zoom = MAX_ZOOM_PROSPETTICA;
//                min_zoom = MIN_ZOOM_PROSPETTICA;
//                tipo_proiezione = tipo;
//            }
//            break;
//    }
//
//    glGetIntegerv(GL_VIEWPORT, matrice_view);
//    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
//    glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);
//
//    //resetto il movimento dello zoom
//    mouvi_zoom = false;
//
//    //recupero pa posizione z della superfice
//    GLdouble mouse_x, mouse_y;
//    gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &mouse_z_fin_double);
//}
//
//bool Livello::getMousePosGrigliaXY(int altezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux) {
//    mouse_x_fin = mouse_x_fin_aux;
//    mouse_y_fin = mouse_y_fin_aux;
//    return getMousePosGrigliaXY(altezza_fin);
//}
//
//bool Livello::getMousePosGrigliaXY(int altezza_fin) {
//    if (tipo_proiezione == ASSIONOMETRICA) {
//        gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, mouse_z_fin_double, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
//        pos_x_griglia = ((pos_x - griglia_livello.getGriglia().x) / griglia_livello.getGriglia().zoom);
//        pos_y_griglia = ((pos_y - griglia_livello.getGriglia().y) / griglia_livello.getGriglia().zoom);
//        indice_x_griglia = (unsigned) (pos_x_griglia / (GLfloat) ALTEZZA_PEZZO);
//        indice_y_griglia = (unsigned) (pos_y_griglia / (GLfloat) ALTEZZA_PEZZO);
//        if (indice_x_griglia < griglia_livello.getDimGrigliaX() && indice_y_griglia < griglia_livello.getDimGrigliaY()) {
//            indice_griglia_ok = true;
//        } else {
//            indice_griglia_ok = false;
//        }
//    } else {
//        GLuint buffer[512]; // Set Up A Selection Buffer
//        GLint hits;
//        glSelectBuffer(512, buffer);
//        glRenderMode(GL_SELECT);
//        glInitNames();
//        glPushName(0);
//        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
//        {
//            glLoadIdentity();
//            gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (altezza_fin - mouse_y_fin), 1.0f, 1.0f, matrice_view);
//            gluPerspective(FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), ZNEAR, ZFAR);
//            glMatrixMode(GL_MODELVIEW);
//            glPushMatrix();
//            {
//                glLoadName(0);
//                glRotatef(angolo_telecamera_y, 1, 0, 0);
//                glRotatef(-angolo_telecamera_x, 0, 1, 0);
//                glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
//                glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
//                glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model_griglia);
//                glBegin(GL_QUADS);
//                {
//                    glNormal3f(0.0, 0.0, 1.0);
//                    glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
//                    glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
//                    glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
//                    glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
//                }
//                glEnd();
//            }
//            glPopMatrix();
//            glMatrixMode(GL_PROJECTION);
//        }
//        glPopMatrix();
//        glMatrixMode(GL_MODELVIEW);
//        hits = glRenderMode(GL_RENDER);
//        if (hits > 0) // If There Were More Than 0 Hits
//        {
//            //int choose = buffer[3]; // Make Our Selection The First Object
//            GLuint depth = buffer[2]; // Store How Far Away It Is
//            //cout << "depth:" << (GLfloat) depth / (GLfloat) (GLuint) (-1) << '\t' << superfice_z << '\n' << flush;
//            gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, (GLdouble) depth / (GLdouble) (GLuint) (-1), matrice_model_griglia, matrice_proj, matrice_view, &pos_x_griglia, &pos_y_griglia, &pos_z_griglia);
//            indice_x_griglia = pos_x_griglia / (GLfloat) ALTEZZA_PEZZO;
//            indice_y_griglia = pos_y_griglia / (GLfloat) ALTEZZA_PEZZO;
//            if (indice_x_griglia < griglia_livello.getDimGrigliaX() && indice_y_griglia < griglia_livello.getDimGrigliaY()) {
//                indice_griglia_ok = true;
//            } else {
//                indice_griglia_ok = false;
//            }
//        } else {
//            indice_griglia_ok = false;
//        }
//        gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, mouse_z_fin_double, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
//    }
//    return indice_griglia_ok;
//}

//int Livello::mouseSelezione(int altezza_fin) {
//    GLuint buffer[512]; // Set Up A Selection Buffer
//    GLint hits = 0;
//    glSelectBuffer(512, buffer);
//    glRenderMode(GL_SELECT);
//    glInitNames();
//    glPushName(0);
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    {
//        glLoadIdentity();
//        gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (altezza_fin - mouse_y_fin), 1.0f, 1.0f, matrice_view);
//        if (tipo_proiezione == PROSPETTICA) {
//            gluPerspective(FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), ZNEAR, ZFAR);
//        } else {
//            glOrtho(0, (GLfloat) (matrice_view[2] - matrice_view[0]), 0, (GLfloat) altezza_fin, ZNEAR, ZFAR);
//            glMultMatrixf(cavalier);
//        }
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        {
//
//            if (tipo_proiezione == PROSPETTICA) {
//                glRotatef(angolo_telecamera_y, 1, 0, 0);
//                glRotatef(-angolo_telecamera_x, 0, 1, 0);
//            }
//            glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
//            glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
//            int indice = 1;
//            for (int i = -1; i < 2; i++) {
//                for (int j = -1; j < 2; j++) {
//                    if ((int) indice_x_griglia + i >= 0 && (int) indice_x_griglia + i < (int) griglia_livello.getDimGrigliaX() && (int) indice_y_griglia + j >= 0 && (int) indice_y_griglia + j < (int) griglia_livello.getDimGrigliaY()) {
//                        if (griglia_livello.getOccupato(indice_x_griglia + i, indice_y_griglia + j)) {
//                            if (griglia_livello.getTipo(indice_x_griglia + i, indice_y_griglia + j) == ELEM_PEZZO) {
//                                glLoadName((i + 1) * 3 + (j + 1) + 1);
//                                Pezzo::stampaPezzoCollisione(indice_x_griglia + i, indice_y_griglia + j);
//                            } else {
//                                glLoadName(11 + (i + 1) * 3 + (j + 1));
//                                Base::stampaBaseCollisione(indice_x_griglia + i, indice_y_griglia + j);
//                            }
//                        } else {
//                            glLoadName((i + 1) * 3 + (j + 1) + 1);
//                            Pezzo::stampaPezzoCollisione(indice_x_griglia + i, indice_y_griglia + j);
//                            glLoadName(11 + (i + 1) * 3 + (j + 1));
//                            Base::stampaBaseCollisione(indice_x_griglia + i, indice_y_griglia + j);
//                        }
//                        indice++;
//                    }
//                }
//            }
//        }
//        glPopMatrix();
//        glMatrixMode(GL_PROJECTION);
//    }
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    hits = glRenderMode(GL_RENDER);
//    caratteristiche_selezione = NIENTE;
//    if (hits > 0) // If There Were More Than 0 Hits
//    {
//        unsigned distanza = -1;
//        entrambi = false;
//        for (int loop = 0; loop < hits; loop++) {
//            if (buffer[loop * 4 + 3] < 10) {
//                if (distanza > buffer[loop * 4 + 1]) {
//                    if (caratteristiche_selezione == DAVANTI_BASE) {
//                        entrambi = true;
//                    }
//                    caratteristiche_selezione = DAVANTI_PEZZO;
//                    distanza = buffer[loop * 4 + 1];
//                    x_pezzo_selezionato = indice_x_griglia + ((buffer[loop * 4 + 3] - 1) / 3 - 1);
//                    y_pezzo_selezionato = indice_y_griglia + ((buffer[loop * 4 + 3] - 1) % 3 - 1);
//                }
//            } else {
//                if (distanza > buffer[loop * 4 + 1]) {
//                    if (caratteristiche_selezione == DAVANTI_PEZZO) {
//                        entrambi = true;
//                    }
//                    caratteristiche_selezione = DAVANTI_BASE;
//                    distanza = buffer[loop * 4 + 1];
//                    x_base_selezionata = indice_x_griglia + ((buffer[loop * 4 + 3] - 11) / 3 - 1);
//                    y_base_selezionata = indice_y_griglia + ((buffer[loop * 4 + 3] - 11) % 3 - 1);
//                }
//            }
//        }
//    }
//    return 0;
//}

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
                    telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    mouseMotion();
                    //?????????????????????
                    //                    setProiezione(PROSPETTICA, gioco->getWindowL(), gioco->getWindowA());
                    break;
                case SDLK_a:
                    telecamera_attuale = &tele_assio;
                    tipo_proiezione = ASSIONOMETRICA;
                    telecamera_attuale->setProiezioneTelecamera(gioco->getWindowL(), gioco->getWindowA());
                    telecamera_attuale->getMousePosGrigliaXY(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
                    mouseMotion();
                    //bisogna recuperare la posizione del mouse in maniera che sia aggiornata
                    //poi bisogna chiamare getMouseGrigliaXY()
                    //così la selezione del pezzo si aggiorna
                    //?????????????????????
                    //                    setProiezione(ASSIONOMETRICA, gioco->getWindowL(), gioco->getWindowA());
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
            telecamera_attuale->getMousePosGrigliaXY(evento->button.x, evento->button.y, griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
            //????????????????????????
            //            getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
            //????????????????????????
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                //!!!!!!!!!!
                telecamera_attuale->registraPosizione();
                //!!!!!!!!!!
                //???????????????
                //                pos_x_iniziali = pos_x;
                //                pos_y_iniziali = pos_y;
                //                aux_griglia.x = griglia_livello.getGriglia().x;
                //                aux_griglia.y = griglia_livello.getGriglia().y;
                //                aux_griglia.zoom = griglia_livello.getGriglia().zoom;
                //???????????????
                bottone_destro = true;
            }
            if (!bottone_destro && (evento->button.button == SDL_BUTTON_WHEELUP || evento->button.button == SDL_BUTTON_WHEELDOWN)) {
                if (evento->button.button == SDL_BUTTON_WHEELUP) {
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    telecamera_attuale->registraZoomAvanti();
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //????????????????????????????????????
                    //                    GLfloat zoom = griglia_livello.getGriglia().zoom;
                    //                    if (zoom < max_zoom) {
                    //                        if (zoom * delta_zoom < max_zoom) {
                    //                            aux_griglia.zoom = zoom * delta_zoom;
                    //                            aux_griglia.x = griglia_livello.getGriglia().x + (1 - delta_zoom)*(pos_x - griglia_livello.getGriglia().x);
                    //                            aux_griglia.y = griglia_livello.getGriglia().y + (1 - delta_zoom)*(pos_y - griglia_livello.getGriglia().y);
                    //                            delta_zoom *= INCREMENTO_DELTA_ZOOM;
                    //                        } else {
                    //                            delta_zoom = DELTA_ZOOM;
                    //                            aux_griglia.zoom = max_zoom;
                    //                            aux_griglia.x = griglia_livello.getGriglia().x + (1 - (GLfloat) max_zoom / zoom)*(pos_x - griglia_livello.getGriglia().x);
                    //                            aux_griglia.y = griglia_livello.getGriglia().y + (1 - (GLfloat) max_zoom / zoom)*(pos_y - griglia_livello.getGriglia().y);
                    //                        }
                    //                        mouvi_zoom = true;
                    //                    }
                    //??????????????????????????????????????
                } else {
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    telecamera_attuale->registraZoomIndietro();
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    //??????????????????????????????????????
                    //                    GLfloat zoom = griglia_livello.getGriglia().zoom;
                    //                    if (zoom > min_zoom) {
                    //                        if (zoom / delta_zoom > min_zoom) {
                    //                            aux_griglia.zoom = zoom / delta_zoom;
                    //                            aux_griglia.x = griglia_livello.getGriglia().x + ((delta_zoom - 1) / delta_zoom)*(pos_x - griglia_livello.getGriglia().x);
                    //                            aux_griglia.y = griglia_livello.getGriglia().y + ((delta_zoom - 1) / delta_zoom)*(pos_y - griglia_livello.getGriglia().y);
                    //                            delta_zoom *= INCREMENTO_DELTA_ZOOM;
                    //                        } else {
                    //                            delta_zoom = DELTA_ZOOM;
                    //                            aux_griglia.zoom = min_zoom;
                    //                            aux_griglia.x = griglia_livello.getGriglia().x + (((zoom / (GLfloat) min_zoom) - 1) / (zoom / (GLfloat) min_zoom))*(pos_x - griglia_livello.getGriglia().x);
                    //                            aux_griglia.y = griglia_livello.getGriglia().y + (((zoom / (GLfloat) min_zoom) - 1) / (zoom / (GLfloat) min_zoom))*(pos_y - griglia_livello.getGriglia().y);
                    //                        }
                    //                        mouvi_zoom = true;
                    //                    }
                    //??????????????????????????????????????
                }
            }
            if (!bottone_destro && evento->button.button == SDL_BUTTON_MIDDLE && tipo_proiezione == PROSPETTICA) {
                //!!!!!!!!!!
                telecamera_attuale->registraPosizione();
                //!!!!!!!!!!
                bottone_centrale = true;
                //??????????????????
                //                angolo_telecamera_x_iniziale = angolo_telecamera_x;
                //                angolo_telecamera_y_iniziale = angolo_telecamera_y;
                //                pos_x_iniziali = pos_x;
                //                pos_y_iniziali = pos_y;
                //?????????????????
            }
            mouseButtonDown(evento);
            break;
        case SDL_MOUSEMOTION:
            telecamera_attuale->getMousePosGrigliaXY(evento->button.x, evento->button.y, griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
            //??????????????????????????
            //            getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
            //??????????????????????????
            if (bottone_destro) {
                //!!!!!!!!!!!!!!!!!
                telecamera_attuale->cambiaXY();
                //!!!!!!!!!!!!!!!!!
                //??????????????
                //                griglia_livello.setGrigliaXY(aux_griglia.x + (pos_x - pos_x_iniziali), aux_griglia.y + (pos_y - pos_y_iniziali));
                //?????????????
            }
            if (bottone_centrale) {
                //!!!!!!!!!!!!!!!!!!!!!!!
                telecamera_attuale->cambiaAngolazione();
                //!!!!!!!!!!!!!!!!!!!!!!!
                //?????????????????????????????????
                //                GLfloat nuovo_angolo_x = angolo_telecamera_x_iniziale + (pos_x_iniziali - pos_x);
                //                GLfloat nuovo_angolo_y = angolo_telecamera_y_iniziale + (pos_y_iniziali - pos_y);
                //                if (fabs(nuovo_angolo_x) < MAX_ANGOLO_TELECAMERA_XY) {
                //                    angolo_telecamera_x = nuovo_angolo_x;
                //                } else {
                //                    if (angolo_telecamera_x < 0)
                //                        angolo_telecamera_x = -MAX_ANGOLO_TELECAMERA_XY;
                //                    else
                //                        angolo_telecamera_x = MAX_ANGOLO_TELECAMERA_XY;
                //                }
                //                if (fabs(nuovo_angolo_y) < MAX_ANGOLO_TELECAMERA_XY) {
                //                    angolo_telecamera_y = nuovo_angolo_y;
                //                } else {
                //                    if (nuovo_angolo_y < 0)
                //                        angolo_telecamera_y = -MAX_ANGOLO_TELECAMERA_XY;
                //                    else
                //                        angolo_telecamera_y = MAX_ANGOLO_TELECAMERA_XY;
                //                }
                //???????????????????????????
            }
            mouseMotion();
            break;
        case SDL_MOUSEBUTTONUP:
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                bottone_destro = false;
            }
            if (evento->button.button == SDL_BUTTON_MIDDLE) {
                bottone_centrale = false;
            }
            mouseButtonUp(evento);
            break;
        case SDL_VIDEORESIZE:
            gioco->setWindowLA(evento->resize.w, evento->resize.h);
            //!!!!!!!!!!!!!!
            telecamera_attuale->setProiezioneTelecamera(evento->resize.w, evento->resize.h);
            //!!!!!!!!!!!!!!!!
            //?????????????????????
            //            setProiezione(tipo_proiezione, evento->resize.w, evento->resize.h);
            //????????????????????
        default:
            break;
    }
}

void Livello::aggiornaPosizioneGriglia() {
    //!!!!!!!!!!!!!!!!!!!!1
    telecamera_attuale->animaZoom();
    //!!!!!!!!!!!!!!!!!!!!
    //???????????????????
    //    if (mouvi_zoom) {
    //        if (fabs(griglia_livello.getGriglia().zoom - aux_griglia.zoom) >= 0.001) {
    //            griglia_livello.setGrigliaXY(griglia_livello.getGriglia().x + ((aux_griglia.x - griglia_livello.getGriglia().x) / 10),
    //                    griglia_livello.getGriglia().y + ((aux_griglia.y - griglia_livello.getGriglia().y) / 10));
    //
    //            griglia_livello.setGrigliaZoom(griglia_livello.getGriglia().zoom + (aux_griglia.zoom - griglia_livello.getGriglia().zoom) / 10);
    //        } else {
    //            mouvi_zoom = false;
    //            griglia_livello.setGrigliaXY(aux_griglia.x, aux_griglia.y);
    //            griglia_livello.setGrigliaZoom(aux_griglia.zoom);
    //        }
    //    }
    //???????????????????

    //!!!!!!!!!!!!!!!!!!!!!
    telecamera_attuale->controlloPosizione(griglia_livello.getDimGrigliaX(), griglia_livello.getDimGrigliaY());
    //!!!!!!!!!!!!!!!!!!!!
    //??????????????????????
    //    if (griglia_livello.getGriglia().x > 0) {
    //        griglia_livello.setGrigliaXY(0, griglia_livello.getGriglia().y);
    //    } else {
    //        if (griglia_livello.getGriglia().x < -(GLdouble) (griglia_livello.num_x_colonne * ALTEZZA_PEZZO) * griglia_livello.getGriglia().zoom) {
    //            griglia_livello.setGrigliaXY(-(GLdouble) (griglia_livello.num_x_colonne * ALTEZZA_PEZZO) * griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().y);
    //        }
    //    }
    //    if (griglia_livello.getGriglia().y > 0) {
    //        griglia_livello.setGrigliaXY(griglia_livello.getGriglia().x, 0);
    //    } else {
    //        if (griglia_livello.getGriglia().y < -(GLdouble) (griglia_livello.num_y_righe * ALTEZZA_PEZZO) * griglia_livello.getGriglia().zoom) {
    //            griglia_livello.setGrigliaXY(griglia_livello.getGriglia().x, -(GLdouble) (griglia_livello.num_y_righe * ALTEZZA_PEZZO) * griglia_livello.getGriglia().zoom);
    //        }
    //    }
    //????????????????????????
    //!!!!!!!!!!!!!!!!!
    telecamera_attuale->resettaDeltaZoom(gioco->getFrames());
    //!!!!!!!!!!!!!!!!!
    //?????????????????
    //    if (delta_zoom > DELTA_ZOOM) {
    //        tempo_reset_delta_zoom++;
    //        if (tempo_reset_delta_zoom == (1000 / gioco->getFrames())) {
    //            tempo_reset_delta_zoom = 0;
    //            delta_zoom = DELTA_ZOOM;
    //        }
    //    }
    //?????????????????
}

void Livello::cicloGioco(SDL_Event *evento) {
    SDL_PumpEvents();
    while (SDL_PollEvent(evento)) {
        gestisciInput(evento);
    }

    aggiornaPosizioneGriglia();

    attivaSelezioni();

    glPushMatrix();

    stampaSfondo();

    //!!!!!!!!!!!!!!!!
    telecamera_attuale->visualeOpenGL();
    //!!!!!!!!!!!!!!!!!
    //???????????????????????
    //    if (tipo_proiezione == PROSPETTICA) {
    //        glRotatef(angolo_telecamera_y, 1, 0, 0);
    //        glRotatef(-angolo_telecamera_x, 0, 1, 0);
    //    }
    //    //STO inserendo la pallina per colpire gli oggetti ma manca la struttura dati di supporto
    //    //Poi devo recuperare il caricatore del ds e del computer che fava che sono!
    //    glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
    //    glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
    //???????????????????????

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
    static GLfloat colorblue [] = {0.0f, 0.0f, 1.0f, 0.7f};
    static GLfloat lightpos_ambient[] = {60, 120, 150, 0.0};
    static GLfloat colorwhite [] = {1.0f, 1.0f, 1.0f, 1.0f};
    static GLfloat colorwhite2 [] = {0.1f, 0.1f, 0.1f, 0.5f};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, colorwhite);
    glLightfv(GL_LIGHT1, GL_AMBIENT, colorwhite2);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos_ambient);
    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorblue);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorblue);
    glTranslatef(0.0, 0.0, POSIZIONE_SUPERFICE);
    //glColor3f(1.0f, 1.0f, 0.0f);
    //glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_PEZZO]);
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0f, 0.0f), glVertex3f(-ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glTexCoord2f(1.0f, 0.0f), glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, -ALTEZZA_PEZZO, 0);
        glTexCoord2f(1.0f, 1.0f), glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
        glTexCoord2f(0.0f, 1.0f), glVertex3f(-ALTEZZA_PEZZO, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO, 0);
    }
    glEnd();
    glPopMatrix();
}

void Livello::stampaSfondo() {
    glClearColor(37.0 / 255.0, 104.0 / 255.0, 246.0 / 255.0, 1.0f);

    //    static GLfloat cieloAzzurro [] = {37.0 / 255.0, 104.0 / 255.0, 246.0 / 255.0, 1.0f};
    //    glPushMatrix();
    //    glDisable(GL_LIGHTING);
    //    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cieloAzzurro);
    //    //glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, colorblue);
    //    glTranslatef(0.0, 0.0, -1000.0);
    //    glColor4fv(cieloAzzurro);
    //    //glBindTexture(GL_TEXTURE_2D, indice_texture[TEX_PEZZO]);
    //    glBegin(GL_QUADS);
    //    {
    //        glNormal3f(0.0, 0.0, 1.0);
    //        glVertex3f(-10000.0, -10000.0, 0.0);
    //        glVertex3f(-1000.0, 10000.0, 0.0);
    //        glVertex3f(10000.0, 10000.0, 0.0);
    //        glVertex3f(10000.0, -10000.0, 0.0);
    //
    //    }
    //    glEnd();
    //    glEnable(GL_LIGHTING);
    //    glPopMatrix();
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
    cout << "pezzo:" << x_pezzo_selezionato << ' ' << y_pezzo_selezionato << '\n' << flush;
}

void Livello::selezioneDavantiBase(unsigned aux_x_base_selezionata, unsigned aux_y_base_selezionata) {
    if (caratteristiche_selezione == DAVANTI_PEZZO) {
        entrambi = true;
    }
    caratteristiche_selezione = DAVANTI_BASE;
    x_base_selezionata = aux_x_base_selezionata;
    y_base_selezionata = aux_y_base_selezionata;
    cout << "base:" << x_base_selezionata << ' ' << y_base_selezionata << '\n' << flush;

}