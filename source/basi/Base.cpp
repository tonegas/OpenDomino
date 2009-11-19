/* 
 * File:   Base.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.45
 */

#include "../../include/Domino.h"
//#include "../../include/basi/Base.h"
//#include "../../include/pezzi/Pezzo.h"

Base::Base(unsigned x_aux, unsigned y_aux) : Elemento(x_aux, y_aux) {
}

Base::Base(const Base& orig) : Elemento(orig) {
}

Elemento* Base::costruttore() {
    return new Base(*this);
}

void Base::aggiornaStato(Griglia &griglia) {
}

void Base::setStato(void *stato) {
}

void Base::stampaSelezione(unsigned x, unsigned y, GLfloat attivo) {
    static GLfloat xf, yf, sposto_x, sposto_y, grandezza;

    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;
    grandezza = attivo;

    glPushMatrix();
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    glTranslatef(SPESSORE_BASE * (1.0 - grandezza) / 2, ALTEZZA_BASE * (1.0 - grandezza) / 2, LARGHEZZA_BASE * (1.0 - grandezza) / 2);
    glScalef(grandezza, grandezza, grandezza);
    glColor4f(0.0f, 1.0f, 0.0f, attivo);

    glDisable(GL_LIGHTING);
    glLineWidth(grandezza + 1);
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void Base::stampaBaseCollisione(unsigned x, unsigned y) {
    static GLfloat xf, yf, sposto_x, sposto_y;
    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);

        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);

        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);

        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);

        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
    }
    glEnd();
    glPopMatrix();
}

void Base::stampa() {
    static GLfloat colorgreen [] = {0.0f, 1.0f, 0.0f, 1.0f};
    static GLfloat xf, yf, sposto_x, sposto_y;

    xf = (GLfloat) x;
    yf = (GLfloat) y;
    sposto_x = ((GLfloat) ALTEZZA_PEZZO) * xf;
    sposto_y = ((GLfloat) ALTEZZA_PEZZO) * yf;

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colorgreen);
    glColor4fv(colorgreen);

    glTranslatef(sposto_x, sposto_y + ALTEZZA_PEZZO - ALTEZZA_BASE, 0.0);

    glBegin(GL_QUADS);
    {
        glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);

        glNormal3f(1.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);

        glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);

        glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);

        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, LARGHEZZA_BASE);
        glVertex3f(SPESSORE_BASE, ALTEZZA_BASE, 0.0);
        glVertex3f(0.0, ALTEZZA_BASE, 0.0);

        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, 0.0);
        glVertex3f(SPESSORE_BASE, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, LARGHEZZA_BASE);
        glVertex3f(0.0, 0.0, 0.0);
    }
    glEnd();
    glPopMatrix();
}