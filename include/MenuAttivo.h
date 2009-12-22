/* 
 * File:   MenuAttivo.h
 * Author: tonegas
 *
 * Created on 14 dicembre 2009, 18.32
 */

#ifndef _MENUATTIVO_H
#define	_MENUATTIVO_H

enum StatoMenu {
    VUOTA,
    PRINCIPALE,
    //:::::::::::::::::::::::::::::::::::::::::::::::::
    /**/ CONTINUA_PARTITA,
    /**/ SCEGLI_LIVELLO,
    /*   */ LIVELLO_SCELTO_PARTITA,
    /**/ GESTIONE_LIVELLI,
    /*   */ GEL_NUOVO_LIVELLO,
    /*      */ NOME_LIVELLO,
    /*      */ GEL_NL_DIMX_LIVELLO,
    /*      */ GEL_NL_DIMY_LIVELLO,
    /*      */ GEL_NL_CREA_LIVELLO,
    /*   */ GEL_SCEGLI_LIVELLO,
    /*      */ LIVELLO_SCELTO_EDITOR,
    /*   */ GEL_ELIMINA_LIVELLO,
    /*      */ CONFERMA_ELIMINA_LIVELLO_SCELTO,
    /*      */ ELIMINA_LIVELLO_SCELTO,
    /**/ OPZIONI,
    /**/ GESTIONE_PROFILI,
    /*   */ GP_NUOVO_PROFILO,
    /*      */ NOME_PROFILO,
    /*      */ GP_NP_CREA_PROFILO,
    /*   */ GP_CAMBIA_PROFILO,
    /*      */ PROFILO_SCELTO,
    /*   */ GP_COPIA_PROFILO_ATTUALE,
    /*      */ GP_CPA_CREA_PROFILO,
    /*   */ GP_ELIMINA_PROFILO,
    /*      */ CONFERMA_ELIMINA_PROFILO_SCELTO,
    /*      */ ELIMINA_PROFILO_SCELTO,
    /**/ ISTRUZIONI,
    /**/ RINGRAZIAMENTI,
    /**/ ESCI,
    /**/ TORNA_INDIETRO,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    EL_EDITOR_LIVELLO,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    /**/ EL_PROVA_LIVELLO,
    /**/ EL_SALVA_LIVELLO,
    /**/ EL_SALVA_LIVELLO_CON_NOME,
    /*   */ EL_SLCN_SALVA_LIVELLO,
    /*   */ EL_SLCN_TORNA_INDIETRO,
    /**/ EL_CAMBIA_LIVELLO,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    GL_GIOCA_LIVELLO,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    /**/ GL_SALVA_LIVELLO,
    /**/ GL_CAMBIA_LIVELLO,
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::
    ELP_EDITOR_LIVELLO_PROVA,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    /**/ ELP_TORNA_EDITOR,
    /**/ ELP_TORNA_A_MENU_PRINCIPALE_SENZA_SALVARE,
    //::::::::::::::::::::::::::::::::::::::::::::::::::::::
    PAUSA
};

enum TipoMenu {
    MENU_CENTRALE,
    MENU_LATERALE_SCORRIMENTO,
    MENU_VOCI_DINAMICHE
};

#include "Domino.h"

class MenuAttivo {
protected:
    FTPixmapFont *font;
    FTSimpleLayout *layout;

    unsigned dim_x_fin, dim_y_fin;

    unsigned sinistra;
    unsigned sopra;
    unsigned destra;
    unsigned sotto;

    unsigned numero_voci_menu_attivo;
    unsigned voce_selezionata;
    QString titolo;
    QStringList voci_menu;
    QVector<StatoMenu> stati_menu;
    QVector<QString*> voci_dinamiche;
    QVector<bool> stati_menu_attivi;
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

    void inserisci(QString voce, StatoMenu stato = VUOTA, bool attivo = true, bool selezionabile = true);

    void inserisci(QStringList lista_voci, StatoMenu stato);

    void inserisci(QString parte_iniziale_voce, QString* voce_dinamica, StatoMenu stato, bool selezionabile = false);

    void azzera();

    void resize(unsigned dim_x, unsigned dim_y);

    void resize();

    StatoMenu statoSelezionato();

    void incrementoSelezione();

    void decrementoSelezione();

    unsigned getVoceSelezionata();

    void setVoceSelezionata(unsigned num_voce);

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

