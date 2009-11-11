/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */
#include "../include/Domino.h"


ElementoAttivo::ElementoAttivo() {
    selezione_pezzo = 0;
    selezione_base = 0;
    elem = NULL;
}

ElementoAttivo::ElementoAttivo(Elemento *elem_aux, unsigned x_aux, unsigned y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux, ElementoAttivo *prev_aux) {
    selezione_pezzo = 0;
    selezione_base = 0;
    x = x_aux;
    y = y_aux;
    tipo = tipo_aux;
    next = next_aux;
    prev = prev_aux;
    elem = elem_aux;
}

ElementoAttivo::ElementoAttivo(unsigned x_aux, unsigned y_aux, ElementoAttivo *next_aux, ElementoAttivo *prev_aux) {
    selezione_pezzo = 0;
    selezione_base = 0;
    x = x_aux;
    y = y_aux;
    next = next_aux;
    prev = prev_aux;
    elem = NULL;
}

ElementoAttivo::ElementoAttivo(unsigned x_aux, unsigned y_aux, TipoElemento tipo_aux, ElementoAttivo *next_aux, ElementoAttivo *prev_aux) {
    x = x_aux;
    y = y_aux;
    next = next_aux;
    prev = prev_aux;
    if (tipo_aux == ELEM_PEZZO) {
        selezione_pezzo = 1;
        selezione_base = 0;
    } else {
        selezione_base = 1;
        selezione_pezzo = 0;
    }
    elem = NULL;
    tipo = tipo_aux;
}

ElementoAttivo::ElementoAttivo(const ElementoAttivo& orig) {
    x = orig.x;
    y = orig.y;
    next = NULL;
    prev = NULL;
    selezione_pezzo = orig.selezione_pezzo;
    selezione_base = orig.selezione_base;
    tipo = orig.tipo;
    if (orig.elem != NULL) {
        elem = orig.elem->costruttore();
    } else {
        elem = NULL;
    }
}

ElementoAttivo::~ElementoAttivo() {
    if (elem != NULL)
        delete elem;
    elem = NULL;
}

Elemento* ElementoAttivo::getElem() {
    return elem;
}

bool ElementoAttivo::getOccupato() {
    return elem != NULL ? true : false;
}

void ElementoAttivo::liberaPosizione() {
    if (elem != NULL)
        delete elem;
    elem = NULL;
}

void ElementoAttivo::attivaSelezione(int tipo_aux) {
    if (tipo_aux == ELEM_PEZZO) {
        selezione_pezzo = 1;
    } else {
        selezione_base = 1;
    }
}

int ElementoAttivo::getTipo() {
    return tipo;
}

void ElementoAttivo::occupaPosizione(Elemento *elem_aux, TipoElemento tipo_aux) {
    tipo = tipo_aux;
    elem = elem_aux;
}
