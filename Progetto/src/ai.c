#include "tessera.h"
#include "lista.h"
#include "interattiva.h"
#include "partita.h"
#include "controllo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "ai.h"

/*
Lista_doppia* settare(Lista_doppia* mano) {
    printf("settare\n");
    Lista_doppia risultante;
    inizializza_vuota(&risultante);
    Lista_doppia salvata;
    inizializza_vuota(&salvata);
    return combinazioni(mano, &risultante, &salvata);
}
Lista_doppia* combinazioni(Lista_doppia* mano, Lista_doppia* risultante, Lista_doppia* salvata) {
    printf("combinazioni\n");
    if(!game_continue(risultante, mano)) {
        if(valore_lista(salvata) < valore_lista(risultante)) {
            salvata = risultante;
        }
        stampa(salvata);
        return salvata;
    }
    Nodo* corrente = mano->testa;
    while(corrente) {
        if (corrente->valore->dx == risultante->testa->valore->sx) {
            Lista_doppia nuovoRisultante = copyList(risultante);
            push_front_valore(corrente, &nuovoRisultante);
            Lista_doppia nuovaMano = copyList(mano);
            pop_tessera(&nuovaMano, corrente);
            combinazioni(&nuovaMano, &nuovoRisultante, salvata);
        }
        if(corrente->valore->dx == risultante->coda->valore->dx) {
            Lista_doppia nuovoRisultante = copyList(risultante);
            swap(corrente->valore);
            push_back_valore(corrente, &nuovoRisultante);
            swap(corrente->valore);
            Lista_doppia nuovaMano = copyList(mano);
            pop_tessera(&nuovaMano, corrente);
            combinazioni(&nuovaMano, &nuovoRisultante, salvata);
        }
        if(corrente->valore->sx == risultante->testa->valore->sx) {
            Lista_doppia nuovoRisultante = copyList(risultante);
            swap(corrente->valore);
            push_front_valore(corrente, &nuovoRisultante);
            swap(corrente->valore);
            Lista_doppia nuovaMano = copyList(mano);
            pop_tessera(&nuovaMano, corrente);
            combinazioni(&nuovaMano, &nuovoRisultante, salvata);
        }
        if(corrente->valore->sx == risultante->testa->valore->dx) {
            Lista_doppia nuovoRisultante = copyList(risultante);
            push_back_valore(corrente, &nuovoRisultante);
            Lista_doppia nuovaMano = copyList(mano);
            pop_tessera(&nuovaMano, corrente);
            combinazioni(&nuovaMano, &nuovoRisultante, salvata);
        }
        corrente = corrente->prossimo;
    }
}
*/

Lista_doppia* settings(Lista_doppia* mano) {
    Lista_doppia risultante;
    inizializza_vuota(&risultante);

    Nodo* corrente = mano->testa->prossimo;
    Nodo* massimo = mano->testa;
    while(corrente) {
        if(corrente->valore->sx + corrente->valore->dx > massimo->valore->sx + massimo->valore->dx) {
            massimo = corrente;
        }
        corrente = corrente->prossimo;
    }
    inizializza_valore(massimo, &risultante);
    pop_tessera(mano, massimo);
    return risolvi(mano, &risultante);
}
Lista_doppia* risolvi(Lista_doppia* mano, Lista_doppia* risultante) {
    stampa_lista_numerata(risultante);
    if(!game_continue(risultante, mano)) {
        score_ai(risultante);
        return risultante;
    }
    Nodo* corrente = mano->testa;
    Nodo* massimo = NULL;
    while(corrente) {
        if(!massimo) {
            if(corrente->valore->sx == risultante->testa->valore->sx || corrente->valore->sx == risultante->coda->valore->dx || corrente->valore->dx == risultante->testa->valore->sx || corrente->valore->dx == risultante->coda->valore->dx) {
                massimo = corrente;
            }
        } else {
            if(val_tessera(corrente->valore) > val_tessera(massimo->valore) && (corrente->valore->sx == risultante->testa->valore->sx || corrente->valore->sx == risultante->coda->valore->dx || corrente->valore->dx == risultante->testa->valore->sx || corrente->valore->dx == risultante->coda->valore->dx)) {
                massimo = corrente;
            }
        }
        corrente = corrente->prossimo;
    }
    if (massimo->valore->dx == risultante->testa->valore->sx) {
        push_front_valore(massimo, risultante);
        pop_tessera(mano, massimo);
    } else if(massimo->valore->dx == risultante->coda->valore->dx) {
        swap(massimo->valore);
        push_back_valore(massimo, risultante);
        pop_tessera(mano, massimo);
    } else if (massimo->valore->sx == risultante->testa->valore->sx) {
        swap(massimo->valore);
        push_front_valore(massimo, risultante);
        pop_tessera(mano, massimo);
    } else {
        push_back_valore(massimo, risultante);
        pop_tessera(mano, massimo);
    }
    return risolvi(mano, risultante);
}

