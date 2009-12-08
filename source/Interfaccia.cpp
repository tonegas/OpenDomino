/* 
 * File:   Inerfaccia.cpp
 * Author: tonegas
 * 
 * Created on 1 dicembre 2009, 23.52
 */

#include "../include/Domino.h"

Gioco* Interfaccia::gioco = NULL;
SDL_Event* Interfaccia::evento = NULL;

Interfaccia::Interfaccia(){
}

Interfaccia::Interfaccia(Gioco* gioco_aux, SDL_Event* evento_aux){
    gioco = gioco_aux;
    evento = evento_aux;
}