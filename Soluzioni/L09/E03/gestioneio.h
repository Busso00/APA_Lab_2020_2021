#ifndef GESTIONEIO_H_INCLUDED
#define GESTIONEIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxl 50
#define NINV 8

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[maxl];
    char tipo[maxl];
    stat_t stat;
}inv_t;

typedef struct{
    int inUso;
    inv_t vettEq[NINV];
}tabEquip_t;

typedef struct{
    char codice[7];
    char nome[maxl];
    char classe[maxl];
    tabEquip_t equip;
    stat_t stat;
}caratteristiche;

FILE* getfilep(FILE* fp);
int readstr(FILE* fp,void* dest,int flag);

#endif // GESTIONEIO_H_INCLUDED
