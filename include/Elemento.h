/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 31 ottobre 2009, 20.13
 */

#ifndef _ELEMENTO_H
#define	_ELEMENTO_H


#include "Domino.h"

class Elemento {
protected:
    bool presente;
    int tipo;
    GLfloat selezione;
public:
    Elemento(int tipo_aux,bool alive_aux = false);
    Elemento(const Elemento& orig);
    //virtual ~Elemento();

    void setAlive(bool alive_aux);
    bool getAlive();
    void setSelezione(GLfloat selezione_aux);
    GLfloat getSelezione();
    int getTipo();
};

#endif	/* _ELEMENTO_H */

