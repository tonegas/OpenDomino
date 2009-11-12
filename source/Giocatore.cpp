/* 
 * File:   Giocatore.cpp
 * Author: tonegas
 * 
 * Created on 12 novembre 2009, 0.04
 */

#include "../include/Domino.h"

Giocatore::Giocatore(string nome_aux) {
    nome = nome_aux;
    file_giocatore.open(nome.c_str(), ios::out);
    if (file_giocatore) {
        caricaGiocatore();
    } else {
        nuovoGiocatore();
    }
}

Giocatore::~Giocatore() {
    salvaGiocatore();
}

void Giocatore::caricaGiocatore() {
    if (!file_giocatore.is_open()) {
        file_giocatore.open(nome.c_str(), ios::in);
    }
    string aux;
    file_giocatore >> aux;
    nome = aux.substr(aux.find(":"));
    file_giocatore >> tempo_di_gioco_apertura;
    //tempo_di_gioco_apertura = aux.substr(aux.find(":"));
    file_giocatore >> creazione_giocatore;
    //creazione_giocatore = aux.substr(aux.find(":"));
    file_giocatore.close();
}

void Giocatore::salvaGiocatore() {
    if (!file_giocatore.is_open()) {
        file_giocatore.open(nome.c_str(), ios::out);
    }
    file_giocatore << "Nome:" << nome << "\n";
    //file_giocatore << "Tempo di gioco complessivo (sec):" << time() - tempo_partita << "\n";
    //file_giocatore << "Data creazione (sec dal 1° gennaio dal 1970):" << creazione_giocatore << "\n";
    file_giocatore.close();
}

void Giocatore::nuovoGiocatore() {
    tempo_partita = time(NULL);
    tempo_di_gioco_apertura = 0;
    creazione_giocatore = time(NULL);
    salvaGiocatore();
}
//Giocatore::Giocatore(const Giocatore& orig) {
//}

