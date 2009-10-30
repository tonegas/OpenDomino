/* 
 * File:   Base.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.45
 */

#include "../../include/Domino.h"

Base::Base(bool alive_aux) {
    presente = alive_aux;
}

Base::Base(const Base& orig) {
    presente = orig.presente;
    selezione = orig.selezione;
}

void Base::setAlive(bool alive_aux) {
    presente = alive_aux;
}

bool Base::getAlive() {
    return presente;
}

void Base::setSelezione(GLfloat selezione_aux) {
    selezione = selezione_aux;
}

GLfloat Base::getSelezione() {
    return selezione;
}

