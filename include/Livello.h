/* 
 * File:   Livello.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 16.03
 */

#ifndef _LIVELLO_H
#define	_LIVELLO_H

#include "Griglia.h"

enum Proiezione {
    ASSIONOMETRICA, PROSPETTICA
};

class Livello {
protected:
    //matrici dinamiche di pezzi e basi
    Griglia livello_editor;

    //struttura ausiliaria per il movimento della griglia
    PosXYZoom aux_griglia;

    //proiezione della griglia a schermo
    Proiezione tipo_proiezione;

    //per ora sono solo due bottoni ma penso che diventerà una struttura per gestire l'input in maniera
    //differente a seconda che il livello si editor partita o altro
    bool bottone_sinistro, bottone_destro;

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

    Livello(int num_x_colonne_aux, int num_y_righe_aux);

    bool getMousePosGrigliaXY(int larghezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux);

    bool getMousePosGrigliaXY(int larghezza_fin);
};

#endif	/* _LIVELLO_H */

