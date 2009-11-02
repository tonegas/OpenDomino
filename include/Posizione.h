/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 31 ottobre 2009, 20.13
 */

#ifndef _POSIZONE_H
#define	_POSIZONE_H

#include "Domino.h"

class Elemento {
public:
    Elemento(){};
    Elemento(const Elemento& orig){};
    //virtual ~Elemento();
};

class Posizione {
public:
    GLfloat selezione_pezzo;
    GLfloat selezione_base;
    int tipo;
    bool occupata;
    Elemento *elem;

    Posizione();

    ~Posizione();

    void liberaPosizione();

    void attivaSelezione(int tipo_aux);

    int getTipo();

    void occupaPosizione(Elemento *elem_aux,int tipo_aux);
};

#endif	/* _POSIZONE_H */

