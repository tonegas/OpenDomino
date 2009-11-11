/* 
 * File:   Elemento.h
 * Author: tonegas
 *
 * Created on 31 ottobre 2009, 20.13
 */

#ifndef _POSIZONE_H
#define	_POSIZONE_H

enum TipoElemento {
    NESSUNO, ELEM_PEZZO, ELEM_BASE
};

class Griglia;

#include "Domino.h"


class Elemento {
protected:
    unsigned x, y;
public:
    Elemento(unsigned x_aux, unsigned y_aux) {
        x = x_aux;
        y = y_aux;
    };

    Elemento(const Elemento& orig) {
        x = orig.x;
        y = orig.y;
    };

    void spostaElemento(unsigned x_new,unsigned y_new){
        x=x_new;
        y=y_new;
    }

    virtual Elemento* costruttore(){
        return NULL;
    }

    virtual void aggiornaStato(Griglia &griglia){}

    virtual void setStato(void *stato){}

    static void stampa(bool wire, unsigned x, unsigned y, GLfloat attivo) {
    }

    virtual void stampa() {
    }
    //virtual ~Elemento();
};

class ElementoAttivo {
    friend class Griglia;
    friend class Pezzo;
public:
    unsigned x, y;
    TipoElemento tipo;
    Elemento *elem;

    GLfloat selezione_pezzo;
    GLfloat selezione_base;
    ElementoAttivo *next;
    ElementoAttivo *prev;


    ElementoAttivo();

    ElementoAttivo(unsigned x_aux, unsigned y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(Elemento *elem_aux, unsigned x_aux, unsigned y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(unsigned x_aux, unsigned y_aux, ElementoAttivo *next_aux = NULL, ElementoAttivo *prev_aux = NULL);

    ElementoAttivo(const ElementoAttivo& orig);

    ~ElementoAttivo();

    Elemento* getElem();

    void liberaPosizione();

    void attivaSelezione(int tipo_aux);

    bool getOccupato();

    int getTipo();

    void occupaPosizione(Elemento *elem_aux, TipoElemento tipo_aux);
};

#endif	/* _POSIZONE_H */

