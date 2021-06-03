#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
void malloc2dp(int*** P,int nr,int nc)
{
    int i;
    *P=(int**)malloc(nr*sizeof(int*));
    if(*P==NULL)
    {
        printf("non è stata allocata la matrice\n");
        return;
    }
    for(i=0;i<nr;i++)
    {
        (*P)[i]=(int*)malloc(nc*sizeof(int));
        if(((*P)[i])==NULL)
        {
            printf("non è stata allocata la matrice\n");
            return;
        }
    }
}

void getM(FILE* fp,int** M,int nr,int nc)
{
    int i,j;
    for(i=0;i<nr;i++)
        for(j=0;j<nc;j++)
            fscanf(fp,"%d",&(M[i][j]));
}

void freeM(int** M,int nr)
{
    int i;
    for(i=0;i<nr;i++)   free(M[i]);
    free(M);
}

void separa(int **mat, int nr, int nc, int** VB, int** VN)
{
    int i,j,cont,cb=0,cn=0;
    *VB=(int*)malloc(((nr*nc/2)+1)*sizeof(int));
    *VN=(int*)malloc(nr*nc/2*sizeof(int));
    for(i=0;i<nr;i++)
    {
        if((i%2)==0) cont=1;
        else    cont=0;
        for(j=0;j<nc;j++)
        {
            if((cont%2)==1)
            {
                (*VB)[cb]=mat[i][j];
                cb++;
            }
            else
            {
                (*VN)[cn]=mat[i][j];
                cn++;
            }
            cont++;
        }
    }
}

int main()
{
    FILE* fp;
    int nr,nc;
    int i;
    int** M;
    int *VB,*VN;
    fp=fopen("mat.txt","r");
    fscanf(fp,"%d%d",&nr,&nc);
    malloc2dp(&M,nr,nc);
    getM(fp,M,nr,nc);
    separa(M,nr,nc,&VB,&VN);
    printf("elementi disposti sulle caselle bianche:\n");
    for(i=0;((nc*nr)%2==1)?(i<(nc*nr)/2+1):(i<(nc*nr)/2);i++)    printf("%d ",VB[i]);
    printf("\n");
    printf("elementi disposti sulle caselle nere:\n");
    for(i=0;(i<(nc*nr)/2);i++)    printf("%d ",VN[i]);
    free(VB);
    free(VN);
    freeM(M,nr);
    return 0;
}
