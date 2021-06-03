#ifndef GRAPH_H
#define GRAPH_H
#include "ST.h"

typedef struct edge
{
    int v;
    int w;
    int wt;
}Edge;

typedef struct graph* Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHgetIndex(Graph G, char *label, char *labelr);
void  GRAPHstore(Graph G, FILE *fout);
void GRAPHbuildlist(Graph G);
int GRAPHadjPairs(Graph G,int f);


#endif
