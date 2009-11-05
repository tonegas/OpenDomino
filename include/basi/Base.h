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
#include "../Posizione.h"


class Base : public Elemento{
public:
    Base(int x_aux = -1,int y_aux= -1);
    Base(const Base& orig);
    void stampa(bool wire, int x, int y, GLfloat attivo);
    void stampa();
};

#endif	/* _BASE_H */

