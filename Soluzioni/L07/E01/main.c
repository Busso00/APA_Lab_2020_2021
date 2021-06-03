#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int checkvertexc(int* sol,int** E,int k,int ne,int n)
{
    int i;
    int* check;
    check=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++) check[i]=0;
    for(i=0;i<k;i++)
    {
        check[sol[i]]=1;
    }
    for(i=0;i<ne;i++)
    {
        if((!(check[E[i][0]]))&&(!(check[E[i][1]]))) return 0;
    }
    return 1;
}

int disppow(int* V,int n,int* sol,int k,int pos,int start,int** E,int ne,int count)
{
    int i;
    if(pos>=k)
    {
        if(checkvertexc(sol,E,k,ne,n))
        {
            printf("vertexcover n %d:\n",count+1);
            for(i=0;i<pos;i++)  printf("%d ",sol[i]);
            printf("\n");
            return count+1;
        }
        return count;
    }
    for(i=start;i<n;i++)
    {
        sol[pos]=i;
        count=disppow(V,n,sol,k,pos+1,i+1,E,ne,count);
    }
    return count;
}

void powerset(int* V,int n,int** E,int ne)
{
    int i=0,count=0;
    int* Mark;
    int* sol;
    Mark=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)  Mark[i]=0;
    for(i=0 ;i<=n;i++)
    {
        sol=(int*)malloc((i)*sizeof(int));
        count=disppow(V,n,sol,i,0,0,E,ne,count);
        free(sol);
    }
}

int main()
{
    FILE* fp;
    fp=fopen("grafo.txt","r");
    int i;
    int ne;
    int** E;
    int n;
    int* V;

    fscanf(fp,"%d%d",&n,&ne);
    V=(int*)malloc(n*sizeof(int));
    E=(int**)malloc(ne*sizeof(int*));
    for(i=0;i<ne;i++)
    {
        E[i]=(int*)malloc(2*sizeof(int));
        fscanf(fp,"%d %d",&(E[i][0]),&(E[i][1]));
    }
    for(i=0;i<n;i++)
        V[i]=i;

    powerset(V,n,E,ne);

    fclose(fp);
    return 0;
}
