#include <stdio.h>
#include <math.h>
#include <string.h>
#include "grafo-fs.h"

#define ROW_LENGTH 256

typedef struct{
    double x;
    double y;
    double z;
}posizione;

typedef struct{
    int progressivo;
    char elementoAtomo[5];
    char molecola[8];
    int molecolaProgressiva;
    posizione posizioneAtomo;
}atomo;

typedef struct{
    int numeroIdentificativoMolecola;
    int numeroAtomi;
    atomo arrayAtomi[100];
}molecola;

#define TRUE  1
#define FALSE 0
#define boolean int

void inizializzaMolecola(molecola *, int i);

void aggiungiAtomoAMolecola(molecola *m ,atomo a);

void letturaNomeFile( char *nomeFile);

FILE *getFILE( char *nomeFile);

int salvataggioMolecole(char *riga, molecola *arrayMolecola, FILE *fp, int *nIdrogeno);

void stampaNumeroAtomiperMolecola(const molecola *arrayMolecola, int numeroMolecole);

boolean isLegameAIdrogeno(molecola *A, molecola *B, double *distanza);

void generavettore(posizione *posizioneIdrogeno, posizione *posizioneAtomo, posizione *vettore);

double getModuloVettore(posizione *vettore);

void inserisciMolecoleInGrafo(molecola *molecola, grafo grafo, int molecole, int *nLegami, int *gradi);

void stampaGradiNodi(int *pInt, int nMolecole);

int main(int argc, char *argv[]){

    //char nomeFile[20];
    char riga[ROW_LENGTH];

    molecola arrayMolecola[100];
    //letturaNomeFile(nomeFile);

    FILE *fp = getFILE("esempio00.txt");
            //getFILE(nomeFile);
    int nIdrogeno=0;
    int numeroMolecole = salvataggioMolecole(riga, arrayMolecola, fp, &nIdrogeno);

    //creazione grafo
    grafo grafoMolecole;
    creagrafo(numeroMolecole, &grafoMolecole);
    int nLegami=0;
    int gradi[numeroMolecole];
    inserisciMolecoleInGrafo(arrayMolecola, grafoMolecole, numeroMolecole, &nLegami, gradi);
    stampagrafo(&grafoMolecole);



    printf("%d legami su %d atomi di idrogeno\n", nLegami, nIdrogeno);
    stampaGradiNodi(gradi, numeroMolecole);
    //stampaNumeroAtomiperMolecola(arrayMolecola, numeroMolecole);

    //stampa # di legami a idrogeno su # atomi di idrogeno

    //calcolare numero di legami a idrogeno per molecola e ordinarle per grado

    //cercare i cluster ( gruppi di molecole con legami a idrogeno)
    //e stamparli in ordine decrescente - intero delle molecole

    //distanza tra due molecole -> numero minimo di legami a idrogeno tra molecole
    // 1-> legate direttamente //2 -> legate indirettamente //inf altrimenti

    //diametro del cluster: distanza max tra due molecole; 0 se è una molecola sola

    //stampa il diametro del primo cluster

    //lunghezza per ogni legame: distanza tra accettore e donore
    // albero lunghezza minima primo cluster
    return 0;
}

void stampaNumeroAtomiperMolecola(const molecola *arrayMolecola, int numeroMolecole) {
    int i;
    for ( i=1; i<=numeroMolecole; i++){
        printf("numero atomo: %d, numero indice Molecola: %d\n", arrayMolecola[i].numeroAtomi, arrayMolecola[i].numeroIdentificativoMolecola);
    }
}

