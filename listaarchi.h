#ifndef __listaarchi_h
#define __listaarchi_h

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define boolean int


typedef struct _arco arco;
typedef arco* listaarchi;
typedef arco* posarco;
typedef int nodo;

#define NO_ARC   NULL
#define NO_NODE     0

struct _arco
{
  nodo    orig, dest;
  posarco succ, pred;
  double lunghezza;
};


listaarchi crealistaarchi ();

void distruggelistaarchi (listaarchi *pL);

void leggearco (listaarchi L, posarco p, nodo *porig, nodo *pdest);

listaarchi scrivearco (listaarchi L, posarco p, nodo orig, nodo dest);

posarco primolistaarchi (listaarchi L);

posarco ultimolistaarchi (listaarchi L);

boolean finelistaarchi (listaarchi L, posarco p);

boolean listaarchivuota (listaarchi L);

posarco preclistaarchi (listaarchi L, posarco p);

posarco succlistaarchi (listaarchi L, posarco p);

listaarchi inslistaarchi (listaarchi L, posarco p, nodo orig, nodo dest, double distanza);

listaarchi canclistaarchi (listaarchi L, posarco *pp);

#endif
