#include "ST.h"

struct symboltable {n* id; int maxN; int N;};

ST STinit(int maxN){
    ST st;
    st =(ST) malloc(sizeof(struct symboltable));
    if (st == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    st->id =(n*) calloc(maxN, sizeof(n));
    if (st->id == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    st->maxN=maxN;
    st->N = 0;
    return st;
}

ST STrealloc(ST S,int maxN)
{
    //S->id=(n*)realloc(S->id,maxN*sizeof(n));
    S->maxN = maxN;
    return S;
}

void STfree(ST st) {
    if (st==NULL)
        return;
    free(st->id);
    free(st);
}

int STsize(ST S) {
  return S->N;
}

void STinsert(ST st, char *str,char* straddinfo, int i) {
    strcpy(st->id[i].idelab,str);
    strcpy(st->id[i].idrete,straddinfo);
    st->N++;
    return;
}

int STsearch(ST S, char *str) {
    int i;
    for (i = 0; i  < S->N; i++)
        if (S->id[i].idelab!=NULL && strcmp(str, S->id[i].idelab)==0)
            return i;
    return -1;
}

static n addinfovoid()
{
    n temp;
    memcpy(temp.idelab,"-",1);
    memcpy(temp.idrete,"-",1);
    return temp;
}

char* STsearchByIndex(ST st, int i){
    if (i < 0 || i >= st->N)
    {
        return "-";
    }
    return st->id[i].idelab;
}

void STsort(ST S) {
    int i, j, min;
    n temp;
    for(i = 0; i < (S->N); i++) {
        min = i;
        for (j = i+1; j <= (S->N); j++)
            if ((strcmp(S->id[j].idelab,S->id[min].idelab))<0)
                min = j;
        temp=S->id[min];
        S->id[min]=S->id[i];
        S->id[i]=temp;
    }
    return;
}
