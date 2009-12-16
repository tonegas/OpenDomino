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


//questa mi seve qua ma poi va tolta

#include "Domino.h"

class Menu : public Interfaccia {
    GestoreGiocatori *gestore_giocatori;
    MenuAttivo* menu_attuale;
    MenuCentrale menu_centrale;
    MenuLaterale menu_laterale;
    MenuCreaLivello menu_crea_livello;
    MenuInserisciParola menu_inserisci_parola;

    QStringList nomi_giocatori;
    QStringList lista_livelli;

    QString nuovo_nome;
    QString dim_x_nuovo_livello;
    QString dim_y_nuovo_livello;

    //variabili per scrivere
    FTPixmapFont *font;
    FTSimpleLayout layout;

    unsigned dim_x_fin, dim_y_fin;

    int dim_nome, dist_da_destra_nome, dist_da_alto_nome;

    unsigned prima_voce_visibile;
    unsigned voci_visibili;
    int posizione_voci_visibili;


    //variabili di stato
    StatoMenu stato;
    StatoMenu stato_cambio_posticipato;
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

    QStringList pausa;

//    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu);
//    void inizializzaVariabiliMenu(StatoMenu nuovo_stato, QStringList nuove_voci_menu, unsigned numero_voci_in_piu);

//    void costruisciCaselleMenuCentrale();
//    void costruisciCaselleMenuLaterale();
//    void costruisciCaselleMenuCrea();

    void cambiaVociMenu();
    //:::::::::::::::::::::::::::::::
    void cambiaVociMenuPrincipale();
    void cambiaVociMenuGioca();
    void cambiaVociMenuGScegliLivello();
    void cambiaVociMenuGestioneLivelli();
    void cambiaVociMenuGeLNuovoLivello();
    void cambiaVociMenuGeLScegliLivello();
    void cambiaVociMenuGeLEliminaLivello();
    void cambiaVociMenuGestioneProfili();
    void cambiaVociMenuGPNuovoProfilo();
    void cambiaVociMenuGPCambiaProfilo();
    void cambiaVociMenuGPCopiaProfiloAttuale();
    void cambiaVociMenuGPEliminaProfilo();
    //:::::::::::::::::::::::::::::::::
    void cambiaVociMenuELEditorLivelli();
    void cambiaVociMenuELSalvaConNome();
    void cambiaVociMenuELCambiaLivello();
    //:::::::::::::::::::::::::::::::::
    void cambiaVociMenuGLGiocaLivello();
    void cambiaVociMenuGLCambiaLivello();
    //:::::::::::::::::::::::::::::::::
    void cambiaVociMenuELPEditorLivelloProva();


//    bool gestisciSelezioneMouse();
//    bool gestisciSelezioneMouseMenuLaterale();
    void gestisciInput();

    void stampa();
    void stampaGiocatoreAttuale();
//    void stampaMenuCentrale();
//    void stampaMenuLaterale();
//    void stampaMenuCreaLivello();
//    void stampaMenuInserisciParola();

//    void aggiornaStatoAttivoVociMenu();
//    void aggiornaStatoAttivoVociMenuLaterale();
//    void aggiornaStatoAttivoVociMenuLateraleMouse();

public:
    Menu(unsigned dim_x_fin_aux, unsigned dim_y_fin_aux);
    ~Menu();
    void setStato(StatoMenu nuovo_stato);
//    void setStatoCambioPosticipato(StatoMenu nuovo_stato);
    void resize(unsigned dim_x, unsigned dim_y);
    void resize();
    StatoMenu getStato();
    void cicloGioco();
};

#endif	/* _MENU_H */

