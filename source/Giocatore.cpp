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
    tempo_di_gioco_apertura = time(NULL);
    data_di_creazione = time(NULL);
    domino = NULL;
    domino_editor = NULL;
}

Giocatore::Giocatore(const Giocatore& orig) {
    nome = orig.nome;
    tempo_di_gioco = orig.tempo_di_gioco;
    tempo_di_gioco_apertura = orig.tempo_di_gioco_apertura;
    data_di_creazione = orig.data_di_creazione;
    if (orig.domino != NULL) {
        domino = new Partita(*orig.domino);
    } else {
        domino = NULL;
    }
    if (orig.domino_editor != NULL) {
        domino_editor = new Editor(*orig.domino_editor);
    } else {
        domino_editor = NULL;
    }
}

Giocatore::~Giocatore() {
    if (domino != NULL) {
        delete domino;
    }
    if (domino_editor != NULL) {
        delete domino_editor;
    }
}

Giocatore::Giocatore(QString nome_aux, time_t tempo_di_gioco_aux, time_t data_di_creazione_aux) {
    nome = nome_aux;
    tempo_di_gioco = tempo_di_gioco_aux;
    tempo_di_gioco_apertura = time(NULL);
    data_di_creazione = data_di_creazione_aux;
    domino = NULL;
    domino_editor = NULL;
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

}