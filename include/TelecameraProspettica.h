/* 
 * File:   TelecameraProspettica.h
 * Author: tonegas
 *
 * Created on 14 novembre 2009, 23.38
 */

#ifndef _TELECAMERAPROSPETTICA_H
#define	_TELECAMERAPROSPETTICA_H

#define PROSPETTICA_Z_MAX 3
#define PROSPETTICA_Z_MIN 0.035
#define PROSPETTICA_DELTA_Z 1.1
#define PROSPETTICA_INCREMENTO_DELTA_Z 1.1
#define PROSPETTICA_FOVY 40
#define PROSPETTICA_ZFAR 20000
#define PROSPETTICA_ZNEAR 1
#define PROSPETTICA_Z_TELECAMERA 200
#define PROSPETTICA_Y_TELECAMERA 0
#define PROSPETTICA_X_TELECAMERA 0
#define PROSPETTICA_MAX_ANGOLO_TELECAMERA 70

#include "Domino.h"

class TelecameraProspettica : public Telecamera {
    PosTeleProsp aux_posizione_telecamera;
    PosTeleProsp posizione_telecamera;
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

    bool mouseSelezione(Livello *liv, Griglia* griglia_livello);

    void registraPosizione();

    void registraZoomAvanti();

    void registraZoomIndietro();

    void cambiaXY();

    void cambiaAngolazione();

    void animaZoom();

    void controlloPosizione(unsigned dim_grilia_X, unsigned dim_grilia_Y);

    void resettaDeltaZoom(int frame_ms);

    void visualeOpenGL();
};


#endif	/* _TELECAMERAPROSPETTICA_H */

