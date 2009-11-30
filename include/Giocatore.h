/* 
 * File:   Giocatore.h
 * Author: tonegas
 *
 * Created on 12 novembre 2009, 0.04
 */

#ifndef _GIOCATORE_H
#define	_GIOCATORE_H

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include <QtXml>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QVector>

#include <FTGL/ftgl.h>

using namespace std;

class Giocatore {
    QString nome;
    time_t tempo_di_gioco_apertura;
    time_t tempo_di_gioco;
    time_t data_di_creazione;
public:

    Giocatore() {
        cout << "Costruttore Giocatore\n";
    }
    Giocatore(QString nome_aux);
    Giocatore(QString nome_aux, time_t tempo_di_gioco_aux, time_t data_di_creazione_aux);
    Giocatore(const Giocatore& orig);
    QString getNome();
    void setNome(QString nuovo_nome);
    time_t getDataDiCreazione();
    time_t getTempoDiGioco();
    time_t getTempoDiGiocoApertura();
    void setTempoDiGiocoApertura();
};

class GestoreGiocatori {
    //variabili giocatore attuale
    QFile file_giocatore_attuale;
    QFile* file_giocatore;
    QString nome_giocatore_attuale;
    Giocatore *giocatore_attuale;
    void apriFileGioAttuale();
    void chiudiFileGioAttuale();
    void eliminaFileGioAttuale();
    void apriFileGio();
    void chiudiFileGio();
    void eliminaFileGio();
    void creaFileGiocatoreAttuale(QString nome_giocatore = "__DOMINO__");
    void caricaFileGiocatoreAttuale();
    void creaFileGiocatore();
    void caricaFileGiocatore();
    void salvaFileGiocatore();
public:
    GestoreGiocatori();
    ~GestoreGiocatori();
    bool nuovoGiocatore(QString nome_giocatore);
    bool copiaGiocatoreAttuale(QString nome_giocatore);
    bool cambiaGiocatore(QString nome_giocatore);
    bool eliminaGiocatore(QString nome_giocatore);
    void eliminaGiocatore();
    void salvaGiocatore();
    QString nomeGiocatoreAttuale();
    QStringList nomiGiocatori();
};


#endif	/* _GIOCATORE_H */

