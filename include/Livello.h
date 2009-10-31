/* 
 * File:   Livello.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 16.03
 */

#ifndef _LIVELLO_H
#define	_LIVELLO_H

#include "Domino.h"

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
#define DELTA_ZOOM 1.1
#define INCREMENTO_DELTA_ZOOM 1.1

enum Proiezione {
    ASSIONOMETRICA, PROSPETTICA
};

const GLfloat cavalier[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    -0.5, -0.5, 1, 0,
    0, 0, 0, 1
};

class Gioco;

class Livello {
protected:
    //puntatore al gioco per interagire sulle funzionidi gioco
    Gioco *gioco;

    //matrici dinamiche di pezzi e basi
    Griglia griglia_livello;

    //flag che indica se è incorso un animazione sullo zoom
    bool mouvi_zoom;
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom aux_griglia;

    //proiezione della griglia a schermo
    Proiezione tipo_proiezione;
    //massimo livello di zoom per la proiezione corrente
    GLfloat max_zoom,min_zoom;
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom griglia_assionometrica;
    //struttura ausiliaria per il movimento della griglia
    PosXYZoom griglia_prospettica;
    //modifica degli angoli di vista della telecamera
    GLfloat angolo_telecamera_x,angolo_telecamera_y;
    GLfloat angolo_telecamera_x_iniziale,angolo_telecamera_y_iniziale;


    //per ora sono solo due bottoni ma penso che diventerà una struttura per gestire l'input in maniera
    //differente a seconda che il livello si editor partita o altro
    bool bottone_sinistro, bottone_destro, bottone_centrale;

    //variazione del delta di incremento dello zoom
    GLfloat delta_zoom;
    //tempo per il reset del delta_zoom
    int tempo_reset_delta_zoom;
    //velocita di frame rate per temporizzare le cose
    int frame_rate;

    //matrici per il recupero dell'input del muose
    //inizializzate della classe che deriva livello
    GLdouble matrice_model[16];
    GLdouble matrice_proj[16];
    GLint matrice_view[4];

    //posizione z della superfice base di sfondo
    GLdouble superfice_z;

    //posizione 3d del mouse
    GLdouble pos_x, pos_y, pos_z;
    //posizione 3d iniziali del mouse per lo spostamento della griglia
    GLdouble pos_x_iniziali, pos_y_iniziali;

    //indice sulla griglia del mouse
    int pos_x_griglia, pos_y_griglia;
    //indicatore booleano che indica se l'indice sulla griglia è più o meno sensato
    bool pos_griglia_ok;

    //posizione 2d del mouse sulla finestra
    int mouse_x_fin, mouse_y_fin;

public:

    Livello(int num_x_colonne_aux, int num_y_righe_aux,int frame_rate);

    bool getMousePosGrigliaXY(int larghezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux);

    bool getMousePosGrigliaXY(int larghezza_fin);

    void setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin);

    virtual int aggiornaStato();

    virtual int gestisciInput(SDL_Event *evento);
    
};

#endif	/* _LIVELLO_H */

