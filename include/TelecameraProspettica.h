/* 
 * File:   TelecameraProspettica.h
 * Author: tonegas
 *
 * Created on 14 novembre 2009, 23.38
 */

#ifndef _TELECAMERAPROSPETTICA_H
#define	_TELECAMERAPROSPETTICA_H

#define PROSPETTICA_Z_MAX 960
#define PROSPETTICA_Z_MIN 0
#define PROSPETTICA_DELTA_Z 1.05
#define PROSPETTICA_INCREMENTO_DELTA_Z 1.2
#define PROSPETTICA_FOVY 40
#define PROSPETTICA_ZFAR 20000
#define PROSPETTICA_ZNEAR 1
#define PROSPETTICA_Z_TELECAMERA 1000
#define PROSPETTICA_Y_TELECAMERA 0
#define PROSPETTICA_X_TELECAMERA 0
#define PROSPETTICA_MAX_ANGOLO_TELECAMERA 70

#include "Domino.h"

class TelecameraProspettica : public Telecamera {
    PosTeleProsp posizione_telecamera_iniziale;
    PosTeleProsp posizione_telecamera;

    //posizione 3d del mouse rispetto alla griglia ausiliaria
    //variabili per lo spostamento della griglia
    GLdouble pos_x_iniziale_griglia_iniziale, pos_y_iniziale_griglia_iniziale;
    GLdouble pos_x_griglia_iniziale, pos_y_griglia_iniziale, pos_z_griglia_iniziale;

    //posizione 3d iniziali del mouse per lo spostamento della griglia
    GLdouble pos_x_iniziali_griglia, pos_y_iniziali_griglia; //questi si inizializzano da soli quando premo
    GLdouble pos_x_iniziali, pos_y_iniziali; //questi si inizializzano da soli quando premo
    //flag che indica se è incorso un animazione sullo zoom
    bool mouvi_z; //inizializzati nella setProiezione
    //massimo livello di zoom per la proiezione corrente
    GLfloat max_z, min_z; //inizializzati nella setProiezione
    //variazione del delta di incremento dello zoom
    GLfloat delta_z; //ok
    //tempo per il reset del delta_zoom
    int tempo_reset_delta_z; //ok

public:

    TelecameraProspettica();

    TelecameraProspettica(const TelecameraProspettica& orig);

    TelecameraProspettica(PosTeleProsp &pos_tele_aux);

    void setProiezioneTelecamera(int larghezza_fin, int altezza_fin);

    bool getMousePosGrigliaXY(unsigned dim_grilia_X, unsigned dim_grilia_Y);

    bool getMousePosGrigliaXYIniziale(unsigned dim_grilia_X, unsigned dim_grilia_Y);

    bool mouseSelezione(Livello *liv, Griglia* griglia_livello);

    void registraPosizioneMovimento(int mouse_x_fin_aux, int mouse_y_fin_aux, unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void registraPosizioneRotazione(int mouse_x_fin_aux, int mouse_y_fin_aux, unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void cambiaXY(int mouse_x_fin_aux, int mouse_y_fin_aux, unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void cambiaAngolazione(int mouse_x_fin_aux, int mouse_y_fin_aux, unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void registraZoomAvanti();

    void registraZoomIndietro();

    void animaZoom();

    void controlloPosizione(unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void resettaDeltaZoom(int frame_ms);

    void visualeOpenGL();

    void visualeOpenGLIniziale();
};


#endif	/* _TELECAMERAPROSPETTICA_H */

