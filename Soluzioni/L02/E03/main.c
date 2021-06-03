#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxl 200
#define maxs 20
#define maxls 5
#define maxlp 25
#define maxocc 10

typedef struct
{
    char p[maxlp];
    int l;
}s;

typedef struct
{
    char par[maxlp];
    int n;
}st;

int confronta(int pl,char parola[pl],s diz)
{

    int trovato=0;
    int lastpos=0;

    char temp1[pl],temp2[diz.l];
    strcpy(temp1,parola), strcpy(temp2,diz.p);
    strlwr(temp1), strlwr(temp2);

    while((diz.l+lastpos<=pl)&&(!trovato))
    {
        if(strncmp(&temp1[lastpos],temp2,diz.l)==0)
        {
            trovato=1;
        }
        lastpos++;
    }
    return trovato;
}

int main()
{
    FILE *f;
    FILE *d;

    char p[maxlp],str[maxl];
    int occ[maxs];
    st pos[maxs][maxocc];
    int cont=0;
    s diz[maxs];
    int nr=0;
    int i,j,k,pl,strl;
    f=fopen("sequenze.txt","r");
    d=fopen("testo.txt","r");

    fscanf(f,"%d\n",&nr);
    for(i=0;i<nr;i++)
    {
        fscanf(f,"%s",diz[i].p);
        occ[i]=0;
        diz[i].l=strlen(diz[i].p);
    }

    while(fgets(str,maxl,d)!=NULL)
    {
        strl=strlen(str);
        for(k=0;k<strl;k++)
        {

            j=0;
            if(isalnum(str[k])) cont++;
            while(isalnum(str[k]))
            {
                p[j]=str[k];
                j++,k++;
            }

            pl=strlen(p);

            for(i=0;i<nr;i++)
            {
                if((confronta(pl,p,diz[i])==1)&&(occ[i]<=10))
                {
                    pos[i][occ[i]].n=cont;
                    strcpy(pos[i][occ[i]].par,p);
                    occ[i]++;
                }
            }
            while(j>=0)
            {
                p[j]='\0';
                j--;
            }
        }
    }

    for(i=0;i<nr;i++)
    {
        printf("la parola %s è contenuta in: \n",diz[i].p);
        for(j=0;j<occ[i];j++)
        {
            printf("%s in posizione %d nel testo\n",pos[i][j].par,pos[i][j].n);
        }
    }
    return 0;
}
