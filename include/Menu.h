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
    //:::::::::::::::::::::::::::::::::::::::::::::::::
    GIOCA = 10,
    G_GIOCA = 103,
    //---------------
    G_CONTINUA = 100,

    G_SCEGLI_LIVELLO = 101,
    G_SL_SCEGLI_LIVELLO = 1011, G_SL_TORNA_A_MENU_PRINCIPALE = 1010,

    G_TORNA_A_MENU_PRINCIPALE = 102,
    //---------------

    GESTIONE_LIVELLI = 11,
    GEL_GESTIONE_LIVELLI = 115,
    //---------------
    GEL_NUOVO_LIVELLO = 110,
    GEL_NL_NUOVO_LIVELLO = 1102, GEL_NL_CREA_LIVELLO = 1100, GEL_NL_TORNA_GESTIONE_LIVELLI = 1101,

    GEL_SCEGLI_LIVELLO = 111,
    GEL_SL_SCEGLI_LIVELLO = 1111, GEL_SL_TORNA_GESTIONE_LIVELLI = 1110,

    GEL_ELIMINA_LIVELLO = 113,
    GEL_EL_ELIMINA_LIVELLO = 1131, GEL_EL_TORNA_GESTIONE_LIVELLI = 1130,

    GEL_TORNA_A_MENU_PRINCIPALE = 114,
    //---------------

    OPTION = 12,

    GESTIONE_PROFILI = 13,
    GP_GESTIONE_PROFILI = 135,
    //---------------
    GP_NUOVO_PROFILO = 130,
    GP_NP_NUOVO_PROFILO = 1302, GP_NP_CREA_PROFILO = 1300, GP_NP_TORNA_A_MENU_GESTIONE_PROFILI = 1301,

    GP_CAMBIA_PROFILO = 131,
    GP_CP_CAMBIA_PROFILO = 1311, GP_CP_TORNA_A_MENU_GESTIONE_PROFILI = 1310,

    GP_COPIA_PROFILO_ATTUALE = 132,
    GP_CPA_COPIA_PROFILO_ATTUALE = 1322, GP_CPA_CREA_COPIA_PROFILO = 1320, GP_CPA_TORNA_A_MENU_GESTIONE_PROFILI = 1321,

    GP_ELIMINA_PROFILO = 133,
    GP_EL_ELIMINA_PROFILO = 1331, GP_EL_TORNA_A_MENU_GESTIONE_PROFILI = 1330,

    GP_TORNA_A_MENU_PRINCIPALE = 134,
    //----------------

    ISTRUZIONI = 14,

    RINGRAZIAMENTI = 15,

    ESCI = 16,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::

    EL_EDITOR_LIVELLO = 25,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    EL_PROVA_LIVELLO = 20,

    EL_SALVA_LIVELLO = 21,

    EL_SALVA_LIVELLO_CON_NOME = 22,
    EL_SLCN_SALVA_LIVELLO_CON_NOME = 222, EL_SLCN_SALVA_LIVELLO = 220, EL_SLCN_TORNA_MENU_PRECEDENTE = 221,

    EL_CAMBIA_LIVELLO = 23,
    EL_CL_CAMBIA_LIVELLO = 231, EL_SLCN_TORNA_MENU_PRECEDENTE = 230,

    EL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 24,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::

    GL_GIOCA_LIVELLO = 33,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    GL_SALVA_LIVELLO = 30,

    GL_CAMBIA_LIVELLO = 31,
    GL_CL_CAMBIA_LIVELLO = 311, GL_SLCN_TORNA_MENU_PRECEDENTE = 310,

    GL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 32,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::

    ELP_EDITOR_LIVELLO_PROVA = 42,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    ELP_TORNA_EDITOR = 40,

    ELP_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 41
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
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
    QStringList lista_livelli;
    //Gioco* gioco;

    QString nome_nuovo_giocatore;
    QString nome_nuovo_livello;

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
    //::::::::::::::::::::::::::::::::::
    QStringList voci_menu_gioca;
    QStringList voci_menu_g_scegli_livello;

    QStringList voci_menu_gestione_livelli;
    QStringList voci_menu_gel_nuovo_livello;
    QStringList voci_menu_gel_scegli_livello;
    QStringList voci_menu_gel_elimina_livello;

    QStringList voci_menu_gestione_profili;
    QStringList voci_menu_gp_nuovo_profilo;
    QStringList voci_menu_gp_cambia_profilo;
    QStringList voci_menu_gp_copia_profilo_attuale;
    QStringList voci_menu_gp_elimina_profilo;
    //::::::::::::::::::::::::::::::::::

    QStringList voci_menu_el_editor_livello;
    //::::::::::::::::::::::::::::::::::
    QStringList voci_menu_el_salva_con_nome;
    QStringList voci_menu_el_cambia_livello;
    //::::::::::::::::::::::::::::::::::

    QStringList voci_menu_gl_gioca_livello;
    //::::::::::::::::::::::::::::::::::
    QStringList voci_menu_gl_cambia_livello;
    //::::::::::::::::::::::::::::::::::

    QStringList voci_menu_elp_editor_livello_prova;

    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu);
    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu, unsigned numero_voci_in_piu);

    void costruisciCaselleMenuCentrale();
    void costruisciCaselleMenuLaterale();
    void costruisciCaselleMenuCrea();

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
    void stampaMenuCreaLivello();
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

