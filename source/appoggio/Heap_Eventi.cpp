/* 
 * File:   Heap_Eventi.cpp
 * Author: tonegas
 * 
 * Created on 22 ottobre 2009, 23.00
 */

#include "../../include/appoggio/Heap_Eventi.h"


static bool comp(const Evento &elem1, const Evento &elem2) {
    if (elem1.getQuando() > elem2.getQuando()) {
        return true;
    } else {
        return false;
    }
}

Heap_Eventi::Heap_Eventi() {
    nuovo_evento_cond = SDL_CreateCond();
    nuovo_evento_mutex = SDL_CreateMutex();
}

void Heap_Eventi::inserisciEvento(void (*fn_aux)(void*), void *param_aux, Uint32 quando_aux) {
    Evento aux(fn_aux, param_aux, quando_aux);
    SDL_mutexP(nuovo_evento_mutex);
    Heap.push_back(aux);
    push_heap(Heap.begin(), Heap.end(), comp);
    SDL_CondSignal(nuovo_evento_cond);
    SDL_mutexV(nuovo_evento_mutex);
}

void Heap_Eventi::inserisciEventoPeriodico(void (*fn_aux)(void*), void *param_aux, Uint32 intervallo_aux, bool rip_aux) {
    Evento aux(fn_aux, param_aux, intervallo_aux, rip_aux);
    SDL_mutexP(nuovo_evento_mutex);
    Heap.push_back(aux);
    push_heap(Heap.begin(), Heap.end(), comp);
    SDL_CondSignal(nuovo_evento_cond);
    SDL_mutexV(nuovo_evento_mutex);
}

Evento Heap_Eventi::estraiEvento() {
    SDL_mutexP(nuovo_evento_mutex);
    if (Heap.empty()) {
        SDL_CondWait(nuovo_evento_cond, nuovo_evento_mutex);
    }
    Evento evento = Heap.front();
    pop_heap(Heap.begin(), Heap.end(), comp);
    Heap.pop_back();
    if (evento.getRip() == 1) {
        evento.setQuando(SDL_GetTicks() + evento.getIntervallo());
        Heap.push_back(evento);
        push_heap(Heap.begin(), Heap.end(), comp);
        SDL_CondSignal(nuovo_evento_cond);
    }
    SDL_mutexV(nuovo_evento_mutex);
    return evento;
}

void Heap_Eventi::controlloHeap() {
    for (unsigned i = 0; i < Heap.size(); i++) cout << " " << Heap[i].getQuando() << flush;
}

bool Heap_Eventi::empty() {
    return Heap.empty();
}