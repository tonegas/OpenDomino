/* 
 * File:   Editor.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 23.37
 */

#ifndef _EDITOR_H
#define	_EDITOR_H

#include "Domino.h"
#include "Livello.h"
#include "Partita.h"


#define GRIGLIA_EDITOR_Y 1000
#define GRIGLIA_EDITOR_X 1000

#define LARGHEZZA_FIN_EDITOR 1000
#define ALTEZZA_FIN_EDITOR  1000

#define POSIZIONE_SUPERFICE -0.001

#define POSIZIONE_SUPERFICE -0.001

#define POSIZIONA_PEZZI 1
#define POSIZIONA_BASI 2
#define ELIMINA_PEZZI -1
#define ELIMINA_BASI -2

#define DAVANTI_PEZZO 3
#define DAVANTI_BASE 4

class Editor : public Livello {
    Partita test;
    
    Pezzo aux_pezzo;
    Base aux_base;

    int num_x_colonne;
    int num_y_righe;

    bool posiziona_pezzi, posiziona_basi;
    int azione_continua;

    int caratteristiche_selezione;
    bool entrambi;
    unsigned x_pezzo_selezionato,y_pezzo_selezionato;
    unsigned x_base_selezionata,y_base_selezionata;

    //GLfloat **cubo_selezione;

public:
    Editor(Gioco *gioco_aux, int num_x_colonne_aux= GRIGLIA_EDITOR_X, int num_y_righe_aux= GRIGLIA_EDITOR_Y);
    
    ~Editor();

    void inizializzaEditor();

    int mouseSelezione(int larghezza_fin);

    int aggiornaStato();
    int video();
    int gestisciInput(SDL_Event *evento);

    int aggiornaStatoEditor();
    int videoEditor();
    int gestisciInputEditor(SDL_Event *evento);


    void stampaSuperficeBase();
    void stampaQuadrato(int x, int y, GLfloat attivo);

};


#endif	/* _EDITOR_H */

