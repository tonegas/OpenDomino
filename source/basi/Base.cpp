/* 
 * File:   Base.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.45
 */

#include "../../include/Domino.h"

Base::Base(bool alive_aux) : Elemento(BASE,alive_aux){}

Base::Base(const Base& orig) : Elemento(orig)  {}