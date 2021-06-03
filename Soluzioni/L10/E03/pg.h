#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED
#include "equipArray.h"

typedef struct nodo* linkPg;

typedef struct c{
    char codice[7];
    char nome[maxl];
    char classe[maxl];
    Eq equip;
    stat_t statb,stateq;
}caratteristiche;

//legge personaggio da file
int readstrPg(FILE* fp,caratteristiche* pt);
//chiama funzione che dealloca vettore equip
void pg_clean(caratteristiche* pgc);

//stampa il personaggio
void pPgL1(caratteristiche* x,tabInvP tabInv);

//ritorna 1 se il codice del personaggio e quello cercato
int codisEq(caratteristiche* P,char* key);
//chiama modeqL0 (equipArray.h)
int modeqL1(caratteristiche* x,tabInvP tabInv);


#endif // PG_H_INCLUDED
