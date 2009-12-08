/* 
 * File:   Inerfaccia.h
 * Author: tonegas
 *
 * Created on 1 dicembre 2009, 23.52
 */

#ifndef _INTERFACCIA_H
#define	_INTERFACCIA_H

class Gioco;

#include "Domino.h"

class Interfaccia {
protected:
    static Gioco *gioco;
    static SDL_Event *evento;
public:
    Interfaccia();
    Interfaccia(Gioco *gioco_aux, SDL_Event *evento);
};

#endif	/* _INERFACCIA_H */

