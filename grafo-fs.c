#include "grafo-fs.h"

/* Crea un grafo *pG di n nodi, senza archi */
void creagrafo (int n, grafo *pG)
{
  nodo o;


  pG->n = n;
  pG->m = 0;
  pG->FS = (listaarchi *) calloc(pG->n+1,sizeof(listaarchi));
  if (pG->FS == NULL)
  {
    fprintf(stderr,"Errore nell'allocazione del vettore delle forward star!\n");
    exit(EXIT_FAILURE);
  }

  for (o = 1; o <= pG->n; o++)
    pG->FS[o] = crealistaarchi();

}


/* Distrugge il grafo *pG */
void distruggegrafo (grafo *pG)
{
  nodo o;


  for (o = 1; o <= pG->n; o++)
    distruggelistaarchi(&pG->FS[o]);
  free(pG->FS);

  pG->n = 0;
  pG->m = 0;
}


/* Aggiunge l'arco (o,d) dal grafo *pG (non fa nulla se gia' esiste) */
void insarco (nodo o, nodo d, grafo *pG, double lunghezza)
{
  posarco pa, q;
  nodo orig, dest;

  for (pa = primolistaarchi(pG->FS[o]); !finelistaarchi(pG->FS[o],pa); pa = succlistaarchi(pG->FS[o],pa))
  {
    leggearco(pG->FS[o],pa,&orig,&dest);
    if ( (o == orig) && (d == dest) ) break;
  }

  if (finelistaarchi(pG->FS[o],pa))
  {
    q = succlistaarchi(pG->FS[o],ultimolistaarchi(pG->FS[o]));
    inslistaarchi(pG->FS[o],q,o,d, lunghezza);
    pG->m++;
  }
}


/* Cancella l'arco (o,d) dal grafo *pG (non fa nulla se non esiste) */
void cancarco (nodo o, nodo d, grafo *pG)
{
  posarco pa;
  nodo orig, dest;

  for (pa = primolistaarchi(pG->FS[o]); !finelistaarchi(pG->FS[o],pa); pa = succlistaarchi(pG->FS[o],pa))
  {
    leggearco(pG->FS[o],pa,&orig,&dest);
    if ( (o == orig) && (d == dest) ) break;
  }

  if (!finelistaarchi(pG->FS[o],pa))
  {
    canclistaarchi(pG->FS[o],&pa);
    pG->m--;
  }
}


/* Determina se l'arco (orig,dest) appartiene al grafo *pG */
boolean esistearco (nodo o, nodo d, grafo *pG)
{
  posarco pa;
  nodo orig, dest;


  for (pa = primolistaarchi(pG->FS[o]); !finelistaarchi(pG->FS[o],pa); pa = succlistaarchi(pG->FS[o],pa))
  {
    leggearco(pG->FS[o],pa,&orig,&dest);
    if ( (o == orig) && (d == dest) ) return TRUE;
  }

  return FALSE;
}


/* Stampa a video il grafo *pG */
void stampagrafo (grafo *pG)
{
  posarco pa;
  nodo o, d, orig;


  for (orig = 1; orig <= pG->n; orig++)
    for (pa = primolistaarchi(pG->FS[orig]); !finelistaarchi(pG->FS[orig],pa); pa = succlistaarchi(pG->FS[orig],pa))
    {
      leggearco(pG->FS[orig],pa,&o,&d);
      printf("(%d,%d) ",o,d);
    }
}


/* Restituisce la posizione del primo arco della forward star del nodo o del grafo *pG */
posarco primoarcoFS (grafo *pG, nodo o)
{
  return primolistaarchi(pG->FS[o]);
}


/* Restituisce la posizione dell'arco successivo a pa nella forward star del nodo o del grafo *pG */
posarco succarcoFS (grafo *pG, nodo o, posarco pa)
{
  return succlistaarchi(pG->FS[o],pa);
}


/* Determina se la posizione pa e' fuori della forward star del nodo o del grafo *pG */
boolean finearchiFS (grafo *pG, nodo o, posarco pa)
{
  return finelistaarchi(pG->FS[o],pa);
}


/* Restituisce la destinazione dell'arco in posizione pa nella forward star del nodo o del grafo *pG */
nodo leggedestarco (grafo *pG, nodo o, posarco pa)
{
  int orig, d;

  leggearco(pG->FS[o],pa,&orig,&d);
  return d;
}




/* Visita in modo ricorsivo in profondita' il grafo G a partire dalla sorgente s marcando i vertici visitati in C con l'indice c */
void DFSricorsiva (grafo *pG, nodo s, int *C, int c)
{
  nodo w;
  posarco pa;

  /* Marca la sorgente s */
  C[s] = c;

  /* Scorre i vertici adiacenti alla sorgente */
  for (pa = primoarcoFS(pG,s); !finearchiFS(pG,s,pa); pa = succarcoFS(pG,s,pa))
  {
    /* Se l'elemento adiacente non e' ancora stato visitato */
    w = leggedestarco(pG,s,pa);
    if (C[w] == 0) DFSricorsiva(pG,w,C,c);
  }
}