int salvataggioMolecole(char *riga, molecola *arrayMolecola, FILE *fp, int *idrogeno) {
    int pos = 0;
    int n;
    while(fgets(riga,ROW_LENGTH,fp) != NULL){
        atomo temp;
        //printf("while\n");
        char tempP[5];

        n = sscanf(riga,"%s %d %s %s %d %lf %lf %lf",
                   tempP,
                   &temp.progressivo,
                   temp.elementoAtomo,
                   temp.molecola,
                   &temp.molecolaProgressiva,
                   &temp.posizioneAtomo.x,
                   &temp.posizioneAtomo.y ,
                   &temp.posizioneAtomo.z );

        if(strcmp(temp.elementoAtomo, "H")== 0){
            (*idrogeno)++;
        }
        if(temp.molecolaProgressiva > pos ){
            //printf(">pos");
            pos = temp.molecolaProgressiva;
            inizializzaMolecola(&arrayMolecola[pos], pos);
        }
        aggiungiAtomoAMolecola(&arrayMolecola[pos], temp);

        //printf("%d %s %s %d %lf %lf %lf\n", temp.progressivo,temp.elementoAtomo, temp.molecola,temp.molecolaProgressiva, temp.posizioneAtomo.x, temp.posizioneAtomo.y ,temp.posizioneAtomo.z );

    }
    /*
    int i=pos, j=0;
    for (j=0; j<arrayMolecola[i].numeroAtomi; j++) {
        printf("Molecola: %d \n x: %f\t y: %f\t z: %f\n", arrayMolecola[i].numeroIdentificativoMolecola,
               arrayMolecola[i].arrayAtomi[j].posizioneAtomo.x, arrayMolecola[i].arrayAtomi[j].posizioneAtomo.y,
               arrayMolecola[i].arrayAtomi[j].posizioneAtomo.z);
    }
    */
    return pos;
}

FILE *getFILE( char *nomeFile) {
    FILE *fp = fopen(nomeFile, "r");

    if(fp == NULL){
        printf("errore in apertura file\n");
    } else printf("file aperto\n");
    return fp;
}

void letturaNomeFile( char *nomeFile) {
    printf("inserire nome file:\n");
    scanf("%s", nomeFile);
}

double calcolaDistanza(atomo *primoAtomo, atomo *secondoAtomo){
    posizione posizionePrimoAtomo = primoAtomo->posizioneAtomo;
    posizione posizioneSecondoAtomo = secondoAtomo->posizioneAtomo;
    double x_a = posizionePrimoAtomo.x;
    double y_a = posizionePrimoAtomo.y;
    double z_a = posizionePrimoAtomo.z;

    double x_b = posizioneSecondoAtomo.x;
    double y_b = posizioneSecondoAtomo.y;
    double z_b = posizioneSecondoAtomo.z;
    double distanza = sqrt((x_a-x_b)*(x_a-x_b) + (y_a-y_b)*(y_a-y_b) + (z_a-z_b)*(z_a-z_b));
    return distanza ;
}

void generavettore(posizione *posizioneIdrogeno, posizione *posizioneAtomo, posizione *vettore) {
    vettore->x= (*posizioneAtomo).x - (*posizioneIdrogeno).x;
    vettore->y= (*posizioneAtomo).y - (*posizioneIdrogeno).y;
    vettore->z= (*posizioneAtomo).z - (*posizioneIdrogeno).z;
}

double getModuloVettore(posizione *vettore) { return sqrt(
            (*vettore).x * (*vettore).x + (*vettore).y * (*vettore).y + (*vettore).z * (*vettore).z ); }

boolean isAngoloValido(posizione *posizioneIdrogeno, posizione *posizionePrimoAtomo, posizione *posizioneSecondoAtomo) {
    posizione primoVettore;
    posizione secondoVettore;
/*
    printf("posizione idrogeno: %f %f %f\n", posizioneIdrogeno->x, posizioneIdrogeno->y, posizioneIdrogeno->z);

    printf("posizione primo atomo: %f %f %f\n", posizionePrimoAtomo->x, posizionePrimoAtomo->y, posizionePrimoAtomo->z);

    printf("posizione secondo Atomo: %f %f %f\n", posizioneSecondoAtomo->x, posizioneSecondoAtomo->y, posizioneSecondoAtomo->z);
*/
    generavettore(posizioneIdrogeno, posizionePrimoAtomo, &primoVettore);
    generavettore(posizioneIdrogeno, posizioneSecondoAtomo, &secondoVettore);
    double prodottoScalare = primoVettore.x*secondoVettore.x + primoVettore.y*secondoVettore.y +primoVettore.z*secondoVettore.z;
    double moduloPrimoVettore = getModuloVettore(&primoVettore);
    double moduloSecondoVettore = getModuloVettore(&secondoVettore);
    //printf("modulo primo vettore: %f\n", moduloPrimoVettore);
    //printf("modulo secondo vettore: %f\n", moduloSecondoVettore);
    //printf("prodottoScalare: %f\n", prodottoScalare);

    double angolo = acos(prodottoScalare/(moduloPrimoVettore*moduloSecondoVettore))*180/M_PI;

  //  printf("\t \t \tangolo: %f\n", angolo);
    //printf("angoloMinimo:  %f \n", 5 *M_PI/6);
    return angolo > 150;
}

