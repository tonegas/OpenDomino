/* 
 * File:   Editor.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 23.37
 */

#ifndef _EDITOR_H
#define	_EDITOR_H

#define GRIGLIA_EDITOR_Y 1000
#define GRIGLIA_EDITOR_X 1000

#define LARGHEZZA_FIN_EDITOR 1000
#define ALTEZZA_FIN_EDITOR  1000

#define POSIZIONE_SUPERFICE -0.001

enum AzioneMouse {
    NESSUNA_AZIONE, POSIZIONA_PEZZI, POSIZIONA_BASI, ELIMINA_PEZZI, ELIMINA_BASI
};

class Partita;
class Livello;
class Gioco;

#include "Domino.h"

class Editor : public Livello {
    int num_x_colonne;
    int num_y_righe;

    AzioneMouse azione_continua;

protected:
    void mouseButtonDown(SDL_Event *evento);
    void mouseMotion();
    void mouseButtonUp(SDL_Event *evento);
    void attivaSelezioni();

public:
    Editor(Gioco *gioco_aux, int num_x_colonne_aux = GRIGLIA_EDITOR_X, int num_y_righe_aux = GRIGLIA_EDITOR_Y);
    ~Editor();
};


#endif	/* _EDITOR_H */

