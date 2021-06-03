#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char col;
    int val;
}seg;

typedef struct
{
    seg v;
    seg o;
    int ruota;
    int preso;
    int n;
}tessera;

tessera tesserasetvoid()
{
    tessera t;
    t.v.col='n';
    t.v.val=0;
    t.o.col='n';
    t.o.val=0;
    t.n=-1;
    t.ruota=-1;
    t.preso=0;
    return t;
}

int calcolaval(int N,int M,tessera** sol)
{
    int i,j,val=0,tmpval;
    tessera** tmpsol=malloc(N*sizeof(tessera*));
    for(i=0;i<N;i++)
    {
        tmpsol[i]=malloc(M*sizeof(tessera));
        for(j=0;j<M;j++)
        {
            if(sol[i][j].ruota)
            {
                tmpsol[i][j].v=sol[i][j].o;
                tmpsol[i][j].o=sol[i][j].v;
            }
            else
            {
                tmpsol[i][j].v=sol[i][j].v;
                tmpsol[i][j].o=sol[i][j].o;
            }
        }
    }

    for(i=0;i<N;i++)
    {
        tmpval=0;
        for(j=0;j<M&&((j==0)||(tmpsol[i][j].o.col==tmpsol[i][j-1].o.col));j++)
        {
            tmpval+=tmpsol[i][j].o.val;
        }
        if(j==M)
            val+=tmpval;
    }

    for(j=0;j<M;j++)
    {
        tmpval=0;
        for(i=0;i<N&&((i==0)||(tmpsol[i][j].v.col==tmpsol[i-1][j].v.col));i++)
        {
            tmpval+=tmpsol[i][j].v.val;
        }
        if(i==N)
            val+=tmpval;
    }
    return val;
}

void Solve(tessera* vt,tessera** sol,tessera** bestsol,int K,int N,int M,int pos,int* mval)
{
    int i,j,k,temp;
    if(pos>=N*M)
    {
        if((temp=calcolaval(N,M,sol))>*mval)
        {
            for(i=0;i<N;i++)
                for(j=0;j<M;j++)
                    bestsol[i][j]=sol[i][j];
            *mval=temp;
        }
        return;
    }
    i=pos/M;
    j=pos%M;
    if(sol[i][j].ruota==-1)
    {
        for(k=0;k<K;k++)
        {
            if(!(vt[k].preso))
            {
                vt[k].preso=1;
                sol[i][j]=vt[k];
                sol[i][j].ruota=0;
                Solve(vt,sol,bestsol,K,N,M,pos+1,mval);
                sol[i][j].ruota=1;
                Solve(vt,sol,bestsol,K,N,M,pos+1,mval);
                vt[k].preso=0;
                sol[i][j]=tesserasetvoid();
            }
        }
    }
    else
    {
        Solve(vt,sol,bestsol,K,N,M,pos+1,mval);
    }
    return;
}

int main()
{
    FILE *fpt,*fpb;
    char temp[30],tmp;
    int K,N,M,i,j,*mval;
    tessera* vt;
    tessera** sol;
    tessera** bestsol;
    int index,r;
    fpt=fopen("tiles.txt","r");
    fpb=fopen("board.txt","r");

    fscanf(fpt,"%d\n",&K);
    fscanf(fpb,"%d %d\n",&N,&M);
    mval=malloc(sizeof(int));
    vt=malloc(K*sizeof(tessera));
    sol=malloc(N*sizeof(tessera*));
    bestsol=malloc(N*sizeof(tessera*));

    for(i=0;i<K;i++)
    {
        fgets(temp,30,fpt);
        sscanf(temp,"%s %d %c %d ",&(vt[i].o.col),&(vt[i].o.val),&(vt[i].v.col),&(vt[i].v.val));
        vt[i].ruota=0;
        vt[i].preso=0;
        vt[i].n=i;
    }

    for(i=0;i<N;i++)
    {
        sol[i]=malloc(M*sizeof(tessera));
        bestsol[i]=malloc(M*sizeof(tessera));
        for(j=0;j<M;j++)
        {
            fscanf(fpb,"%d/%d ",&index,&r);
            if(index!=-1)
            {
                sol[i][j]=vt[index];
                vt[index].preso=1;
            }
            else
                sol[i][j]=tesserasetvoid();
            sol[i][j].ruota=r;
        }
    }
    *mval=0;
    Solve(vt,sol,bestsol,K,N,M,0,mval);

    printf("la soluzione migliore è\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
            printf("%d/%d ",bestsol[i][j].n,bestsol[i][j].ruota);
        printf("\n");
    }
    tmp=calcolaval(N,M,bestsol);
    printf("il valore massimo e: %d",tmp);

    return 0;
}
