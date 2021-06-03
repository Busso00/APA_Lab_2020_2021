#ifndef ST_H
#define ST_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#define MAXC 30

typedef struct
{
    char idelab[MAXC];
    char idrete[MAXC];
}n;

typedef struct symboltable *ST;

ST    STinit(int maxN);
ST STrealloc(ST S,int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *str,char* straddinfo, int i);
int   STsearch(ST st, char *str);
char* STsearchByIndex(ST st, int i);
void STsort(ST S);

#endif

