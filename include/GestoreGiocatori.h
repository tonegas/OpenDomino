/* 
 * File:   GestoreGiocatori.h
 * Author: tonegas
 *
 * Created on 4 dicembre 2009, 16.39
 */

#ifndef _GESTOREGIOCATORI_H
#define	_GESTOREGIOCATORI_H

#include "Domino.h"

class GestoreGiocatori {
    //variabili giocatore attuale
    QFile file_giocatore_attuale;
    QFile* file_giocatore;
    QString nome_giocatore_attuale;
    Giocatore *giocatore_attuale;
    GestoreLivelli gestore_livelli;
    
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

    Giocatore** getGiocatoreAttuale();

    bool nuovoGiocatore(QString nome_giocatore);
    bool copiaGiocatoreAttuale(QString nome_giocatore);
    bool cambiaGiocatore(QString nome_giocatore);
    bool eliminaGiocatore(QString nome_giocatore);
    void eliminaGiocatore();
    void salvaGiocatore();

    void salvaLivelloGiocatore();

    QString nomeGiocatoreAttuale();
    QStringList nomiGiocatori();
};

#endif	/* _GESTOREGIOCATORI_H */

