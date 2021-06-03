#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
int GRAPHcheckDAG(Graph G,int* mark,Edge* E,int dim);
int GRAPHnedges(Graph G);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void printEdge(Edge* E,Graph G,int*** sol,int i,int f);
void maxwtEdges(Graph G,Edge* E,int** sol,int* maxwtsol,int nsol,int nel);
Graph GRAPHtoDAG(Graph G,Edge* E,int* mark,int dim);
void DAGlp(Graph D);
#endif
