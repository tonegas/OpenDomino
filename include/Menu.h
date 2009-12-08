/* 
 * File:   Menu.h
 * Author: tonegas
 *
 * Created on 25 novembre 2009, 1.03
 */

#ifndef _MENU_H
#define	_MENU_H

#include "Domino.h"

using namespace std;

class GestoreGiocatori;
class Interfaccia;

//questa mi seve qua ma poi va tolta

enum StatoMenu {
    PRINCIPALE = 17,
    CONTINUA_LIVELLO = 10,

    CL_CONTINUA_LIVELLO = 103, CL_CONTINUA = 100, CL_SALVA_LIVELLO = 101, CL_TORNA_A_MENU_PRINCIPALE = 102,

    LISTA_LIVELLI_EDITOR = 11,
    OPTION = 12,
    GESTIONE_PROFILI = 13,

    GP_GESTIONE_PROFILI = 135,
    GP_NUOVO_PROFILO = 130,

    GP_NP_NUOVO_PROFILO = 1302, GP_NP_CREA_PROFILO = 1300, GP_NP_TORNA_A_MENU_GESTIONE_PROFILI = 1301,

    GP_CAMBIA_PROFILO = 131,

    GP_CP_CAMBIA_PROFILO = 1311, GP_CP_TORNA_A_MENU_GESTIONE_PROFILI = 1310,

    GP_COPIA_PROFILO_ATTUALE = 132,

    GP_CPA_COPIA_PROFILO_ATTUALE = 1322, GP_CPA_CREA_COPIA_PROFILO = 1320, GP_CPA_TORNA_A_MENU_GESTIONE_PROFILI = 1321,

    GP_ELIMINA_PROFILO = 133,

    GP_EL_ELIMINA_PROFILO = 1331, GP_EL_TORNA_A_MENU_GESTIONE_PROFILI = 1330,

    GP_TORNA_A_MENU_PRINCIPALE = 134,
    ISTRUZIONI = 14,
    RINGRAZIAMENTI = 15,
    ESCI = 16
};

class Menu : public Interfaccia {
    unsigned dim_x_fin, dim_y_fin;

    int dim_nome, dist_da_destra_nome, dist_da_alto_nome;
    int dim_voce_principale, dist_da_basso_voce_principale;
    int dim_voce, dist_da_voce_principale_voce, dist_da_voce;
    int dist_da_sinistra, dist_da_basso_voce_uscita;

    unsigned prima_voce_visibile;
    unsigned voci_visibili;
    int posizione_voci_visibili;

    //variabili per interagire con il mondo
    GestoreGiocatori *gestore_giocatori;
    QStringList nomi_giocatori;
    //Gioco* gioco;

    QString nome_nuovo_giocatore;

    //    //variabili per scrivere
    FTPixmapFont *font;
    FTSimpleLayout layout;

    //variabili di stato
    StatoMenu stato;
    //unsigned numero_max_voci_visibili;

    unsigned stato_attivo;
    QVector<float> stato_attivo_voci_menu;
    QVector<float> trasparenza_voci_visibili;
    unsigned numero_voci_menu_attivo;
    QStringList voci_menu_attivo;
    QVector<FTBBox> caselle_menu_attivo;
    QVector<FTPoint> posizioni_caselle_menu_attivo;

    QStringList voci_menu_principale;
    QStringList voci_menu_continua_livello;
    QStringList voci_menu_gestione_profili;
    QStringList voci_menu_gp_cambia_profilo;
    QStringList voci_menu_gp_copia_profilo_attuale;
    QStringList voci_menu_gp_elimina_profilo;
    QStringList voci_menu_gp_nuovo_profilo;

    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu);
    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu, unsigned numero_voci_in_piu);

    void costruisciCaselleMenuCentrale();
    void costruisciCaselleMenuLaterale();
    void costruisciCaselleMenuCreaProfilo();

    void cambiaVociMenu();
    void cambiaVociMenuPrincipale();
    void cambiaVociMenuContinuaLivello();
    void cambiaVociMenuGestioneProfili();
    void cambiaVociMenuGPNuovoProfilo();
    void cambiaVociMenuGPCambiaProfilo();
    void cambiaVociMenuGPCopiaProfiloAttuale();
    void cambiaVociMenuGPEliminaProfilo();

    bool gestisciSelezioneMouse();
    bool gestisciSelezioneMouseMenuLaterale();
    void gestisciInput();

    void stampa();
    void stampaGiocatoreAttuale();
    void stampaMenuCentrale();
    void stampaMenuLaterale();
    void stampaMenuCreaProfilo();

    void aggiornaStatoAttivoVociMenu();
    void aggiornaStatoAttivoVociMenuLaterale();
    void aggiornaStatoAttivoVociMenuLateraleMouse();

public:
    Menu(unsigned dim_x_fin_aux, unsigned dim_y_fin_aux);
    ~Menu();
    void setStato(StatoMenu nuovo_stato);
    void resize(unsigned dim_x, unsigned dim_y);
    StatoMenu getStato();
    void cicloGioco();
};

#endif	/* _MENU_H */

