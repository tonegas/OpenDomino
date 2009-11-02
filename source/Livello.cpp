/* 
 * File:   Livello.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 16.03
 */

#include "../include/Livello.h"
#include "../include/Gioco.h"

using namespace std;

Livello::Livello(int num_x_colonne_aux, int num_y_righe_aux, int frame_rate_aux) :
griglia_livello(num_x_colonne_aux, num_y_righe_aux) {
    bottone_destro = false;
    bottone_sinistro = false;
    bottone_centrale = false;
    angolo_telecamera_x = 0;
    angolo_telecamera_y = 0;

    frame_rate = frame_rate_aux;
    delta_zoom = DELTA_ZOOM;
    tempo_reset_delta_zoom = 0;
    mouvi_zoom = false;
}

Livello::Livello(const Livello& orig) :
griglia_livello(orig.griglia_livello.getDimGrigliaX(), orig.griglia_livello.getDimGrigliaY()) {
    bottone_destro = orig.bottone_destro;
    bottone_sinistro = orig.bottone_sinistro;
    bottone_centrale = orig.bottone_centrale;
    angolo_telecamera_x = orig.angolo_telecamera_x;
    angolo_telecamera_y = orig.angolo_telecamera_y;

    frame_rate = orig.frame_rate;
    delta_zoom = DELTA_ZOOM;
    tempo_reset_delta_zoom = 0;
    mouvi_zoom = false;
}

bool Livello::getMousePosGrigliaXY(int larghezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux) {
    mouse_x_fin = mouse_x_fin_aux;
    mouse_y_fin = mouse_y_fin_aux;
    return getMousePosGrigliaXY(larghezza_fin);
}

bool Livello::getMousePosGrigliaXY(int altezza_fin) {
    if (tipo_proiezione == ASSIONOMETRICA) {
        gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, superfice_z, matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
        pos_x_griglia = (int) (((pos_x - griglia_livello.getGriglia().x) / griglia_livello.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
        pos_y_griglia = (int) (((pos_y - griglia_livello.getGriglia().y) / griglia_livello.getGriglia().zoom) / (GLfloat) ALTEZZA_PEZZO);
        if (pos_x_griglia >= 0 && pos_y_griglia >= 0 && (unsigned) pos_x_griglia < griglia_livello.getDimGrigliaX() && (unsigned) pos_y_griglia < griglia_livello.getDimGrigliaY()) {
            pos_griglia_ok = true;
        } else {
            pos_griglia_ok = false;
        }
    } else {
        GLuint buffer[512]; // Set Up A Selection Buffer
        GLint hits;
        glSelectBuffer(512, buffer);
        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        {
            glLoadIdentity();
            gluPickMatrix((GLdouble) mouse_x_fin, (GLdouble) (altezza_fin - mouse_y_fin), 1.0f, 1.0f, matrice_view);
            gluPerspective(FOVY, (GLfloat) (matrice_view[2] - matrice_view[0]) / (GLfloat) (matrice_view[3] - matrice_view[1]), ZNEAR, ZFAR);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            {
                glLoadName(0);
                glRotatef(angolo_telecamera_y, 1, 0, 0);
                glRotatef(-angolo_telecamera_x, 0, 1, 0);
                glTranslatef(griglia_livello.getGriglia().x, griglia_livello.getGriglia().y, 0);
                glScalef(griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom, griglia_livello.getGriglia().zoom);
                glBegin(GL_QUADS);
                {
                    glNormal3f(0.0, 0.0, 1.0);
                    glVertex3f(-ALTEZZA_PEZZO*10, -ALTEZZA_PEZZO*10, 0);
                    glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO*10, -ALTEZZA_PEZZO*10, 0);
                    glVertex3f(griglia_livello.getDimGrigliaX() * ALTEZZA_PEZZO + ALTEZZA_PEZZO*10, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO*10, 0);
                    glVertex3f(-ALTEZZA_PEZZO*10, griglia_livello.getDimGrigliaY() * ALTEZZA_PEZZO + ALTEZZA_PEZZO*10, 0);
                }
                glEnd();
            }
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
        }
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        hits = glRenderMode(GL_RENDER);
        if (hits > 0) // If There Were More Than 0 Hits
        {
            //int choose = buffer[3]; // Make Our Selection The First Object
            GLuint depth = buffer[2]; // Store How Far Away It Is
            //cout << "depth:" << (GLfloat) depth / (GLfloat) (GLuint) (-1) << '\t' << superfice_z << '\n' << flush;
            gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, (GLdouble) depth / (GLdouble) (GLuint) (-1), matrice_model_griglia, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
            pos_x_griglia = pos_x / (GLfloat) ALTEZZA_PEZZO;
            pos_y_griglia = pos_y / (GLfloat) ALTEZZA_PEZZO;
            if (pos_x_griglia >= 0 && pos_y_griglia >= 0 && (unsigned) pos_x_griglia < griglia_livello.getDimGrigliaX() && (unsigned) pos_y_griglia < griglia_livello.getDimGrigliaY()) {
                pos_griglia_ok = true;
            } else {
                pos_griglia_ok = false;
            }
            gluUnProject(mouse_x_fin, altezza_fin - mouse_y_fin, (GLdouble) depth / (GLdouble) (GLuint) (-1), matrice_model, matrice_proj, matrice_view, &pos_x, &pos_y, &pos_z);
        } else {
            pos_griglia_ok = false;
        }
    }
    return pos_griglia_ok;
}

void Livello::setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin) {
    glViewport(0, 0, (GLint) larghezza_fin, (GLint) altezza_fin);
    switch (tipo) {
        case ASSIONOMETRICA:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, (GLfloat) larghezza_fin,
                    0, (GLfloat) altezza_fin,
                    ZNEAR, ZFAR); //misure rispetto alla posizione dell'occhio
            glMultMatrixf(cavalier);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(
                    0.0, 0.0, H_TELECAMERA, /* eye  */
                    0.0, 0.0, 0.0, /* center  */
                    0.0, 1.0, 0.0); /* up is in positive Y direction */
            if (tipo_proiezione != tipo) {
                griglia_prospettica = griglia_livello.getGriglia();
                griglia_livello.setGrigliaXY(griglia_assionometrica.x, griglia_assionometrica.y);
                griglia_livello.setGrigliaZoom(griglia_assionometrica.zoom);
                max_zoom = MAX_ZOOM_ASSIONOMETRIA;
                min_zoom = MIN_ZOOM_ASSIONOMETRIA;
                tipo_proiezione = tipo;
            }
            break;
        case PROSPETTICA:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(FOVY, (GLfloat) larghezza_fin / (GLfloat) altezza_fin, ZNEAR, ZFAR);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(
                    0.0, 0.0, H_TELECAMERA, /* eye  */
                    0.0, 0.0, 0.0, /* center  */
                    0.0, 1.0, 0.0); /* up is in positive Y direction */
            if (tipo_proiezione != tipo) {
                griglia_assionometrica = griglia_livello.getGriglia();
                griglia_livello.setGrigliaXY(griglia_prospettica.x, griglia_prospettica.y);
                griglia_livello.setGrigliaZoom(griglia_prospettica.zoom);
                max_zoom = MAX_ZOOM_PROSPETTICA;
                min_zoom = MIN_ZOOM_PROSPETTICA;
                tipo_proiezione = tipo;
            }
            break;
    }

    glGetIntegerv(GL_VIEWPORT, matrice_view);
    glGetDoublev(GL_MODELVIEW_MATRIX, matrice_model);
    glGetDoublev(GL_PROJECTION_MATRIX, matrice_proj);

    //resetto il movimento dello zoom
    mouvi_zoom = false;

    //recupero pa posizione z della superfice
    GLdouble mouse_x, mouse_y;
    gluProject(0.0, 0.0, 0.0, matrice_model, matrice_proj, matrice_view, &mouse_x, &mouse_y, &superfice_z);
}

