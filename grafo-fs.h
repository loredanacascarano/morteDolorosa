#ifndef __grafofs_h
#define __grafofs_h

#include <stdio.h>
#include <stdlib.h>

#include "listaarchi.h"


#define TRUE  1
#define FALSE 0
#define boolean int


typedef struct _grafo grafo;

struct _grafo
{
  int n;
  int m;
  listaarchi *FS;
};


/* Crea un grafo *pG di n nodi, senza archi */
void creagrafo (int n, grafo *pG);

/* Distrugge il grafo *pG */
void distruggegrafo (grafo *pG);

/* Aggiunge l'arco (o,d) dal grafo *pG (non fa nulla se gia' esiste) */
void insarco (int o, int d, grafo *pG, double distanza);

/* Cancella l'arco (o,d) dal grafo *pG (non fa nulla se non esiste) */
void cancarco (int o, int d, grafo *pG);

/* Determina se l'arco (o,d) appartiene al grafo *pG */
boolean esistearco (int o, int d, grafo *pG);

/* Stampa a video il grafo *pG */
void stampagrafo (grafo *pG);

/* Restituisce la posizione del primo arco della forward star del nodo o del grafo *pG */
posarco primoarcoFS (grafo *pG, nodo o);

/* Restituisce la posizione dell'arco successivo a pa nella forward star del nodo o del grafo *pG */
posarco succarcoFS (grafo *pG, nodo o, posarco pa);

/* Determina se la posizione pa e' fuori della forward star del nodo o del grafo *pG */
boolean finearchiFS (grafo *pG, nodo o, posarco pa);

/* Restituisce la dinazione dell'arco in posizione pa nella forward star del nodo o del grafo *pG */
nodo leggedestarco (grafo *pG, nodo o, posarco pa);

#endif
