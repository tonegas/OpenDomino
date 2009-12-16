/* 
 * File:   MenuAttivo.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 18.32
 */

#ifndef _MENUATTIVO_H
#define	_MENUATTIVO_H

enum StatoMenu {
    PRINCIPALE,
    //:::::::::::::::::::::::::::::::::::::::::::::::::
    /**/ TORNA_INDIETRO,
    /**/ CONTINUA_PARTITA,
    /**/ SCEGLI_LIVELLO,
    /*   */ SL_LIVELLO,
    /**/ GESTIONE_LIVELLI,
    /*   */ GEL_NUOVO_LIVELLO,
    /*      */ GEL_NL_NOME_LIVELLO,
    /*      */ GEL_NL_DIMX_LIVELLO,
    /*      */ GEL_NL_DIMY_LIVELLO,
    /*      */ GEL_NL_CREA_LIVELLO,
    /*   */ GEL_SCEGLI_LIVELLO,
    /*      */ GEL_SL_LIVELLO,
    /*   */ GEL_ELIMINA_LIVELLO,
    //---------------

    OPZIONI = 12,

    GESTIONE_PROFILI = 13,
    GP_GESTIONE_PROFILI = 135,
    //---------------
    GP_NUOVO_PROFILO = 130,
    GP_NP_NUOVO_PROFILO = 1302, GP_NP_CREA_PROFILO = 1300, GP_NP_TORNA_INDIETRO = 1301,

    GP_CAMBIA_PROFILO = 131,
    GP_CP_CAMBIA_PROFILO = 1311, GP_CP_TORNA_INDIETRO = 1310,

    GP_COPIA_PROFILO_ATTUALE = 132,
    GP_CPA_COPIA_PROFILO_ATTUALE = 1322, GP_CPA_CREA_COPIA_PROFILO = 1320, GP_CPA_TORNA_INDIETRO = 1321,

    GP_ELIMINA_PROFILO = 133,
    GP_EL_ELIMINA_PROFILO = 1331, GP_EL_TORNA_INDIETRO = 1330,

    GP_TORNA_A_MENU_PRINCIPALE = 134,
    //----------------

    ISTRUZIONI = 14,

    RINGRAZIAMENTI = 15,

    ESCI = 16,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    SECONDO = 2,
    EL_EDITOR_LIVELLO = 25,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    EL_PROVA_LIVELLO = 20,

    EL_SALVA_LIVELLO = 21,

    EL_SALVA_LIVELLO_CON_NOME = 22,
    EL_SLCN_SALVA_LIVELLO_CON_NOME = 222, EL_SLCN_SALVA_LIVELLO = 220, EL_SLCN_TORNA_INDIETRO = 221,

    EL_CAMBIA_LIVELLO = 23,
    EL_CL_CAMBIA_LIVELLO = 231, EL_CL_TORNA_INDIETRO = 230,

    EL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 24,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::

    TERZO = 3,
    GL_GIOCA_LIVELLO = 33,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    GL_SALVA_LIVELLO = 30,

    GL_CAMBIA_LIVELLO = 31,
    GL_CL_CAMBIA_LIVELLO = 311, GL_CL_TORNA_INDIETRO = 310,

    GL_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 32,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::

    QUARTO = 4,
    ELP_EDITOR_LIVELLO_PROVA = 42,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    ELP_TORNA_EDITOR = 40,

    ELP_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE = 41,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::

    QUINTO = 5,
    PAUSA = 51
};

enum TipoMenu {
    MENU_CENTRALE,
    MENU_LATERALE_SCORRIMENTO,
    MENU_INSERISCI_PAROLA,
    MENU_CREA_LIVELLO
};

#include "Domino.h"

class MenuAttivo {
protected:
    FTPixmapFont *font;
    FTSimpleLayout *layout;

    unsigned dim_x_fin, dim_y_fin;

    unsigned numero_voci_menu_attivo;
    unsigned voce_selezionata;
    QString titolo;
    QStringList voci_menu;
    QVector<StatoMenu> stati_menu;
    QVector<bool> stati_menu_selezionabili;
    QVector<float> stato_attivo_voci_menu;
    QVector<FTBBox> caselle_menu_attivo;
    QVector<FTPoint> posizioni_caselle_menu_attivo;

    int dim_voce_principale, dist_da_basso_voce_principale;
    int dim_voce, dist_da_voce_principale_voce, dist_da_voce;

    unsigned prima_voce_visibile;
    unsigned voci_visibili;
    int posizione_voci_visibili;

public:

    TipoMenu tipo;

    MenuAttivo();

    void setCarattere(FTPixmapFont *font_aux, FTSimpleLayout *layout_aux);

    void inserisci(QString voce, StatoMenu stato, bool attivo = true);

    void inserisci(QStringList lista_voci, StatoMenu stato);

    void azzera();

    void resize(unsigned dim_x, unsigned dim_y);

    void resize();

    StatoMenu statoSelezionato();

    void incrementoSelezione();

    void decrementoSelezione();

    unsigned getVoceSelezionata();

    void aggiorna();

    virtual QString getStringa();

    virtual bool gestisciSelezioneMouse(unsigned pos_mouse_x, unsigned pos_mouse_y);

    virtual void aggiornaMovimento() {
    }

    virtual void aggiornaMovimento(unsigned pos_mouse_x, unsigned pos_mouse_y);

    virtual void resizeAggiuntivo() {
    }

    virtual void costruisciCaselle() = 0;

    virtual void stampa() = 0;
};

#endif	/* _MENUATTIVO_H */

