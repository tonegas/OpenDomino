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
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            matrice_elementi[i][j] = NULL;
        }
    }
    //questo andra tolto
//    matrice_posizioni = new ElementoAttivo *[num_x_colonne];
//    for (unsigned i = 0; i < num_x_colonne; i++) {
//        matrice_posizioni[i] = new ElementoAttivo [num_y_righe];
//    }
}

Griglia::Griglia(const Griglia& orig) {
    cout << "chiamata" << flush;
    testa_elementi = NULL;
    griglia = orig.griglia;
    num_y_righe = orig.num_y_righe;
    num_x_colonne = orig.num_x_colonne;
    matrice_elementi = new ElementoAttivo* *[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_elementi[i] = new ElementoAttivo* [num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            matrice_elementi[i][j] = NULL;
        }
    }

    ElementoAttivo *orig_aux = orig.testa_elementi;
    ElementoAttivo* prev = NULL;
    ElementoAttivo* tmp;
    testa_elementi = NULL;
    if (orig_aux != NULL) {
        testa_elementi = new ElementoAttivo(*orig_aux);
        testa_elementi->prev = NULL;
        testa_elementi->next = NULL;
        prev = testa_elementi;
        orig_aux = orig_aux->next;
        while (orig_aux != NULL) {
            tmp = new ElementoAttivo(*orig_aux);
            prev->next = tmp;
            tmp->prev = prev;
            tmp->next = NULL;
            matrice_elementi[tmp->x][tmp->y] = tmp;
            prev = tmp;
            orig_aux = orig_aux->next;
        }
    }
    //questo andra tolto
//    matrice_posizioni = new ElementoAttivo *[num_x_colonne];
//    for (unsigned i = 0; i < num_x_colonne; i++) {
//        matrice_posizioni[i] = new ElementoAttivo[num_y_righe];
//    }
//    for (unsigned i = 0; i < num_x_colonne; i++) {
//        for (unsigned j = 0; j < num_y_righe; j++) {
//            if (orig.matrice_posizioni[i][j].getOccupato()) {
//                matrice_posizioni[i][j].elem = orig.matrice_posizioni[i][j].elem->costruttore();
//                matrice_posizioni[i][j].tipo = orig.matrice_posizioni[i][j].tipo;
//            }
//            //            if (orig.matrice_posizioni[i][j].getOccupato()) {
//            //                if (orig.matrice_posizioni[i][j].tipo == ELEM_PEZZO) {
//            //                    matrice_posizioni[i][j].occupaPosizione(new Pezzo(i, j), ELEM_PEZZO);
//            //                } else {
//            //                    matrice_posizioni[i][j].occupaPosizione(new Base(i, j), ELEM_BASE);
//            //                }
//            //            }
//        }
//    }
}

Griglia::~Griglia() {
    for (unsigned i = 0; i < num_x_colonne; i++) {
        delete [] matrice_elementi[i];
    }
    delete [] matrice_elementi;

    ElementoAttivo *aux = testa_elementi;
    while (aux != NULL) {
        testa_elementi = aux->next;
        delete aux;
        aux = testa_elementi;
    }
    //questo andra tolto
//    for (unsigned i = 0; i < num_x_colonne; i++) {
//        delete [] matrice_posizioni[i];
//    }
//    delete [] matrice_posizioni;
}

PosXYZoom Griglia::getGriglia() {
    return griglia;
}

void Griglia::attivaSelezione(int x, int y, TipoElemento tipo) {
    ElementoAttivo* aux = creaElementoAttivo(x, y);
    if (tipo == ELEM_PEZZO) {
        aux->selezione_pezzo = 1;
    } else {
        aux->selezione_base = 1;
    }
    //-------------
//    if (tipo == ELEM_PEZZO) {
//        matrice_posizioni[x][y].selezione_pezzo = 1;
//    } else {
//        matrice_posizioni[x][y].selezione_base = 1;
//    }
}

bool Griglia::getOccupato(int x, int y) {
    if(matrice_elementi[x][y] != NULL){
        return matrice_elementi[x][y]->getOccupato();
    }else{
        return false;
    }
    //return matrice_posizioni[x][y].getOccupato();
}

TipoElemento Griglia::getTipo(int x, int y) {
    if(matrice_elementi[x][y] != NULL){
        return matrice_elementi[x][y]->tipo;
    }else{
        return NESSUNO;
    }
    //return matrice_posizioni[x][y].tipo;
}

void Griglia::eliminaElemento(int x, int y) {
    if(matrice_elementi[x][y]!=NULL){
        matrice_elementi[x][y]->liberaPosizione();
    }
  //  matrice_posizioni[x][y].liberaPosizione();
}

