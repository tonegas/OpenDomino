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

class Griglia;

#include "../Domino.h"
//#include "../Posizione.h"
//#include "../Griglia.h"

class Base : public Elemento{
public:
    Base(unsigned x_aux,unsigned y_aux);
    Base(const Base& orig);
    Elemento* costruttore();
    void aggiornaStato(Griglia &griglia);
    void setStato(void *stato);
    static void stampaSelezione(unsigned x, unsigned y, GLfloat attivo);
    static void stampaBaseCollisione(unsigned x, unsigned y);
    void stampa();
};

#endif	/* _BASE_H */

