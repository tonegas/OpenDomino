/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 30 novembre 2009, 15.16
 */

#include "../include/Domino.h"

Elemento::Elemento(unsigned x_aux, unsigned y_aux) {
    x = x_aux;
    y = y_aux;
};

Elemento::Elemento(const Elemento& orig) {
    x = orig.x;
    y = orig.y;
};

void Elemento::spostaElemento(unsigned x_new, unsigned y_new) {
    x = x_new;
    y = y_new;
}

Elemento* Elemento::costruttore() {
    return NULL;
}

