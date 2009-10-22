/* 
 * File:   Evento.cpp
 * Author: tonegas
 * 
 * Created on 22 ottobre 2009, 20.03
 */

#include "../../include/appoggio/Evento.h"

Evento::Evento() {
}

Evento::Evento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux) {
    fn = fn_aux;
    param = param_aux;
    quando = quando_aux;
    rip = 0;
}

Evento::Evento(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux) {
    fn = fn_aux;
    param = param_aux;
    intervallo = intervallo_aux;
    quando = SDL_GetTicks() + intervallo_aux;
    rip = rip_aux;
}

Evento::Evento(const Evento &evento_aux) {
    fn = evento_aux.fn;
    param = evento_aux.param;
    quando = evento_aux.quando;
    intervallo = evento_aux.intervallo;
    rip = evento_aux.rip;
}

bool Evento::getRip() {
    return rip;
}

Uint32 Evento::getIntervallo() {
    return intervallo;
}

Uint32 Evento::getQuando() const{
    return quando;
}

void Evento::setQuando(Uint32 quando_aux) {
    quando = quando_aux;
}

void Evento::esegui() {
    fn(param);
}
