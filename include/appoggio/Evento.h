/* 
 * File:   Evento.h
 * Author: tonegas
 *
 * Created on 22 ottobre 2009, 20.03
 */

#ifndef _EVENTO_H
#define	_EVENTO_H

#include <SDL/SDL.h>
#include <algorithm>
#include <vector>

class Evento {
    void (*fn)(void*);
    void *param;
    bool rip;
    Uint32 quando;
    Uint32 intervallo;

public:

    Evento();
    Evento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux);
    Evento(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux);
    Evento(const Evento &evento_aux);
    bool getRip();
    Uint32 getIntervallo();
    Uint32 getQuando() const;
    void setQuando(Uint32 quando_aux);
    void esegui();
    
};

#endif	/* _EVENTO_H */

