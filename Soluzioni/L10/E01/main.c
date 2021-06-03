#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct
{
    int s;
    int f;
}att;

typedef struct
{
    int T;
    int P;
}sEl;

void printsol(att *val,sEl *sol, int i) {
    if (sol[i].P==-1) {
        printf("%d-%d ",val[i].s,val[i].f);
    return;
    }
    printsol(val, sol, sol[i].P);
    printf("%d-%d ", val[i].s,val[i].f);
    return;
}

void attSel(int N,att *v)
{
    int i,j,last=0,ris=0;
    sEl *sol;
    sol=malloc(N*sizeof(sEl));

    sol[0].T=v[0].f-v[0].s;
    sol[0].P=-1;

    for(i=1;i<N;i++)
    {
        sol[i].T=0;
        sol[i].P=-1;
        for(j=0;j<i;j++)
        {
            if ((v[i].s>=v[j].f) && (sol[i].T < sol[j].T+v[i].f-v[i].s)) {
                sol[i].T = sol[j].T+v[i].f-v[i].s;
                sol[i].P=j;
            }
            if(ris<sol[i].T)
            {
                ris=sol[i].T;
                last=i;
            }
        }
    }
    printf("soluzione ottima:\n");
    printsol(v,sol,last);
    printf("\ndi durata totale %d",ris);
}

void mergebyStart(att *A,att *B, int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (A[i].s<= A[j].s)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
    return;
}


mergeSortRbyStart(att* v,att* vord,int i,int f)
{
    int m=(i+f)/2;
    if(f<=i)
        return;
    mergeSortRbyStart(v, vord, i, m);
    mergeSortRbyStart(v, vord, m+1, f);
    mergebyStart(v,vord,i,m,f);
    return;
}

int main()
{
    att *v,*vord;
    FILE* fp;
    char nomefile[50];
    int N,i;
    printf("come si chiama il file delle attivita ?\n");
    scanf("%s",nomefile);
    fp=fopen(nomefile,"r");
    if(fp==NULL)
    {
        printf("file non trovato\n");
        exit(1);
    }
    fscanf(fp,"%d",&N);
    v=malloc(N*sizeof(att));
    vord=malloc(N*sizeof(att));
    for(i=0;i<N;i++)
        fscanf(fp,"%d %d ",&(v[i].s),&(v[i].f));
    mergeSortRbyStart(v,vord,0,N-1);
    attSel(N,vord);
    fclose(fp);
    return 0;
}

