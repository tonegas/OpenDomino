/* 
 * File:   Pezzo.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.35
 */

#include "../../include/pezzi/Pezzo.h"

Pezzo::Pezzo(int x_aux, int y_aux) : Elemento(x_aux, y_aux) {
    stato = IN_PIEDI;
    angolo = 0.0;
}

Pezzo::Pezzo(const Pezzo& orig) : Elemento(orig) {
    stato = orig.stato;
    angolo = orig.angolo;
}

void Pezzo::setStato(StatoPezzo aux_stato) {
    stato = aux_stato;
}

StatoPezzo Pezzo::getStato() {
    return stato;
}

void Pezzo::aggiorna() {
    switch (stato) {
        case IN_PIEDI:
            break;
        case CADE_DESTRA:
            angolo+=2;
            break;
        case CADE_SINISTRA:
            angolo-=2;
            break;

    }
}

void Pezzo::stampa(bool wire, int x, int y, GLfloat attivo) {
    static GLfloat coloryellow[] = {1.0f, 1.0f, 0.0f, 1.0f};

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
    glRotated(angolo,0,0,1);
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

void Pezzo::stampa() {
    stampa(false, x, y, 0);
}
