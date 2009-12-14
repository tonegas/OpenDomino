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
    bool eliminaLivello(QString nome_livello);
    bool copiaLivello(QString old_nome_livello, QString new_nome_livello);
    //----------------------------------------------
    void salvaLivello(StrutturaLivello* livello_aux);
    bool nuovoLivello(StrutturaLivello* livello_aux);
    bool caricaLivello(QString nome_livello, StrutturaLivello* livello_aux);
    QStringList nomiLivelli();
};

#endif	/* _GESTORELIVELLI_H */

