/* 
 * File:   Giocatore.h
 * Author: tonegas
 *
 * Created on 12 novembre 2009, 0.04
 */

#ifndef _GIOCATORE_H
#define	_GIOCATORE_H

#include "Domino.h"

using namespace std;
class Interfaccia;

enum StatoGiocatore {
    PARTITA,
    EDITOR_COSTRUISCI,
    EDITOR_TEST
};

class Giocatore {
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
    QString getNomeLivello();
    void setNomeLivello(QString nuovo_nome_livello);
    TipoLivello getTipoLivello();
    void setNome(QString nuovo_nome);
    time_t getDataDiCreazione();
    time_t getTempoDiGioco();
    time_t getTempoDiGiocoApertura();
    void setTempoDiGiocoApertura();
    void resize(unsigned dim_x, unsigned dim_y);
    StatoGiocatore getStato();
    void setStato(StatoGiocatore stato_aux);
    void getStrutturaLivello(StrutturaLivello *livello);
    void setStrutturaLivello(StrutturaLivello *livello, TipoLivello tipo);
    void inizializzaVideo();
    void cicloGioco();
    void cicloGiocoStampa();
};


#endif	/* _GIOCATORE_H */

