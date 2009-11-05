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

enum StatoPezzo{
    IN_PIEDI,CADE_DESTRA,CADE_SINISTRA
};

class Pezzo : public Elemento{
    GLdouble angolo;
    StatoPezzo stato;
public:
    Pezzo(int x_aux = -1,int y_aux = -1);
    Pezzo(const Pezzo& orig);
    Elemento* costruttore();
    void setStato(void* stato);
    StatoPezzo getStato();
    void aggiornaStato();
    void stampa();
    static void stampa(bool wire, int x, int y, GLfloat attivo, GLdouble angolo = 0);
};

#endif	/* _PEZZO_H */

