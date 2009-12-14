/* 
 * File:   Griglia.cpp
 * Author: tonegas
 * 
 * Created on 30 ottobre 2009, 15.53
 */

#include "../include/Domino.h"

Griglia::Griglia(unsigned num_x_colonne_aux, unsigned num_y_righe_aux) {
    in_partita = false;
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
}

Griglia::Griglia(const Griglia& orig) {
    cout << "costruttore di copia\n" << flush;
    testa_elementi = NULL;
    in_partita = orig.in_partita;
    //griglia = orig.griglia;
    num_y_righe = orig.num_y_righe;
    num_x_colonne = orig.num_x_colonne;
    //cout << "griglia\"" << griglia.x << ' ' << griglia.y << ' ' << griglia.zoom << '\"' << '\n' << flush;
    cout << "numYX\"" << num_y_righe << ' ' << num_x_colonne << "\"\n" << flush;
    matrice_elementi = new ElementoAttivo* *[num_x_colonne];
    for (unsigned i = 0; i < num_x_colonne; i++) {
        matrice_elementi[i] = new ElementoAttivo* [num_y_righe];
    }
    for (unsigned i = 0; i < num_x_colonne; i++) {
        for (unsigned j = 0; j < num_y_righe; j++) {
            //cout<<i<<' '<<j<<',';
            matrice_elementi[i][j] = NULL;
        }
    }
    cout << "copia lista\n" << flush;
    ElementoAttivo *orig_aux = orig.testa_elementi;
    ElementoAttivo* prev = NULL;
    ElementoAttivo* tmp;
    testa_elementi = NULL;
    unsigned numero = 0;
    if (orig_aux != NULL) {
        cout << "testa non è vuota\n" << flush;
        testa_elementi = new ElementoAttivo(*orig_aux);
        cout << "copiata la testa\n" << flush;
        prev = testa_elementi;
        matrice_elementi[testa_elementi->x][testa_elementi->y] = testa_elementi;
        orig_aux = orig_aux->next;
        while (orig_aux != NULL) {
            tmp = new ElementoAttivo(*orig_aux);
            prev->next = tmp;
            tmp->prev = prev;
            tmp->next = NULL;
            matrice_elementi[tmp->x][tmp->y] = tmp;
            cout << "copio elemento:" << ++numero << " x:" << tmp->x << " y:" << tmp->y << "\n" << flush;
            prev = tmp;
            orig_aux = orig_aux->next;
        }
        cout << "copiata tutta la lista\n" << flush;
    }
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
}

bool Griglia::attivaSelezione(unsigned x, unsigned y, TipoElemento tipo) {
    if (x < num_x_colonne && y < num_y_righe) {
        ElementoAttivo* aux = creaElementoAttivo(x, y);
        if (tipo == ELEM_PEZZO) {
            aux->selezione_pezzo = 1;
        } else {
            aux->selezione_base = 1;
        }
        return true;
    }
    return false;
}

bool Griglia::spostaElementoAttivo(unsigned x_sorg, unsigned y_sorg, unsigned x_dest, unsigned y_dest) {
    if (x_dest < num_x_colonne && y_dest < num_y_righe) {
        if (x_sorg < num_x_colonne && y_sorg < num_y_righe) {
            if (matrice_elementi[x_dest][y_dest] == NULL) {
                matrice_elementi[x_sorg][y_sorg]->x = x_dest;
                matrice_elementi[x_sorg][y_sorg]->y = y_dest;
                matrice_elementi[x_dest][y_dest] = matrice_elementi[x_sorg][y_sorg];
                matrice_elementi[x_sorg][y_sorg] = NULL;
                if (matrice_elementi[x_dest][y_dest]->elem != NULL) {
                    matrice_elementi[x_dest][y_dest]->elem->spostaElemento(x_dest, y_dest);
                }
                return true;
            }
        }
    } else {
        eliminaElementoAttivo(matrice_elementi[x_sorg][y_sorg]);
    }
    return false;
}

bool Griglia::getOccupato(unsigned x, unsigned y) {
    if (x < num_x_colonne && y < num_y_righe) {
        if (matrice_elementi[x][y] != NULL) {
            return matrice_elementi[x][y]->getOccupato();
        }
    }
    return false;
}

