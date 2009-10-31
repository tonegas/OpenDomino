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

#define ELEM_PEZZ0 10

#include "../Domino.h"

class Pezzo : public Elemento{
public:
    Pezzo();
    Pezzo(const Pezzo& orig);
};

#endif	/* _PEZZO_H */

