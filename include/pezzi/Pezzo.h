/* 
 * File:   Pezzo.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 15.35
 */

#ifndef _PEZZO_H
#define	_PEZZO_H

#define LARGHEZZA_PEZZO 4
#define ALTEZZA_PEZZO 8
#define SPESSORE_PEZZO 2

#define ELEM_PEZZO 10

#define Z_PEZZO 2

#include "../Domino.h"
#include "../Posizione.h"

class Pezzo : public Elemento{
public:
    Pezzo(int x_aux,int y_aux);
    Pezzo(const Pezzo& orig);
    void stampa();
    void stampa(bool wire, int x, int y, GLfloat attivo);
};

#endif	/* _PEZZO_H */

