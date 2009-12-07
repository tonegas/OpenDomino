/* 
 * File:   Giocatore.cpp
 * Author: tonegas
 * 
 * Created on 12 novembre 2009, 0.04
 */

#include "../include/Domino.h"

Giocatore::Giocatore() {

}

Giocatore::Giocatore(QString nome_aux) {
    nome = nome_aux;
    tempo_di_gioco = 0;
    stato = EDITOR_COSTRUISCI;
    cambia_stato = false;
    nome_livello_attuale = "";
    tempo_di_gioco_apertura = time(NULL);
    data_di_creazione = time(NULL);
    domino = NULL;
    partita_allocata = false;
    domino_editor = NULL;
}

Giocatore::Giocatore(const Giocatore& orig) {
    nome = orig.nome;
    tempo_di_gioco = orig.tempo_di_gioco;
    tempo_di_gioco_apertura = orig.tempo_di_gioco_apertura;
    data_di_creazione = orig.data_di_creazione;
    stato = orig.stato;
    cambia_stato = orig.cambia_stato;
    if (orig.domino != NULL) {
        domino = new Partita(*orig.domino);
        partita_allocata = true;
    } else {
        partita_allocata = false;
        domino = NULL;
    }
    if (orig.domino_editor != NULL) {
        domino_editor = new Editor(*orig.domino_editor);
    } else {
        domino_editor = NULL;
    }
}

Giocatore::~Giocatore() {
    if (partita_allocata) {
        delete domino;
    }
    if (domino_editor != NULL) {
        delete domino_editor;
    }
}

Giocatore::Giocatore(QString nome_aux, time_t tempo_di_gioco_aux, time_t data_di_creazione_aux) {
    nome = nome_aux;
    tempo_di_gioco = tempo_di_gioco_aux;
    nome_livello_attuale = "";
    stato = EDITOR_COSTRUISCI;
    cambia_stato = false;
    tempo_di_gioco_apertura = time(NULL);
    data_di_creazione = data_di_creazione_aux;
    domino = NULL;
    partita_allocata = false;
    domino_editor = NULL;
}

void Giocatore::inizializza(Gioco *gioco_aux, SDL_Event *evento_aux) {
    if (nome_livello_attuale == "") {
        nome_livello_attuale = nome + "Editor";
        domino_editor = new Editor(gioco_aux, evento_aux);
        domino_editor->inizializza();
        domino = domino_editor;
    } else {

    }
}

void Giocatore::riconfiguraVideo() {
    domino->inizializza();
}

QString Giocatore::getNome() {
    return nome;
}

void Giocatore::setNome(QString nuovo_nome) {
    nome = nuovo_nome;
}

time_t Giocatore::getDataDiCreazione() {
    return data_di_creazione;
}

time_t Giocatore::getTempoDiGioco() {
    return tempo_di_gioco;
}

time_t Giocatore::getTempoDiGiocoApertura() {
    return tempo_di_gioco_apertura;
}

void Giocatore::setTempoDiGiocoApertura() {
    tempo_di_gioco_apertura = time(NULL);
}

void Giocatore::cicloGioco() {
    if (cambia_stato) {
        switch (stato) {
            case EDITOR_TEST:
                if (partita_allocata) {
                    delete domino;
                    domino = new Partita(*domino_editor);
                } else {
                    partita_allocata = true;
                    domino = new Partita(*domino_editor);
                }
                break;
            case EDITOR_COSTRUISCI:
                if (partita_allocata) {
                    delete domino;
                }
                partita_allocata = false;
                domino = domino_editor;
                break;
            default:
                break;
        }
        domino->inizializza();
        cambia_stato = false;
    }
    domino->cicloGioco();
}

void Giocatore::cicloGiocoStampa() {
    domino->configuraVisuale();
    domino->cicloGiocoStampa();
}

void Giocatore::setStato(StatoGiocatore stato_aux) {
    if (stato != stato_aux) {
        cambia_stato = true;
        stato = stato_aux;
    }
}

StatoGiocatore Giocatore::getStato() {
    return stato;
}