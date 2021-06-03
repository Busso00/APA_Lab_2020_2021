#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Graph.h"

int combR(Graph G,int* mark,Edge* E,int*** sol,int start,int pos,int k,int f){
    int i;
    if(pos>=k){
        if(GRAPHcheckDAG(G,mark,E,k)){
            if(f==0)
                *sol=calloc(++f,sizeof(int*));
            else
                *sol=realloc(*sol,(++f)*sizeof(int*));
            (*sol)[f-1]=calloc(GRAPHnedges(G),sizeof(int));
            for(i=0;i<pos;i++)
                (*sol)[f-1][i]=mark[i];
            printf("set %d:\n",f);
            for(i=0;i<pos;i++)
                printEdge(E,G,sol,i,f);
            printf("\n");
        }
        return f;
    }
    for(i=start;i<GRAPHnedges(G);i++){
       mark[pos]=i;
       f=combR(G,mark,E,sol,i+1,pos+1,k,f);
    }
    return f;
}

Graph maxEdgeminwtDAG(Graph G,int** sol,int* maxwtsol){
    int c=0,i,f=0;
    Graph DAG;
    Edge* E=malloc(GRAPHnedges(G)*sizeof(Edge));
    int* mark;
    int** temp;
    mark=calloc(GRAPHnedges(G),sizeof(int));
    GRAPHedges(G,E);
    if(GRAPHcheckDAG(G,mark,E,0)){
        printf("il grafo e gia un DAG\n");
        return G;
    }
    else{
        mark=malloc(sizeof(int));
        for(c=1;(c<GRAPHnedges(G))&&(f==0);c++){
            mark=realloc(mark,c*sizeof(int));
            for(i=0;i<c;i++)
                mark[i]=-1;
            f=combR(G,mark,E,&sol,0,0,c,f);
        }
        maxwtsol=malloc(c*sizeof(int));
        maxwtEdges(G,E,sol,maxwtsol,f,c-1);
        printf("\ngli archi eliminati sono i seguenti:\n");
        temp=&maxwtsol;
        for(i=0;i<c-1;i++)
            printEdge(E,G,&temp,i,1);
        printf("\n\n");
        DAG=GRAPHtoDAG(G,E,maxwtsol,c-1);
        return DAG;
    }
}

int main()
{
    Graph G;
    Graph DAG;
    FILE* fp;
    int **sol,*maxwtsol;
    fp=fopen("grafo4.txt","r");
    G=GRAPHload(fp);
    DAG=maxEdgeminwtDAG(G,sol,maxwtsol);
    DAGlp(DAG);
    GRAPHfree(G);
    return 0;
}
