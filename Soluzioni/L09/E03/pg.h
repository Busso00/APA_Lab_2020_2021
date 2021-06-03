#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED
#include "inv.h"

typedef struct nodo* linkPg;

typedef struct nodo{
    caratteristiche pg_t;
    linkPg next;
}nodoPg_t;

typedef struct{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
}tabPg_t;

void pgTinit(tabPg_t** tabPg);
linkPg newnodeT(linkPg newpg,caratteristiche val);
int addintail(tabPg_t* tabPg,linkPg t);
int scanpg(tabPg_t* tabPg,FILE* fp,int f);
int aggiungiTabpg(tabPg_t* tabPg);
int scod(linkPg head,linkPg* xp,linkPg* pp);
int searchcod(tabPg_t* tabPg);
int listDelrKey(tabPg_t* tabPg);
int elimpg(tabPg_t* tabPg);
int modeq(tabPg_t* tabPg,tabInv_t* tabInv);
void printPg(tabPg_t* tabPg);
void liberaP(tabPg_t* tabPg);
#endif // PG_H_INCLUDED
