#ifndef VALUE_H_INCLUDED
#define VALUE_H_INCLUDED
#include "timeitem.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <float.h>
typedef struct BST* BSTP;

typedef struct{
	timep date;
	float Q;
	int n;
}Tquote;

BSTP getquotes(FILE* fp,BSTP);
void BSTfree(BSTP bst);
Tquote BSTsearch(BSTP bst, timep k);
int ITEMcheckNull(Tquote T);
void BSTbalance(BSTP bst);
int BSTunbheight(BSTP titolo,float RH);
void BSTsearchMm(BSTP bst,timep k,timep k1,Tquote* QMm);
void printQuote(Tquote Q);
#endif // VALUE_H_INCLUDED
