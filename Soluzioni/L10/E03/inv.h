#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NINV 8
#define maxl 50
#include "stat.h"

typedef struct st{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct inv{
    char nome[maxl];
    char tipo[maxl];
    stat_t stat;
}inv_t;

//leggi e scrivi stat
int scanStatObj(char* str,stat_t* stat);
void printStat(stat_t* res,int soglia);

//legge prima nome e tipo di equipaggiamento, poi chiama lettura stat(scanstatObj)
int readstrEq(FILE* fp,inv_t* it);
void pObjL0(inv_t* Obj);//questa è la stampa effettiva dell'oggetto le altre pObjLn servono solo a cercare in lista

//ritorna alle funzioni di ricerca dell'oggetto per nome 1 se l'oggetto ha il nome cercato 0 altrimenti
int KeyisEq(char* nomeoggetto,inv_t* it);

stat_t inv_getStat(inv_t* invp);

#endif // INV_H_INCLUDED
