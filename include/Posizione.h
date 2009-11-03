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
protected:
    int x,y;
public:
    Elemento(int x_aux,int y_aux){
        x=x_aux;
        y=y_aux;
    };
    Elemento(const Elemento& orig){
        x=orig.x;
        y=orig.y;
    };
    virtual void stampa(bool wire, int x, int y, GLfloat attivo){}
    virtual void stampa(){}
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

    Elemento* getElem();

    void liberaPosizione();

    void attivaSelezione(int tipo_aux);

    int getTipo();

    void occupaPosizione(Elemento *elem_aux,int tipo_aux);
};

#endif	/* _POSIZONE_H */

