#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define maxc 5
#define maxl 255

typedef struct{
    int* scelte;
    int num_scelte;
}livello;

typedef struct{
    char** scelte_canzoni;
}brani_livello;

int princ_molt(livello* val,int n,int pos,int* sol,brani_livello* playlist,int count)
{
    int i;
    if(pos>=n)
    {
        printf("playlist %d:\n",count);
        for(i=0;i<n;i++)    printf("%s\n",playlist[i].scelte_canzoni[sol[i]]);
        printf("\n");
        count++;
       return count;
    }
    for(i=0;(i<val[pos].num_scelte);i++)
    {
        sol[pos]=val[pos].scelte[i];
        count=princ_molt(val,n,pos+1,sol,playlist,count);
    }
    return count;
}

int main()
{
    FILE* fp;
    int A;
    int i,j;
    livello* val;
    char canzone_temp[maxl];
    brani_livello* playlist;
    int* sol;

    fp=fopen("brani.txt","r");
    fscanf(fp,"%d",&A);

    val=(livello*)malloc(A*sizeof(livello));
    playlist=(brani_livello*)malloc(A*sizeof(brani_livello));
    sol=(int*)malloc(A*sizeof(int));

    for(i=0;i<A;i++)
    {
        fscanf(fp,"%d",&(val[i].num_scelte));
        val[i].scelte=(int*)malloc(val[i].num_scelte*(sizeof(int)));
        playlist[i].scelte_canzoni=(char**)malloc(val[i].num_scelte*(sizeof(char*)));
        for(j=0;j<val[i].num_scelte;j++)
        {
            val[i].scelte[j]=j;
            fscanf(fp,"%s",canzone_temp);
            playlist[i].scelte_canzoni[j]=(char*)malloc((strlen(canzone_temp)+1)*sizeof(char));
            strcpy(playlist[i].scelte_canzoni[j],canzone_temp);
        }
    }

    princ_molt(val,A,0,sol,playlist,1);

    for(i=0;i<A;i++)
    {

        for(j=0;j<val[i].num_scelte;j++)
        {
            free(playlist[i].scelte_canzoni[j]);
        }
        free(val[i].scelte);
        free(playlist[i].scelte_canzoni);
    }
    free(val);
    free(playlist);
    free(sol);
}
