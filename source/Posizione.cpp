/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */

#include "../include/Domino.h"
#include "../include/Posizione.h"
#include "../include/pezzi/Pezzo.h"
#include "../include/basi/Base.h"

ElementoAttivo::ElementoAttivo() {
    selezione_pezzo = 0;
    selezione_base = 0;
    elem = NULL;
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
    if (tipo_aux == ELEM_PEZZO)
        selezione_pezzo = 1;
    if (tipo_aux == ELEM_BASE)
        selezione_base = 1;
}

int ElementoAttivo::getTipo() {
    return tipo;
}

void ElementoAttivo::occupaPosizione(Elemento *elem_aux, TipoElemento tipo_aux) {
    tipo = tipo_aux;
    elem = elem_aux;
}
