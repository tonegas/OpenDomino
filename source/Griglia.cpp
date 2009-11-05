/* 
 * File:   Griglia.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.53
 */

#include "../include/Griglia.h"

Griglia::Griglia(int num_x_colonne_aux, int num_y_righe_aux) {
    testa_elementi = NULL;
    num_y_righe = num_y_righe_aux;
    num_x_colonne = num_x_colonne_aux;
    matrice_elementi = new ElementoAttivo* *[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_elementi[i] = new ElementoAttivo* [num_y_righe];
    }
}

Griglia::~Griglia() {
    for (unsigned i = 0; i < num_x_colonne; i++) {
        delete [] matrice_elementi[i];
    }
    delete [] matrice_elementi;

    ElementoAttivo *aux = testa_elementi;
    testa_elementi = aux->next;
    while (aux != NULL) {
        delete aux;
        aux = testa_elementi;
        testa_elementi = aux->next;
    }
}

void Griglia::pulisciGriglia() {
    ElementoAttivo *aux = testa_elementi;
    testa_elementi = aux->next;
    while (aux != NULL) {
        matrice_elementi[aux->x][aux->y] = NULL;
        delete aux;
        aux = testa_elementi;
        testa_elementi = aux->next;
    }
}

void Griglia::inserisciElemento(Elemento *elem, int x, int y, TipoElemento tipo) {
    if (matrice_elementi[x][y] == NULL) {
        if (testa_elementi != NULL) {
            ElementoAttivo *aux = testa_elementi;
            testa_elementi = new ElementoAttivo(elem, x, y, tipo, aux);
            aux->prev = testa_elementi;
        } else {
            testa_elementi = new ElementoAttivo(elem, x, y, tipo);
        }
    } else {
        matrice_elementi[x][y] -> tipo = tipo;
        matrice_elementi[x][y] -> elem = elem;
    }
}

//-------------------------------------------------------------------------------------

//Griglia::Griglia(const Griglia& orig) {
//    griglia = orig.griglia;
//    num_y_righe = orig.num_y_righe;
//    num_x_colonne = orig.num_x_colonne;
//    matrice_elementi = new ElementoAttivo* *[num_x_colonne];
//    for (unsigned i = 0; i < num_x_colonne; i++) {
//        matrice_elementi[i] = new ElementoAttivo* [num_y_righe];
//    }
//    Elemen
//
//
//}
//
//    if (orig.testa != NULL) {
//        if(orig.testa->getOccupato())
//            if(orig.)
//            testa = new ElementoAttivo(orig.testa->getX(), orig.testa->getY(), orig.testa->getTipo());
//        matrice_posizioni[orig.testa->elem->getX()][orig.testa->elem->getY()].occupaPosizione(testa);
//        testa->prev = NULL;
//        ElementoAttivo *aux_orig = orig.testa;
//        ElementoAttivo *aux = testa;
//        while (aux_orig->next != NULL) {
//            aux->next = new ElementoAttivo(aux->next->elem->getX(), aux->next->elem->getY(), aux->next->tipo);
//            matrice_posizioni[orig.testa->elem->getX()][orig.testa->elem->getY()].occupaPosizione(aux->next);
//            aux->next->prev = aux;
//            aux = aux->next;
//            aux_orig = aux->next;
//        }
//        aux->next = NULL;
//    } else {
//        testa = NULL;
//    }
//}


//funzione per inserire dei pezzi
// se torna 0 ok altrimenti errore

int Griglia::inserisci(Elemento *elem, int x, int y, TipoElemento tipo) {
    if (testa_elementi != NULL) {
        ElementoAttivo *aux = testa_elementi;
        testa_elementi = new ElementoAttivo(elem, x, y, tipo, aux);
        aux->prev = testa_elementi;
    } else {
        testa_elementi = new ElementoAttivo(elem, x, y, tipo);
    }
    if (matrice_elementi[x][y] == NULL) {
        matrice_elementi[x][y] = testa_elementi;
        return 0;
    } else {
        return 1;
    }
}

