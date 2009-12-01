/* 
 * File:   TelecameraProspettica.h
 * Author: tonegas
 *
 * Created on 14 novembre 2009, 23.38
 */

#ifndef _TELECAMERAPROSPETTICA_H
#define	_TELECAMERAPROSPETTICA_H

#define PROSPETTICA_Z_MAX 1950
#define PROSPETTICA_Z_MIN 0
#define PROSPETTICA_DELTA_Z 20
#define PROSPETTICA_INCREMENTO_DELTA_Z 1.5
#define PROSPETTICA_FOVY 25
#define PROSPETTICA_ZFAR 12000
#define PROSPETTICA_ZNEAR 1
#define PROSPETTICA_Z_TELECAMERA 2000
#define PROSPETTICA_Y_TELECAMERA 0
#define PROSPETTICA_X_TELECAMERA 0
#define PROSPETTICA_MAX_ANGOLO_TELECAMERA 70

#include "Domino.h"

class TelecameraProspettica : public Telecamera {
    PosTeleProsp posizione_telecamera_iniziale;
    PosTeleProsp posizione_telecamera;
    //flag che indica se è incorso un animazione sullo zoom

    //posizione 3d iniziali del mouse per lo spostamento della griglia
    GLdouble pos_x_griglia_iniziale, pos_y_griglia_iniziale; //questi si inizializzano da soli quando premo
    //posizione 3d iniziali del mouse per la rotazione della griglia
    GLdouble pos_x_iniziale, pos_y_iniziale; //questi si inizializzano da soli quando premo

    bool mouvi_z; //inizializzati nella setProiezione
    //massimo livello di zoom per la proiezione corrente
    GLfloat max_z, min_z; //inizializzati nella setProiezione
    //variazione del delta di incremento dello zoom
    GLfloat delta_z; //ok
    //tempo per il reset del delta_zoom
    int tempo_reset_delta_z; //ok

public:

    TelecameraProspettica(unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux);

    TelecameraProspettica(const TelecameraProspettica& orig);

    TelecameraProspettica(PosTeleProsp &pos_tele_aux, unsigned dim_grilia_X_aux, unsigned dim_grilia_Y_aux);

    void setProiezioneTelecamera(int larghezza_fin, int altezza_fin);

    bool getMousePosGrigliaXY();

    bool getMousePosGrigliaXYIniziale();

    bool mouseSelezione(Livello *liv, Griglia* griglia_livello);

    void registraPosizione();

    void registraZoomAvanti();

    void registraZoomIndietro();

    void cambiaXY();

    void cambiaAngolazione();

    void animaZoom();

    void controlloPosizione();

    void resettaDeltaZoom(int frame_ms);

    void visualeOpenGL();

    void visualeOpenGLIniziale();

    void configuraVisuale();
};


#endif	/* _TELECAMERAPROSPETTICA_H */

