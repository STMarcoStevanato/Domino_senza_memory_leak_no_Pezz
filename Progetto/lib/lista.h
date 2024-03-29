#ifndef LISTA_H
#define LISTA_H

#include "tessera.h"

typedef struct Nodo {
    Tessera* valore;
    struct Nodo* prossimo;
    struct Nodo* previo;
} Nodo;

typedef struct Lista_doppia {
    Nodo* testa;
    Nodo* coda;
} Lista_doppia;

void inizializza_random(Lista_doppia* ptr);
void inizializza_valore(Nodo* ptr, Lista_doppia* a);
void push_front_random(Lista_doppia* ptr);
void push_back_random(Lista_doppia* ptr);
void push_front_valore(Nodo* ptr, Lista_doppia* a);
void push_back_valore(Nodo* ptr, Lista_doppia* a);
Nodo* pop_indice(Lista_doppia* ptr, int i);
void crea_lista(int n, Lista_doppia* a);
void crea_lista_vuota(Lista_doppia* a);
void stampa_lista(Lista_doppia* ptr);
void stampa_lista_numerata(Lista_doppia* ptr);
int num_elementi(Lista_doppia* ptr);
Nodo* get_nodo(Lista_doppia* ptr, int i);
void free_lista(Lista_doppia* ptr);

#endif