int Livello::aggiornaStato() {
    //così fa schifo va sistemato non è possibile che ogni volta devo settare anche l'aux altrimenti mi si sposta tutto è meglio se faccio un booleano
    if (mouvi_zoom) {
        if (fabs(griglia_livello.getGriglia().zoom - aux_griglia.zoom) >= 0.001) {
            griglia_livello.setGrigliaXY(griglia_livello.getGriglia().x + ((aux_griglia.x - griglia_livello.getGriglia().x) / 10),
                    griglia_livello.getGriglia().y + ((aux_griglia.y - griglia_livello.getGriglia().y) / 10));

            griglia_livello.setGrigliaZoom(griglia_livello.getGriglia().zoom + (aux_griglia.zoom - griglia_livello.getGriglia().zoom) / 10);
        } else {
            mouvi_zoom = false;
            griglia_livello.setGrigliaXY(aux_griglia.x, aux_griglia.y);
            griglia_livello.setGrigliaZoom(aux_griglia.zoom);
        }
    }
    if (delta_zoom > DELTA_ZOOM) {
        tempo_reset_delta_zoom++;
        if (tempo_reset_delta_zoom == frame_rate) {
            tempo_reset_delta_zoom = 0;
            delta_zoom = DELTA_ZOOM;
        }
    }
    return 1;
}

