/* 
 * File:   Pezzo.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.35
 */

#include "../../include/Domino.h"
//#include "../../include/pezzi/Pezzo.h"
//#include"../../include/Griglia.h"

Pezzo::Pezzo(unsigned x_aux, unsigned y_aux) : Elemento(x_aux, y_aux) {
    stato = IN_PIEDI;

    angolo_destro = false;
    angolo = 0.0;
    dx = dy = dz = 0;
}

Pezzo::Pezzo(const Pezzo& orig) : Elemento(orig) {
    stato = orig.stato;

    angolo_destro = orig.angolo_destro;
    angolo = orig.angolo;
    dx = orig.dx;
    dy = orig.dy;
    dz = orig.dz;
}

Elemento* Pezzo::costruttore() {
    return new Pezzo(*this);
}

void Pezzo::setStato(void* aux_stato) {
    stato = *(StatoPezzo*) aux_stato;
}

StatoPezzo Pezzo::getStato() {
    return stato;
}

void Pezzo::aggiornaStato(Griglia &griglia) {
    int x_successiva = 0;
    switch (stato) {
        case IN_PIEDI:
            if (dy >= 0 && !griglia.getOccupato(x,y - 1)) {
                stato = CADE_GIU;
            }
            break;
        case CADE_SINISTRA:
            x_successiva = x - 1;
            break;
        case CADE_DESTRA:
            angolo_destro = true;
            x_successiva = x + 1;
            break;
        case CADE_GIU:
            dy -=(GLdouble) ALTEZZA_PEZZO/8.0;
            if (dy<-((GLdouble) ALTEZZA_PEZZO / 2.0)) {
                griglia.spostaElementoAttivo(x, y, x, y - 1);
                dy = -dy;
            }
            if (dy <= 0 && griglia.getOccupato(x,y - 1)) {
                stato = IN_PIEDI;
                dy = 0;
            }
            break;
    }
    if (stato == CADE_SINISTRA || stato == CADE_DESTRA) {
        if (angolo < 77) {
            if (angolo > 50) {
                if (griglia.getOccupato(x_successiva, y)) {
                    griglia.setStato(x_successiva, y, stato);
                } else {
                    angolo += 1;
                }
            } else {
                angolo += 1;
            }
            angolo += 1;
        } else {
            if (!griglia.getOccupato(x_successiva, y)) {
                if (angolo < 90) {
                    angolo += 2;
                } else {
                    if (!griglia.getOccupato(x_successiva, y - 1)) {
                        griglia.spostaElementoAttivo(x, y, x_successiva, y - 1);
                        angolo = 0;
                    } else {
                        angolo = 90;
                    }
                }
            }
        }
    }
}

void Pezzo::stampaSelezione(unsigned x, unsigned y, GLfloat attivo) {
    static GLfloat xf, yf, sposto_x, sposto_y, grandezza;

    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;
    grandezza = attivo;

    glPushMatrix();
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);
    glTranslatef(SPESSORE_PEZZO * (1.0 - grandezza) / 2, ALTEZZA_PEZZO * (1.0 - grandezza) / 2, LARGHEZZA_PEZZO * (1.0 - grandezza) / 2);
    glScalef(grandezza, grandezza, grandezza);
    glColor4f(1.0f, 1.0f, 0.0f, attivo);

    glDisable(GL_LIGHTING);

    glLineWidth(grandezza + 1);
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Pezzo::stampaPezzoCollisione(unsigned x, unsigned y) {
    static GLfloat xf, yf, sposto_x, sposto_y;
    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);
    glBegin(GL_QUADS);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);

        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);

        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);

        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);

        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glPopMatrix();
}

void Pezzo::stampa() {
    static GLfloat xf, yf, sposto_x, sposto_y;
    static GLfloat coloryellow[] = {1.0f, 1.0f, 0.0f, 1.0f};

    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf + ((GLfloat) ALTEZZA_PEZZO / 2.0)-((GLfloat) SPESSORE_PEZZO / 2.0);
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, coloryellow);
    glTranslatef(sposto_x, sposto_y, Z_PEZZO);

    glTranslated(dx, dy, dz);
    if (angolo_destro) {
        static const GLfloat ribalta[] = {
            -1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
        glTranslated(SPESSORE_PEZZO, 0, 0);
        glMultMatrixf(ribalta);
    }
    glTranslated(angolo / 90.0 * ((GLdouble) SPESSORE_PEZZO / 2.0), 0, 0);
    glRotated(angolo, 0, 0, 1);
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);

        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, LARGHEZZA_PEZZO);
        glVertex3f(SPESSORE_PEZZO, ALTEZZA_PEZZO, 0.0);
        glVertex3f(0.0, ALTEZZA_PEZZO, 0.0);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, 0.0);
        glVertex3f(SPESSORE_PEZZO, 0.0, LARGHEZZA_PEZZO);
        glVertex3f(0.0, 0.0, LARGHEZZA_PEZZO);
    }
    glEnd();
    glPopMatrix();
}
