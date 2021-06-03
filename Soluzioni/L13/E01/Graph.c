#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "Graph.h"
#define minWT -1000000
#define MAXC 20

typedef struct{
    int V;
    int wt;
}Item;

typedef struct nodo* link;

struct nodo{
    Item I;
    link next;
};

struct graph {int V; int E; int **madj; ST tab;link* ladj;};
static Edge EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int*));
  if (t == NULL)
    return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

static link newnode(link next,Item val)
{
    link New=calloc(1,sizeof(*New));
    if(New==NULL)
        return NULL;
    New->I=val;
    New->next=next;
    return New;
}


static void GRAPHbuildlist(Graph G)
{
    int i,j;
    Item val;
    link k;
    G->ladj=calloc(G->V,sizeof(link));
    for(i=0;i<(G->V);i++)
    {
        k=NULL;
        for(j=0;j<(G->V);j++)
        {
            if((G->madj[i][j]!=0)&&(k==NULL))
            {
                val.V=j;
                val.wt=G->madj[i][j];
                G->ladj[i]=newnode(NULL,val);
                k=G->ladj[i];
            }
            else if(G->madj[i][j]!=0)
            {
                val.V=j;
                val.wt=G->madj[i][j];
                k->next=newnode(NULL,val);
                k=k->next;
            }
        }
    }
    return;
}

int dfsR(Graph G, Edge e, int *time,int *pre, int *post,int isBack){
    link t;
    int v, w = e.w;
    pre[w] = (*time)++;
    for (t = G->ladj[w];(t!=NULL); t = t->next){
        if (pre[t->I.V] == -1)
            isBack=dfsR(G, EDGEcreate(w, t->I.V,t->I.wt), time, pre, post,isBack);
        else {
            v = t->I.V;
            if (post[v] == -1)
                isBack=1;
            }
    }
    post[w] = (*time)++;
    return isBack;
}

int GRAPHdfs(Graph G, int id) {
    int v, time=0, *pre, *post;
    pre=malloc(G->V * sizeof(int));
    post=malloc(G->V * sizeof(int));
    for (v=0;v<G->V;v++) {
        pre[v]=-1; post[v]=-1;
    }
    for (v=0; v < G->V; v++)
        if (pre[v]==-1)
            if(dfsR(G,EDGEcreate(v,v,0),&time,pre,post,0))//se trova un arco back non è un dag
                return 0;
    return 1;
}

Graph GRAPHtoDAG(Graph G,Edge* E,int* mark,int dim){
    Graph TEMP=malloc(sizeof(*TEMP));
    TEMP->E=G->E;
    TEMP->V=G->V;
    TEMP->tab=STinit(STsize(G->tab));
    STcpy(TEMP->tab,G->tab);
    int i,j;
    TEMP->madj=malloc(TEMP->V*sizeof(int*));
    for(i=0;i<TEMP->V;i++)
    {
        TEMP->madj[i]=malloc(TEMP->V*sizeof(int));
        for(j=0;j<TEMP->V;j++){
            TEMP->madj[i][j]=G->madj[i][j];
        }
    }
    for(i=0;i<dim;i++){
        GRAPHremoveE(TEMP,E[mark[i]].v,E[mark[i]].w);
    }
    GRAPHbuildlist(TEMP);
    return TEMP;
}

int GRAPHcheckDAG(Graph G,int* mark,Edge* E,int dim){
    Graph TEMP=GRAPHtoDAG(G,E,mark,dim);
    if(!GRAPHdfs(TEMP,0)){
        GRAPHfree(TEMP);
        return 0;
    }
    GRAPHfree(TEMP);
    return 1;
}

void printEdge(Edge* E,Graph G,int*** sol,int i,int f){
    printf("%s->%s ",STsearchByIndex(G->tab,E[(*sol)[f-1][i]].v),STsearchByIndex(G->tab,E[(*sol)[f-1][i]].w));
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof(*G));
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;

  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

int GRAPHnedges(Graph G){
    return G->E;
}

static void insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2, 0));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] != 0)
    G->E--;
  G->madj[v][w] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=0; w < G->V; w++)
      if (G->madj[v][w] != 0)
        a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void maxwtEdges(Graph G,Edge* E,int** sol,int* maxwtsol,int nsol,int nel){
    int i,j,maxwt=0,wt;
    for(i=0;i<nsol;i++){
        wt=0;
        for(j=0;j<nel;j++){
            wt+=E[sol[i][j]].wt;
        }
        if(wt>maxwt){
            maxwt=wt;
            for(j=0;j<nel;j++)
                maxwtsol[j]=sol[i][j];
        }
    }
}

static void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
    int w;
    pre[v] = 0;
    for (w = 0; w < D->V; w++)
        if (D->madj[w][v] != 0)
            if (pre[w] == -1)
                TSdfsR(D, w, ts, pre, time);
    ts[(*time)++] = v;
}

static void DAGts(Graph D,int* ts) {
    int v, time = 0, *pre;
    pre = malloc(D->V*sizeof(int));
    for (v=0; v < D->V; v++) { pre[v] = -1;ts[v] = -1; }
    for (v=0; v < D->V; v++)
        if (pre[v]== -1) TSdfsR(D, v, ts, pre, &time);
    printf("DAG nodes in topological order \n");
    for (v=0; v < D->V; v++)
        printf("%s ", STsearchByIndex(D->tab,ts[v]));
    printf(" \n\n");
}

static int indegree(Graph G,int i){
    int j,degree=0;
    for(j=0;j<G->V;j++)
        if(G->madj[j][i])
            degree++;
    return degree;
}

static void GRAPHlpD(Graph G, int id,int nv,int* Q){
    int v,w;
    int  *d;
    link t;
    d = malloc(nv*sizeof(int));
    for (v = 0; v < nv; v++)
        d[v] = minWT;
    d[Q[id]] = 0;
    for(v=id;v<nv;v++)//v scorre il vettore dei vertici ordinati con ts
    {
        if (d[Q[v]]!=minWT){
            t=G->ladj[Q[v]];
            while(t!=NULL){
                if ((d[Q[v]] + t->I.wt > d[t->I.V]))
                    d[t->I.V]=d[Q[v]] + t->I.wt;
                t=t->next;
            }
        }
    }
    for(w=1;w<nv;w++){
        if((d[Q[w]]!=minWT)&&(d[Q[w]]!=0)){
            printf("il cammino max da vertice %s al vertice %s",STsearchByIndex(G->tab,Q[id]),STsearchByIndex(G->tab,Q[w]));
            printf(" e: %d\n",d[Q[w]]);
        }
    }
    printf("\n");
    free(d);
}

void DAGlp(Graph D){
    int* ts,i;
    ts = malloc(D->V*sizeof(int));
    DAGts(D,ts);
    for(i=0;i<D->V;i++){
        if(indegree(D,ts[i])==0)//controllo se il primo dell' ordine topologico sono source
            GRAPHlpD(D,i,D->V,ts);
    }
}
