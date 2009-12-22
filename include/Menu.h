/* 
 * File:   Menu.h
 * Author: tonegas
 *
 * Created on 25 novembre 2009, 1.03
 */

#ifndef _MENU_H
#define	_MENU_H

class GestoreGiocatori;
class Interfaccia;
class MenuAttivo;
class MenuCentrale;
class MenuLaterale;
class MenuVociDinamiche;

//questa mi seve qua ma poi va tolta

#include "Domino.h"

class Menu : public Interfaccia {
    //puntatore al gestore di giocatori
    GestoreGiocatori *gestore_giocatori;

    //tipologie menu
    MenuAttivo* menu_attuale;
    MenuCentrale menu_centrale;
    MenuLaterale menu_laterale;
    MenuVociDinamiche menu_voci_dinamiche;

    //voci dinamiche menu
    QStringList nomi_giocatori;
    QStringList lista_livelli;
    QStringList stringa_stato_giocatore;
    QString livello_da_eliminare;
    QString profilo_da_eliminare;
    QString nuovo_nome;
    QString dim_x_nuovo_livello;
    QString dim_y_nuovo_livello;

    //informazioni di stato
    int dist_da_destra_nome, dist_da_alto_nome, dim_nome;

    //variabili per scrivere
    FTPixmapFont *font;
    FTSimpleLayout layout;

    //dimensione finestra
    unsigned dim_x_fin, dim_y_fin;

    //variabili di stato
    StatoMenu stato;
    StatoMenu stato_cambio_posticipato;

    void cambiaVociMenu();
    void gestisciInput();

    void stampa();
    void stampaGiocatoreAttuale();
public:
    Menu(unsigned dim_x_fin_aux, unsigned dim_y_fin_aux);
    ~Menu();
    void setStato(StatoMenu nuovo_stato);
    void setStatoCambioPosticipato(StatoMenu nuovo_stato);
    void resize(unsigned dim_x, unsigned dim_y);
    void resize();
    StatoMenu getStato();
    void cicloGioco();
};

#endif	/* _MENU_H */

