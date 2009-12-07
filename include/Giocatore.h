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
class Interfaccia;

enum StatoGiocatore {
    PARTITA,
    EDITOR_COSTRUISCI,
    EDITOR_TEST
};

class Giocatore : public Interfaccia {
    QString nome;
    time_t tempo_di_gioco_apertura;
    time_t tempo_di_gioco;
    time_t data_di_creazione;

    bool cambia_stato;
    StatoGiocatore stato;
    QString nome_livello_attuale;
    Editor *domino_editor;
    bool partita_allocata;
    Livello *domino;
public:

    Giocatore();
    Giocatore(QString nome_aux);
    Giocatore(QString nome_aux, time_t tempo_di_gioco_aux, time_t data_di_creazione_aux);
    Giocatore(const Giocatore& orig);
    ~Giocatore();
    QString getNome();
    void setNome(QString nuovo_nome);
    time_t getDataDiCreazione();
    time_t getTempoDiGioco();
    time_t getTempoDiGiocoApertura();
    void setTempoDiGiocoApertura();
    void inizializza(Gioco *gioco_aux, SDL_Event *evento_aux);
    StatoGiocatore getStato();
    void setStato(StatoGiocatore stato_aux);
    void riconfiguraVideo();
    void cicloGioco();
    void cicloGiocoStampa();
};


#endif	/* _GIOCATORE_H */