//funzione per inserire delle selezioni

void Griglia::inserisci(int x, int y, TipoElemento tipo) {
    if (testa_elementi != NULL) {
        ElementoAttivo *aux = testa_elementi;
        testa_elementi = new ElementoAttivo(x, y, tipo, aux);
        aux->prev = testa_elementi;
    } else {
        testa_elementi = new ElementoAttivo(x, y, tipo);
    }
    matrice_elementi[x][y] = testa_elementi;
}

//funzione per iserire dei pezzi se è già allocata la selezione

void Griglia::inserisci(Elemento *elem, ElementoAttivo *elem_lista) {
    elem_lista -> elem = elem;
}

void Griglia::estrazione(ElementoAttivo *elem_lista) {
    if (elem_lista->prev == NULL) {
        testa_elementi = elem_lista->next;
        if (testa_elementi != NULL) {
            testa_elementi->prev = NULL;
        }
    } else {
        elem_lista->prev->next = elem_lista->next;
        if (elem_lista->next != NULL) {
            testa_elementi->next->prev = elem_lista->prev;
        }
    }
    matrice_elementi[elem_lista->x][elem_lista->y] = NULL;
    delete elem_lista;
}

PosXYZoom Griglia::getGriglia() {
    return griglia;
}

void Griglia::attivaSelezione(int x, int y, TipoElemento tipo) {
    if (matrice_elementi[x][y] != NULL) {
        matrice_elementi[x][y].selezione = 1;
        matrice_elementi[x][y].tipo = tipo;
    } else {
        inserisci(x, y, tipo);
    }
}

GLfloat Griglia::getSelezione(int x, int y) {
    return matrice_elementi[x][y].selezione;
}

void Griglia::aggiornaSelezione(int x, int y) {
    matrice_elementi[x][y].selezione - 0.05;
}

void Griglia::liberaPosizione(int x, int y) {
    estrazione(matrice_elementi[x][y]);
}

bool Griglia::getOccupata(int x, int y) {
    return matrice_elementi[x][y]->getOccupato();
}

TipoElemento Griglia::getTipo(int x, int y) {
    return matrice_elementi[x][y]->tipo;
}

//ritorna zero significa che non è andata a buon fine

int Griglia::occupaPosizione(int x, int y, TipoElemento tipo, bool selezione) {
    switch (tipo) {
        case ELEM_PEZZO:
            inserisci(new Pezzo(x, y), x, y, tipo);
            break;
        case ELEM_BASE:
            inserisci(new Base(x, y), x, y, tipo);
            break;

    }
    if (selezione) {

    } else {

    }
    Posizione *aux_pos = matrice_elementi[x][y];
    if (aux_pos->elem_lista) {
        if (aux_pos->occupata) {
            return 0;
        } else {
            aux_pos->elem_lista->tipo = tipo;
        }
    } else {
        switch (tipo) {
            case ELEM_PEZZO:
                inserisci(new Pezzo(x, y));
                break;
            case ELEM_BASE:
                inserisci(new Base(x, y));
                break;
        }
    }
    if (selezione) {
        aux_pos->elem_lista->elem->attivaSelezione();
    }
}

//Posizione* Griglia::getPosizione(int i, int j) {
//    return &matrice_posizioni[i][j];
//}
//
//Pezzo& Griglia::getPezzo(int i, int j) {
//    return *(Pezzo*) matrice_posizioni[i][j].elem;
//}
//
//Base& Griglia::getBase(int i, int j) {
//    return *(Base*) matrice_posizioni[i][j].elem;
//}

void Griglia::setGrigliaZoom(GLfloat zoom) {
    griglia.zoom = zoom;
}

void Griglia::setGrigliaXY(GLfloat x, GLfloat y) {
    griglia.x = x;
    griglia.y = y;
}

unsigned Griglia::getDimGrigliaX() const {
    return num_x_colonne;
}

unsigned Griglia::getDimGrigliaY() const {
    return num_y_righe;
}
