/* 
 * File:   Elemento.cpp
 * Author: tonegas
 * 
 * Created on 31 ottobre 2009, 20.13
 */

#include "../include/Domino.h"

Elemento::Elemento(bool alive_aux) {
    presente = alive_aux;
}

Elemento::Elemento(const Elemento& orig) {
    presente = orig.presente;
    selezione = orig.selezione;
}

void Elemento::setAlive(bool alive_aux) {
    presente = alive_aux;
}

bool Elemento::getAlive() {
    return presente;
}

void Elemento::setSelezione(GLfloat selezione_aux) {
    selezione = selezione_aux;
}

GLfloat Elemento::getSelezione() {
    return selezione;
}
