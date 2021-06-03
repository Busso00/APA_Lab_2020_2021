#ifndef TITOLI_H_INCLUDED
#define TITOLI_H_INCLUDED
#include "value.h"

typedef struct titoli* tTab;
typedef struct titolo* link;

tTab Tinit();
tTab getT(tTab T,FILE* fp);
link searcht(tTab T,char* cod);
Tquote BSTsearchL2(link T,timep k);
int BSTunbheightL2(link titolo,float RH);
void BSTbalanceL2(link titolo);
void freeT(tTab T);
#endif // TITOLI_H_INCLUDED
