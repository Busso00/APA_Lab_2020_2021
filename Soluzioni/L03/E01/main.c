#include <stdio.h>
#include <stdlib.h>
#define MAXR 50

typedef enum
{
    _false,_true
}boolean;

void leggiMatrice(int M[MAXR][MAXR],int m,int* nr,int* nc)
{
    FILE *fp;
    int R,C;
    R=*nr,C=*nc;
    fp=fopen("mappa.txt","r");
    int i,j;
    fscanf(fp,"%d %d",&R,&C);
    for(i=0;i<R;i++)
    {
        for(j=0;j<C;j++)
        {
            fscanf(fp,"%d",&M[i][j]);
        }
    }
    fclose(fp);
    *nr=R,*nc=C;
}

boolean  riconosciRegione(int M[MAXR][MAXR],int nr,int nc,int r,int c,int* b,int* h)
{
    int i,j;
    *b=0,*h=0;
    if(M[r][c]==1)
    {
        if(((M[r-1][c]==0)||(r==0))&&((M[r][c-1]==0)||(c==0)))
        {
            for(i=r;(M[i][c]!=0)&&(i<nr);i++)
            {
                (*h)++;
            }
            for(j=c;M[r][j]&&(j<nc);j++)
            {
                (*b)++;
            }
            return _true;
        }
    }
    printf("non ci sono estremi superiori sinistri\n");
    return _false;
}

int main()
{
    int nr=0,nc=0,M[MAXR][MAXR],r,c,b,h;
    leggiMatrice(M,MAXR,&nr,&nc);
    printf("scrivere riga e collonna da verificare\n");
    scanf("%d %d",&r,&c);
    while((r>=0)&&(c>=0))
    {
        if(riconosciRegione(M,nr,nc,r,c,&b,&h))
        {
            printf("rettangolo con estremo in r:%d c:%d di base:%d e altezza:%d\n",r,c,b,h);
        }
        printf("scrivere riga e collonna da verificare\n");
        scanf("%d %d",&r,&c);
    }
    return 0;
}