TipoElemento Griglia::getTipo(unsigned x, unsigned y) {
    if (x < num_x_colonne && y < num_y_righe) {
        if (matrice_elementi[x][y] != NULL) {
            return matrice_elementi[x][y]->tipo;
        }
    }
    return NESSUNO;

}

bool Griglia::eliminaElemento(unsigned x, unsigned y) {
    if (x < num_x_colonne && y < num_y_righe) {
        if (matrice_elementi[x][y] != NULL) {
            matrice_elementi[x][y]->liberaPosizione();
        }
        return true;
    }
    return false;
}

bool Griglia::creaElemento(unsigned x, unsigned y, TipoElemento tipo) {
    if (x < num_x_colonne && y < num_y_righe) {
        ElementoAttivo* aux = creaElementoAttivo(x, y);
        switch (tipo) {
            case ELEM_PEZZO:
                aux->elem = new Pezzo(x, y);
                break;
            case ELEM_BASE:
                aux->elem = new Base(x, y);
                break;
            default:
                return false;
                break;
        }
        aux->tipo = tipo;
        return true;
    }
    return false;
}

ElementoAttivo * Griglia::creaElementoAttivo(unsigned x, unsigned y) {
    if (matrice_elementi[x][y] == NULL) {
        ElementoAttivo* tmp = testa_elementi;
        testa_elementi = new ElementoAttivo(x, y, tmp);
        if (tmp != NULL)
            tmp->prev = testa_elementi;
        matrice_elementi[x][y] = testa_elementi;
    }
    return matrice_elementi[x][y];
}

void Griglia::eliminaElementoAttivo(ElementoAttivo * tokill) {
    if (tokill->prev == NULL) {
        testa_elementi = tokill->next;
        if (testa_elementi != NULL) {
            testa_elementi->prev = NULL;
        }
    } else {
        tokill->prev->next = tokill->next;
        if (tokill->next != NULL) {
            tokill->next->prev = tokill->prev;
        }
    }
    matrice_elementi[tokill->x][tokill->y] = NULL;
    delete tokill;
}

void Griglia::stampa() {
    ElementoAttivo* aux = testa_elementi;
    while (aux != NULL) {
        if (aux->elem != NULL)
            aux->elem->stampa();
        if (aux->selezione_pezzo > 0)
            Pezzo::stampaSelezione(aux->x, aux->y, aux->selezione_pezzo);
        if (aux->selezione_base > 0)
            Base::stampaSelezione(aux->x, aux->y, aux->selezione_base);
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
            if (in_partita) {
                aux->elem->aggiornaStato(*this);
            }
            elimina = false;
        }
        if (elimina == true) {
            eliminaElementoAttivo(aux);
        }
        aux = aux->next;
    }
}

void Griglia::aggiornaStatoEStampa() {
    ElementoAttivo* aux = testa_elementi;
    bool elimina;
    while (aux != NULL) {
        elimina = true;
        if (aux->selezione_pezzo > 0) {
            Pezzo::stampaSelezione(aux->x, aux->y, aux->selezione_pezzo);
            aux->selezione_pezzo -= 0.05;
            elimina = false;
        }
        if (aux->selezione_base > 0) {
            Base::stampaSelezione(aux->x, aux->y, aux->selezione_base);
            aux->selezione_base -= 0.05;
            elimina = false;
        }
        if (aux->elem != NULL) {
            aux->elem->stampa();
            if (in_partita) {
                aux->elem->aggiornaStato(*this);
            }
            elimina = false;
        }
        if (elimina == true) {
            eliminaElementoAttivo(aux);
        }
        aux = aux->next;
    }

}

ElementoAttivo* Griglia::getTestaElementi() const{
    return testa_elementi;
}

void Griglia::setInPartita(bool aux_in_partita) {
    in_partita = aux_in_partita;
}

bool Griglia::getInPartita(){
    return in_partita;
}


bool Griglia::setStato(unsigned x, unsigned y, StatoPezzo stato) {
    if (x < num_x_colonne && y < num_y_righe) {
        if (matrice_elementi[x][y]->getOccupato() && matrice_elementi[x][y]->tipo == ELEM_PEZZO) {
            matrice_elementi[x][y]->elem->setStato(&stato);
        }
        return true;
    }
    return false;
}

unsigned Griglia::getDimGrigliaX() const {
    return num_x_colonne;
}

unsigned Griglia::getDimGrigliaY() const {
    return num_y_righe;
}
