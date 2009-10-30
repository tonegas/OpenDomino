/* 
 * File:   Base.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.45
 */

#ifndef _BASE_H
#define	_BASE_H

#define LARGHEZZA_BASE 8
#define ALTEZZA_BASE 2
#define SPESSORE_BASE 8

#include "../Domino.h"


class Base {
    bool presente;
    GLfloat selezione;
public:

    Base(bool alive_aux = false);

    Base(const Base& orig);

    void setAlive(bool alive_aux);

    bool getAlive();

    void setSelezione(GLfloat selezione_aux);

    GLfloat getSelezione();
};

#endif	/* _BASE_H */

