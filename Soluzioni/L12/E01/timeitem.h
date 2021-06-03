#ifndef TIMEITEM_H_INCLUDED
#define TIMEITEM_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MAXL 20

typedef struct time* timep;

int islater(timep A,timep B);
int isequal(timep A,timep B);
timep getdate(FILE* fp);
int KEYcmp(timep A,timep B);
timep ITEMsetNullD();
int ITEMcheckNullD(timep date);
void freedate(timep date);
#endif // TIMEITEM_H_INCLUDED
