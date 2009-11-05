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

#define Z_PEZZO 2

#include "../Domino.h"
#include "../Posizione.h"

enum StatoPezzo {
    IN_PIEDI, CADE_DESTRA, CADE_SINISTRA
};

class Pezzo : public Elemento {
    GLdouble angolo;
    StatoPezzo stato;
public:
    Pezzo(int x_aux = -1, int y_aux = -1);
    Pezzo(const Pezzo& orig);
    void setStato(StatoPezzo aux_stato);
    StatoPezzo getStato();
    void aggiorna();
    void stampa();
    void stampa(bool wire, int x, int y, GLfloat attivo);
};

#endif	/* _PEZZO_H */

