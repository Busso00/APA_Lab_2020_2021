#include "Graph.h"
#define maxWT INT_MAX

typedef struct{
    int V;
    int wt;
}Item;

typedef struct nodo* link;

struct nodo{
    Item I;
    link next;
};

struct graph {int V; int E; int **madj;link* ladj; ST tab;};

static Graph GRAPHrealloc(Graph G,int S);
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

int** MATRIXint(int r, int c, int val) {
  int i, j;
  int **t =(int**) malloc(r * sizeof(int*));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] =(int*) malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph G =(Graph)malloc(sizeof(struct graph));
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

static Graph GRAPHrealloc(Graph G,int S)
{
    G->V = S;
    G->E = 0;
    G->madj = MATRIXint(S, S, maxWT);
    if (G->madj == NULL)
        return NULL;
    G->tab = STrealloc(G->tab,S);
    if (G->tab == NULL)
        return NULL;
    G->ladj=NULL;
    STsort(G->tab);
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

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == maxWT)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;//grafo non orientato
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt,tmp;
    char label1[MAXC], label2[MAXC],label1r[MAXC],label2r[MAXC],temp[MAXC*5];
    Graph G;
    while(fgets(temp,MAXC*5,fin)!=NULL)
    {
        V++;
    }
    rewind(fin);
    G=GRAPHinit(V);
    for (i=0; i<V; i++) {//V per ora è il numero di archi
        fgets(temp,MAXC*5,fin);
        if(sscanf(temp,"%s%s%s%s%d",label1,label1r,label2,label2r,&tmp)==5)
        {
            GRAPHgetIndex(G,label1,label1r);
            GRAPHgetIndex(G,label2,label2r);
        }
        else
            printf("errore nell'acquisizione dell' arco %d\n",i);
    }
    G=GRAPHrealloc(G,STsize(G->tab));
    rewind(fin);
    while((fgets(temp,MAXC*5,fin)!=NULL)&&(sscanf(temp, "%s%s%s%s%d", label1,label1r,label2,label2r,&wt) == 5)) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    int j;
    Edge *a;
    a =(Edge*) malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;
    printf("archi in ordine alfabetico matrice di adiacenza\n");
    for(i=0;i < G->V; i++)
    {
        fprintf(fout,"%s\n",STsearchByIndex(G->tab,i));
        for(j=0;j < G->V; j++)
        {
            if(G->madj[i][j]<maxWT)
                fprintf(fout," -> %s\n",STsearchByIndex(G->tab,j));
        }
        fprintf(fout,"\n");
    }
    return;

}

int GRAPHgetIndex(Graph G, char *label, char *labelr) {//ritorna l'id del nodo label se non trova inserisce label
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, labelr, id);
    }
    return id;
}

link newnode(link next,Item val)
{
    link New=(link)malloc(sizeof(struct nodo));
    if(New==NULL)
        return NULL;
    New->I=val;
    New->next=next;
    return New;
}

void GRAPHbuildlist(Graph G)
{
    int i,j;
    Item val;
    link k;
    G->ladj=(link*)calloc(G->V,sizeof(link));
    for(i=0;i<(G->V);i++)
    {
        k=NULL;
        for(j=0;j<(G->V);j++)
        {
            if((G->madj[i][j]<maxWT)&&(k==NULL))
            {
                val.V=j;
                val.wt=G->madj[i][j];
                G->ladj[i]=newnode(NULL,val);
                k=G->ladj[i];
            }
            else if(G->madj[i][j]<maxWT)
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

int GRAPHadjPairs(Graph G,int f)
{
    char nomeV1[MAXC],nomeV2[MAXC],nomeV3[MAXC];
    int I1,I2,I3;
    link x1,x2,x3;
    fprintf(stdout,"scrivere il nome dei tre vertici (uno alla volta)\n");
    fgets(nomeV1,MAXC,stdin);
    fgets(nomeV2,MAXC,stdin);
    fgets(nomeV3,MAXC,stdin);
    sscanf(nomeV1,"%s",nomeV1);
    sscanf(nomeV2,"%s",nomeV2);
    sscanf(nomeV3,"%s",nomeV3);
    I1=STsearch(G->tab,nomeV1);
    I2=STsearch(G->tab,nomeV2);
    I3=STsearch(G->tab,nomeV3);
    if(((I1!=-1)&&(I2!=-1))&&(I3!=-1)){
        if(f)
        {
            if(((G->madj[I1][I2])!=maxWT)&&((G->madj[I2][I3])!=maxWT)&&((G->madj[I1][I3])!=maxWT))
                return 1;
        }
        else if(G->ladj!=NULL)
        {
            x1=G->ladj[I1];
            x2=G->ladj[I2];
            x3=G->ladj[I3];
            while((x1!=NULL)&&((x1->I.V)!=I2))
                x1=x1->next;
            while((x2!=NULL)&&((x2->I.V)!=I3))
                x2=x2->next;
            while((x3!=NULL)&&((x3->I.V)!=I1))
                x3=x3->next;
            if((x1!=NULL)&&(x2!=NULL)&&(x3!=NULL))
                return 1;
        }
        else
            printf("devi caricare la lista di adiacenza con comando: lista\n");
    }
    return 0;
}