boolean isLegameAIdrogeno(molecola *A, molecola *B, double *distanza){
    //controlla se ogni atomo diverso da H ha una distanza inferiore a 3.5
    int numeroAtomiPrimaMolecola = A->numeroAtomi;
    int numeroAtomiSecondaMolecola = B ->numeroAtomi;
    int nMaxCoppie = numeroAtomiPrimaMolecola * numeroAtomiSecondaMolecola;
    atomo coppie[nMaxCoppie][2];
    atomo idrogeni[numeroAtomiPrimaMolecola+numeroAtomiSecondaMolecola];
    int i;
    int j;
    int k;
    int p=0;
    int p2=0;
    for(i=0; i< numeroAtomiPrimaMolecola; i++){
        atomo primoAtomo = A->arrayAtomi[i];
        //("primo atomo: %s\n",(primoAtomo).elementoAtomo);
        if(strcmp(primoAtomo.elementoAtomo, "H") == 0) {
            idrogeni[p2]=primoAtomo;
            p2++;
            continue;
        }
        for ( j=0; j<numeroAtomiSecondaMolecola; j++){
            atomo secondoAtomo = B->arrayAtomi[j];
            if(strcmp(secondoAtomo.elementoAtomo, "H") == 0){
                idrogeni[p2] = secondoAtomo;
                p2++;
                continue;
            }
            *distanza = calcolaDistanza(&primoAtomo, &secondoAtomo);
            if(*distanza < 3.5) {
                coppie[p][0]= primoAtomo;
                coppie[p][1]= secondoAtomo;
                p++;
            }
        }
    }
    //("Numero coppie individuate %d  numnero atomi ad idrogeno %d\n", p, p2);
    for(i=0;i<p;i++){
        for(k=0; k<p2; k++){
            //printf("ci sono");
            if(isAngoloValido(&idrogeni[k].posizioneAtomo,&coppie[i][0].posizioneAtomo, &coppie[i][1].posizioneAtomo)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

void inizializzaMolecola(molecola* m, int i){
    m->numeroAtomi = 0;
    m->numeroIdentificativoMolecola = i;
}

void aggiungiAtomoAMolecola(molecola *m ,atomo a){

    m->numeroAtomi++;
    m->arrayAtomi[m->numeroAtomi -1 ]= a;
   /* printf("atomo a: %s\n", a.elementoAtomo);
    if(m->numeroAtomi >1){
        printf("atomi m: %s\n\n", m->arrayAtomi[m->numeroAtomi-2].elementoAtomo);
    }
    */
}


void inserisciMolecoleInGrafo(molecola *molecola, grafo grafoMolecola, int numeroMolecole, int *nLegami, int *gradi){
    //controllo coppie molecole
   // printf("sono all'interno di inserisciMolecoleInGrafo\n");
   int k ;
    for (k=0; k<numeroMolecole;k++){
        gradi[k]=0;
    }
    int i;
    int j;
    double distanza;
    for (i =1; i<=numeroMolecole-1; i++){
        for(j=i+1; j<=numeroMolecole; j++){
           // printf("\nMolecola %d, numero identificativo molecola: %d\n", i,  molecola[i].numeroIdentificativoMolecola);
         //   printf("\nMolecola %d, numero identificativo molecola: %d\n", j,  molecola[j].numeroIdentificativoMolecola);
            //printf("\n\ncontrollo molecole i:%d j:%d\n\n",i,j);
            if(isLegameAIdrogeno(&molecola[i], &molecola[j], &distanza)) {
              //  printf("arco individuato");
                (*nLegami)++;
                gradi[(&molecola[i])->numeroIdentificativoMolecola -1] ++;

                gradi[(&molecola[j])->numeroIdentificativoMolecola -1] ++;
                insarco(molecola[i].numeroIdentificativoMolecola, molecola[j].numeroIdentificativoMolecola, &grafoMolecola, distanza );
            };
        }
    }
}


void stampaGradiNodi(int *gradi, int nMolecole){

    int i=0;
    int max=gradi[0];
    for (; i<nMolecole; i++){
        if(max<gradi[i]){
            max=gradi[i];
        }
    }
    int count[max+1];
    for(i=0; i<max+1;i++){
        count[i]=0;
    }
    for (i=0; i<nMolecole; i++){
        count[gradi[i]]++;
    }

   for(i=0; i<=max;i++){
            printf("Grado: %d molecole: %d\n", i, count[i]);
        }

}