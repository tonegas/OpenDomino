/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 30 novembre 2009, 15.16
 */

#ifndef _ELEMENTO_H
#define	_ELEMENTO_H

#include "Domino.h"

class Griglia;

class Elemento {
protected:
    unsigned x, y;
public:
    Elemento(unsigned x_aux, unsigned y_aux);

    Elemento(const Elemento& orig);

    void spostaElemento(unsigned x_new,unsigned y_new);

    virtual Elemento* costruttore();

    virtual void aggiornaStato(Griglia &griglia) = 0;

    virtual void setStato(void *stato) = 0;

    virtual void stampa() = 0;
};

#endif	/* _ELEMENTO_H */

