/* 
 * File:   Heap_Eventi.h
 * Author: tonegas
 *
 * Created on 22 ottobre 2009, 23.00
 */

#ifndef _HEAP_EVENTI_H
#define	_HEAP_EVENTI_H

#include "Evento.h"
//#include <SDL/SDL.h>
#include <iostream>

using namespace std;

class Heap_Eventi {
    vector<Evento> Heap;
    SDL_cond *nuovo_evento_cond;
    SDL_mutex *nuovo_evento_mutex;

public:

    Heap_Eventi();

    void inserisciEvento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux);

    void inserisciEventoPeriodico(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux);

    Evento estraiEvento();

    void controlloHeap();

    bool empty();
};

#endif	/* _HEAP_EVENTI_H */

