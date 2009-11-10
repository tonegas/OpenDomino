/* 
 * File:   Livello.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 16.03
 */

#ifndef _LIVELLO_H
#define	_LIVELLO_H

#define X_TELECAMERA 0
#define Y_TELECAMERA 0
#define H_TELECAMERA 200
#define FOVY    40
#define ZNEAR   5
#define ZFAR    700

#define MAX_ZOOM_ASSIONOMETRIA 23
#define MIN_ZOOM_ASSIONOMETRIA 0.25

#define MAX_ZOOM_PROSPETTICA 3
#define MIN_ZOOM_PROSPETTICA 0.035
#define MAX_ANGOLO_TELECAMERA_XY 70

#define DELTA_ZOOM 1.1
#define INCREMENTO_DELTA_ZOOM 1.1

enum Proiezione {
    ASSIONOMETRICA, PROSPETTICA
};

enum Selezione {
    NIENTE, DAVANTI_PEZZO, DAVANTI_BASE
};

class Gioco;

#include "Domino.h"
//#include "Griglia.h"


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

    //flag che indica se è incorso un animazione sullo zoom
    bool mouvi_zoom; //inizializzati nella setProiezione
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom aux_griglia; //ok

    //proiezione della griglia a schermo
    Proiezione tipo_proiezione; //inizializzati nella setProiezione
    //massimo livello di zoom per la proiezione corrente
    GLfloat max_zoom, min_zoom; //inizializzati nella setProiezione
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom griglia_assionometrica; //ok
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom griglia_prospettica; //ok
    //modifica degli angoli di vista della telecamera
    GLfloat angolo_telecamera_x, angolo_telecamera_y; //ok
    GLfloat angolo_telecamera_x_iniziale, angolo_telecamera_y_iniziale; //si inizializzano prima di usarli nella funzione di imput


    //per ora sono solo due bottoni ma penso che diventerà una struttura per gestire l'input in maniera
    //differente a seconda che il livello si editor partita o altro
    bool bottone_sinistro, bottone_destro, bottone_centrale; //ok

    //variazione del delta di incremento dello zoom
    GLfloat delta_zoom; //ok
    //tempo per il reset del delta_zoom
    int tempo_reset_delta_zoom; //ok
    //velocita di frame rate per temporizzare le cose
    int frame_rate; //ok

    //matrici per il recupero dell'input del muose
    //inizializzate della classe che deriva livello
    GLdouble matrice_model[16]; //inizializzati nella setProiezione
    //coordinate sono riferite alla griglia
    GLdouble matrice_model_griglia[16]; //inizializzata dalla funzione video
    GLdouble matrice_proj[16]; //inizializzati nella setProiezione
    GLint matrice_view[4]; //inizializzati nella setProiezione

    //posizione z della superfice base di sfondo
    GLdouble superfice_z; //inizializzati nella setProiezione

    //posizione 3d del mouse assolute
    GLdouble pos_x, pos_y, pos_z; //si inizializzano nella getMousePosGrigliaXY
    //posizione 3d del mouse rispetto alla griglia
    GLdouble pos_x_griglia, pos_y_griglia,pos_z_griglia;
    //posizione 3d iniziali del mouse per lo spostamento della griglia
    GLdouble pos_x_iniziali, pos_y_iniziali; //questi si inizializzano da soli quando premo

    //indice sulla griglia del mouse
    unsigned indice_x_griglia, indice_y_griglia; //si inizializzano nella getMousePosGrigliaXY
    //indicatore booleano che indica se l'indice sulla griglia è più o meno sensato
    bool pos_griglia_ok; //si inizializzano nella getMousePosGrigliaXY

    //posizione 2d del mouse sulla finestra
    int mouse_x_fin, mouse_y_fin; //si inizializzano nella getMousePosGrigliaXY

    //variabili per la selezione dei pezzi
    Selezione caratteristiche_selezione;
    bool entrambi;
    unsigned x_pezzo_selezionato, y_pezzo_selezionato;
    unsigned x_base_selezionata, y_base_selezionata;

public:

    Livello(Gioco *gioco_aux, int num_x_colonne_aux, int num_y_righe_aux, int frame_rate);

    Livello(const Livello &orig);

    bool getMousePosGrigliaXY(int altezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux);

    bool getMousePosGrigliaXY(int altezza_fin);

    int mouseSelezione(int altezza_fin);

    void setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin, bool reset = false);

    void stampaSuperficeBase();

    virtual int aggiornaStato();

    virtual int gestisciInput(SDL_Event *evento);

    virtual int video();

    int inizializza();
};

#endif	/* _LIVELLO_H */

