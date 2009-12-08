/* 
 * File:   GestoreLivelli.h
 * Author: tonegas
 *
 * Created on 6 dicembre 2009, 14.36
 */

#ifndef _GESTORELIVELLI_H
#define	_GESTORELIVELLI_H

#include "Domino.h"

class GestoreLivelli {
    //variabili giocatore attuale
    QFile* file_livello;
    StrutturaLivello* livello;

    void apriFileLiv();
    void chiudiFileLiv();
    void eliminaFileLiv();
    void creaFileLivello();
    bool caricaFileLivello();
    void salvaFileLivello();
public:
    GestoreLivelli();
    ~GestoreLivelli();
    //Non le uso
    //----------------------------------------------
    bool nuovoLivello(QString nome_livello, unsigned dim_x, unsigned dim_y);
    bool eliminaLivello(QString nome_livello);
    bool copiaLivello(QString old_nome_livello, QString new_nome_livello);
    QStringList nomiLivelli();
    //----------------------------------------------
    void salvaLivello(StrutturaLivello* livello_aux);
    bool caricaLivello(QString nome_livello, StrutturaLivello* livello_aux);
};

#endif	/* _GESTORELIVELLI_H */