int Livello::gestisciInput(SDL_Event *evento) {
    if (evento->type == SDL_QUIT) {
        gioco->gameExit();
        return 0;
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
                case SDLK_PAGEDOWN:
                    gioco->setFrames(gioco->getFrames() + 1);
                    break;
                case SDLK_p:
                    setProiezione(PROSPETTICA, gioco->getWindowL(), gioco->getWindowA());
                    break;
                case SDLK_a:
                    setProiezione(ASSIONOMETRICA, gioco->getWindowL(), gioco->getWindowA());
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
                default:
                    break;

            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                pos_x_iniziali = pos_x;
                pos_y_iniziali = pos_y;
                aux_griglia.x = griglia_livello.getGriglia().x;
                aux_griglia.y = griglia_livello.getGriglia().y;
                aux_griglia.zoom = griglia_livello.getGriglia().zoom;
                bottone_destro = true;
            }
            if (!bottone_destro && (evento->button.button == SDL_BUTTON_WHEELUP || evento->button.button == SDL_BUTTON_WHEELDOWN)) {
                if (evento->button.button == SDL_BUTTON_WHEELUP) {
                    GLfloat zoom = griglia_livello.getGriglia().zoom;
                    if (zoom < max_zoom) {
                        if (zoom * delta_zoom < max_zoom) {
                            aux_griglia.zoom = zoom * delta_zoom;
                            aux_griglia.x = griglia_livello.getGriglia().x + (1 - delta_zoom)*(pos_x - griglia_livello.getGriglia().x);
                            aux_griglia.y = griglia_livello.getGriglia().y + (1 - delta_zoom)*(pos_y - griglia_livello.getGriglia().y);
                            delta_zoom *= INCREMENTO_DELTA_ZOOM;
                        } else {
                            delta_zoom = DELTA_ZOOM;
                            aux_griglia.zoom = max_zoom;
                            aux_griglia.x = griglia_livello.getGriglia().x + (1 - (GLfloat) max_zoom / zoom)*(pos_x - griglia_livello.getGriglia().x);
                            aux_griglia.y = griglia_livello.getGriglia().y + (1 - (GLfloat) max_zoom / zoom)*(pos_y - griglia_livello.getGriglia().y);
                        }
                        mouvi_zoom = true;
                    }
                } else {
                    GLfloat zoom = griglia_livello.getGriglia().zoom;
                    if (zoom > min_zoom) {
                        if (zoom / delta_zoom > min_zoom) {
                            aux_griglia.zoom = zoom / delta_zoom;
                            aux_griglia.x = griglia_livello.getGriglia().x + ((delta_zoom - 1) / delta_zoom)*(pos_x - griglia_livello.getGriglia().x);
                            aux_griglia.y = griglia_livello.getGriglia().y + ((delta_zoom - 1) / delta_zoom)*(pos_y - griglia_livello.getGriglia().y);
                            delta_zoom *= INCREMENTO_DELTA_ZOOM;
                        } else {
                            delta_zoom = DELTA_ZOOM;
                            aux_griglia.zoom = min_zoom;
                            aux_griglia.x = griglia_livello.getGriglia().x + (((zoom / (GLfloat) min_zoom) - 1) / (zoom / (GLfloat) min_zoom))*(pos_x - griglia_livello.getGriglia().x);
                            aux_griglia.y = griglia_livello.getGriglia().y + (((zoom / (GLfloat) min_zoom) - 1) / (zoom / (GLfloat) min_zoom))*(pos_y - griglia_livello.getGriglia().y);
                        }
                        mouvi_zoom = true;
                    }
                }
            }
            if (!bottone_destro && evento->button.button == SDL_BUTTON_MIDDLE && tipo_proiezione == PROSPETTICA) {
                angolo_telecamera_x_iniziale = angolo_telecamera_x;
                angolo_telecamera_y_iniziale = angolo_telecamera_y;
                pos_x_iniziali = pos_x;
                pos_y_iniziali = pos_y;
                bottone_centrale = true;
            }
            break;
        case SDL_MOUSEMOTION:
            getMousePosGrigliaXY(gioco->getWindowA(), evento->button.x, evento->button.y);
            if (bottone_destro) {
                griglia_livello.setGrigliaXY(aux_griglia.x + (pos_x - pos_x_iniziali), aux_griglia.y + (pos_y - pos_y_iniziali));
            }
            if (bottone_centrale) {
                GLfloat nuovo_angolo_x = angolo_telecamera_x_iniziale + (pos_x_iniziali - pos_x);
                GLfloat nuovo_angolo_y = angolo_telecamera_y_iniziale + (pos_y_iniziali - pos_y);
                if (fabs(nuovo_angolo_x) < MAX_ANGOLO_TELECAMERA_XY) {
                    angolo_telecamera_x = nuovo_angolo_x;
                } else {
                    if (angolo_telecamera_x < 0)
                        angolo_telecamera_x = -MAX_ANGOLO_TELECAMERA_XY;
                    else
                        angolo_telecamera_x = MAX_ANGOLO_TELECAMERA_XY;
                }
                if (fabs(nuovo_angolo_y) < MAX_ANGOLO_TELECAMERA_XY) {
                    angolo_telecamera_y = nuovo_angolo_y;
                } else {
                    if (nuovo_angolo_y < 0)
                        angolo_telecamera_y = -MAX_ANGOLO_TELECAMERA_XY;
                    else
                        angolo_telecamera_y = MAX_ANGOLO_TELECAMERA_XY;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (evento->button.button == SDL_BUTTON_RIGHT) {
                bottone_destro = false;
            }
            if (evento->button.button == SDL_BUTTON_MIDDLE) {
                bottone_centrale = false;
            }
            break;
        case SDL_VIDEORESIZE:
            gioco->setWindowLA(evento->resize.w, evento->resize.h);
            setProiezione(tipo_proiezione, evento->resize.w, evento->resize.h);
        default:
            break;
    }
    return 1;
}