/* 
 * File:   Livello.h
 * Author: tonegas
 *
 * Created on 30 ottobre 2009, 16.03
 */

#ifndef _LIVELLO_H
#define	_LIVELLO_H

//?????????????????????????queste si tolgono
#define H_TELECAMERA 200
#define FOVY    40
#define ZNEAR   1
#define ZFAR    20000

#define MAX_ZOOM_ASSIONOMETRIA 23
#define MIN_ZOOM_ASSIONOMETRIA 0.25

#define MAX_ZOOM_PROSPETTICA 3
#define MIN_ZOOM_PROSPETTICA 0.035
#define MAX_ANGOLO_TELECAMERA_XY 70

#define DELTA_ZOOM 1.1
#define INCREMENTO_DELTA_ZOOM 1.1
//???????????????????????????????

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

    //variabili che sostituiranno quelle con i punti interrogativi
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Telecamera *telecamera_attuale;
    TelecameraAssionometrica tele_assio;
    TelecameraProspettica tele_prosp;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//    //questa roba andra via da questa classe
//    //????????????????????????????????????????????????????????????????????????
//    //flag che indica se è incorso un animazione sullo zoom
//    bool mouvi_zoom; //inizializzati nella setProiezione
//    //struttura ausiliaria per il movimento della griglia
//    PosXYZeZoom aux_griglia; //ok
//    //struttura ausiliaria per il movimento della griglia
//    PosXYZeZoom griglia_prospettica; //ok
//    //struttura ausiliaria per il movimento della griglia
//    PosXYZeZoom griglia_assionometrica; //ok
//    //massimo livello di zoom per la proiezione corrente
//    GLfloat max_zoom, min_zoom; //inizializzati nella setProiezione
//    //variazione del delta di incremento dello zoom
//    GLfloat delta_zoom; //ok
//    //tempo per il reset del delta_zoom
//    int tempo_reset_delta_zoom; //ok
//    //posizione 3d iniziali del mouse per lo spostamento della griglia
//    GLdouble pos_x_iniziali, pos_y_iniziali; //questi si inizializzano da soli quando premo
//    //modifica degli angoli di vista della telecamera
//    GLfloat angolo_telecamera_x, angolo_telecamera_y; //ok
//    GLfloat angolo_telecamera_x_iniziale, angolo_telecamera_y_iniziale; //si inizializzano prima di usarli nella funzione di imput
//
//    //matrici per il recupero dell'input del muose
//    //inizializzate della classe che deriva livello
//    GLdouble matrice_model[16]; //inizializzati nella setProiezione
//    //coordinate sono riferite alla griglia
//    GLdouble matrice_model_griglia[16]; //inizializzata dalla funzione video
//    GLdouble matrice_proj[16]; //inizializzati nella setProiezione
//    GLint matrice_view[4]; //inizializzati nella setProiezione
//
//    //questi li tocca solo livello
//    //-----------------------------------------
//    //posizione 2d del mouse sulla finestra
//    //posizione z della superfice base di sfondo dove cammina il mouse
//    GLdouble mouse_z_fin_double; //inizializzati nella setProiezione
//    int mouse_x_fin, mouse_y_fin; //si inizializzano nella getMousePosGrigliaXY
//    //-----------------------------------------
//
//    //questi li possono usare livello ma anche le classi derivate
//    //----------------------------------
//    //variabili per il posizionamento del mouse nello spazio 3d
//    //posizione 3d del mouse assolute
//    GLdouble pos_x, pos_y, pos_z; //si inizializzano nella getMousePosGrigliaXY
//    //posizione 3d del mouse rispetto alla griglia
//    GLdouble pos_x_griglia, pos_y_griglia, pos_z_griglia;
//    //indice sulla griglia del mouse
//    unsigned indice_x_griglia, indice_y_griglia; //si inizializzano nella getMousePosGrigliaXY
//    //indicatore booleano che indica se l'indice sulla griglia è più o meno sensato
//    bool indice_griglia_ok; //si inizializzano nella getMousePosGrigliaXY
    //---------------------------------

    //questi li possono usare livello ma anche le classi derivate
    //---------------------------
    //variabili per la selezione dei pezzi
    Selezione caratteristiche_selezione;
    //flag che indica se ho selezionato sia
    bool entrambi;
    unsigned x_pezzo_selezionato, y_pezzo_selezionato;
    unsigned x_base_selezionata, y_base_selezionata;
    //---------------------------
    //???????????????????????????????????????????????????????????????????????????????????????????????????????

    void gestisciInput(SDL_Event *evento);

    void aggiornaPosizioneGriglia();

//    int mouseSelezione(int altezza_fin);
//
//    void setProiezione(Proiezione tipo, int larghezza_fin, int altezza_fin, bool reset = false);
//
//    bool getMousePosGrigliaXY(int altezza_fin, int mouse_x_fin_aux, int mouse_y_fin_aux);
//
//    bool getMousePosGrigliaXY(int altezza_fin);

protected:
    virtual void stampaSuperficeBase();

    virtual void stampaSfondo();

    virtual void keyDownF5();

    virtual void attivaSelezioni() {
    }

    virtual void mouseButtonDown(SDL_Event *evento) {
    }

    virtual void mouseMotion() {
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

