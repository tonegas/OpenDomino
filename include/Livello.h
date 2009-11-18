/* 
 * File:   Livello.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 16.03
 */

#ifndef _LIVELLO_H
#define	_LIVELLO_H

enum Proiezione {
    ASSIONOMETRICA, PROSPETTICA
};

enum Selezione {
    NIENTE, DAVANTI_PEZZO, DAVANTI_BASE
};

class Gioco;

#include "Domino.h"

const GLfloat cavalier[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    -0.5, -0.5, 1, 0,
    0, 0, 0, 1
};

class Livello {
protected:
    //puntatore al gioco per interagire sulle funzionidi gioco
    Gioco *gioco; //ok

    //matrici dinamiche di pezzi e basi
    Griglia griglia_livello; //ok

    //per ora sono solo due bottoni ma penso che diventerà una struttura per gestire l'input in maniera
    //differente a seconda che il livello si editor partita o altro
    bool bottone_sinistro, bottone_destro, bottone_centrale; //ok

    //proiezione della griglia a schermo
    Proiezione tipo_proiezione; //inizializzati nella setProiezione

    //puntatore alla telecamera corrente e le due telecamere che si possono utilizzare
    Telecamera *telecamera_attuale;
    TelecameraAssionometrica tele_assio;
    TelecameraProspettica tele_prosp;

    //questi li possono usare livello ma anche le classi derivate
    //variabili per la selezione dei pezzi
    Selezione caratteristiche_selezione;
    //flag che indica se ho selezionato sia
    bool entrambi;
    unsigned x_pezzo_selezionato, y_pezzo_selezionato;
    unsigned x_base_selezionata, y_base_selezionata;
    //---------------------------

    void gestisciInput(SDL_Event *evento);

protected:
    virtual void stampaSuperficeBase();

    virtual void stampaSfondo();

    virtual void keyDownF5();

    virtual void attivaSelezioni() {
    }

    virtual void mouseButtonDown(SDL_Event *evento) {
    }

    virtual void mouseMotion(SDL_Event *evento) {
    }

    virtual void mouseButtonUp(SDL_Event *evento) {
    }

public:

    Livello(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux);

    Livello(const Livello &orig);

    int inizializza();

    void cicloGioco(SDL_Event *evento);

    void resettaSelezione();

    void selezioneDavantiPezzo(unsigned aux_x_pezzo_selezionato, unsigned aux_y_pezzo_selezionato);

    void selezioneDavantiBase(unsigned aux_x_base_selezionata, unsigned aux_y_base_selezionata);
};


#endif	/* _LIVELLO_H */