void Griglia::creaElemento(int x, int y, TipoElemento tipo) {
    ElementoAttivo* aux = creaElementoAttivo(x, y);
    switch (tipo) {
        case ELEM_PEZZO:
            aux->elem = new Pezzo(x, y);
            break;
        case ELEM_BASE:
            aux->elem = new Base(x, y);
            break;
        default:
            break;
    }
    aux->tipo = tipo;
    //questa va tolta
//    switch (tipo) {
//        case ELEM_PEZZO:
//            matrice_posizioni[x][y].occupaPosizione(new Pezzo(x, y), ELEM_PEZZO);
//            break;
//        case ELEM_BASE:
//            matrice_posizioni[x][y].occupaPosizione(new Base(x, y), ELEM_BASE);
//            break;
//    }
}

ElementoAttivo* Griglia::creaElementoAttivo(int x, int y) {
    if (matrice_elementi[x][y] == NULL) {
        ElementoAttivo* tmp = testa_elementi;
        testa_elementi = new ElementoAttivo(x, y, tmp);
        if (tmp != NULL)
            tmp->prev = testa_elementi;
        matrice_elementi[x][y] = testa_elementi;
    }
    return matrice_elementi[x][y];
}

void Griglia::eliminaElementoAttivo(ElementoAttivo* tokill) {
    if(tokill->prev == NULL){
        testa_elementi = tokill->next;
        if(testa_elementi != NULL){
            testa_elementi->prev = NULL;
        }
    }else{
        tokill->prev->next = tokill->next;
        if(tokill->next !=NULL){
            tokill->next->prev = tokill->prev;
        }
    }
    matrice_elementi[tokill->x][tokill->y] =NULL;
    delete tokill;
}

void Griglia::stampa() {
    ElementoAttivo* aux = testa_elementi;
    while (aux != NULL) {
        if (aux->elem != NULL)
            aux->elem->stampa();
        if (aux->selezione_pezzo > 0)
            Pezzo::stampa(true, aux->x, aux->y, aux->selezione_pezzo);
        if (aux->selezione_base > 0)
            Base::stampa(true, aux->x, aux->y, aux->selezione_base);
        aux = aux->next;
    }
}

void Griglia::aggiornaStato() {
    ElementoAttivo* aux = testa_elementi;
    bool elimina;
    while (aux != NULL) {
        elimina = true;
        if (aux->selezione_pezzo > 0) {
            aux->selezione_pezzo -= 0.05;
            elimina = false;
        }
        if (aux->selezione_base > 0) {
            aux->selezione_base -= 0.05;
            elimina = false;
        }
        if (aux->elem != NULL) {
            aux->elem->aggiornaStato();
            elimina = false;
        }
        if (elimina == true) {
            eliminaElementoAttivo(aux);
        }
        aux = aux->next;
    }
}

//void Griglia::stampa(int x, int y) {
//    //    matrice_posizioni[x][y].elem->stampa();
//    if (matrice_elementi[x][y] != NULL && matrice_elementi[x][y]->elem != NULL)
//        matrice_elementi[x][y]->elem->stampa();
//}

//ElementoAttivo* Griglia::getPosizione(int i, int j) {
//    return &matrice_posizioni[i][j];
//}

//Pezzo& Griglia::getPezzo(int i, int j) {
//    return *(Pezzo*) matrice_posizioni[i][j].elem;
//}

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

void Griglia::setStato(int x, int y, StatoPezzo stato) {
    if(matrice_elementi[x][y]->getOccupato() && matrice_elementi[x][y]->tipo == ELEM_PEZZO){
        matrice_elementi[x][y]->elem->setStato(&stato);
    }
//    if (matrice_posizioni[x][y].tipo == ELEM_PEZZO) {
//        Pezzo *aux = (Pezzo*) matrice_posizioni[x][y].elem;
//        if (aux != NULL) {
//            aux->setStato(stato);
//        }
//    }
}

//void Griglia::aggiornaStatoPezzo(int x, int y) {
//    if (matrice_posizioni[x][y].tipo == ELEM_PEZZO) {
//        Pezzo *aux = (Pezzo*) matrice_posizioni[x][y].elem;
//        if (aux != NULL) {
//            aux->aggiornaStato();
//        }
//    }
//}

//GLfloat Griglia::getSelezione(int x, int y, TipoElemento tipo) {
//    if (tipo == ELEM_PEZZO) {
//        return matrice_posizioni[x][y].selezione_pezzo;
//    } else {
//        return matrice_posizioni[x][y].selezione_base;
//    }
//}

//void Griglia::aggiornaSelezione(int x, int y, TipoElemento tipo) {
//    if (tipo == ELEM_PEZZO) {
//        matrice_posizioni[x][y].selezione_pezzo -= 0.05;
//    } else {
//        matrice_posizioni[x][y].selezione_base -= 0.05;
//    }
//}

unsigned Griglia::getDimGrigliaX() const {
    return num_x_colonne;
}

unsigned Griglia::getDimGrigliaY() const {
    return num_y_righe;
}
