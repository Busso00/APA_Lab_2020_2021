#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dimd 30
#define dimp 200

typedef struct
{
    int cod;
    char orig[dimp];
    int l;
}s;

void filescan(FILE *d,int r,s diz[r])
{
    int i;
    char st[dimp];
    for(i=0;i<r;i++)
    {
        fgets(st,dimp,d);
        sscanf(st,"$%d$ %s",&diz[i].cod,diz[i].orig);
        diz[i].l=strlen(diz[i].orig);
    }
}

void scrivi(int lastpos,int pl,char parola[pl],FILE *u,s diz)
{
    int j;
    for(j=0;j<lastpos;j++)
    {
        fputc(parola[j],u);
    }
    fprintf(u,"$%d$",diz.cod);
    for(j=(lastpos+diz.l);j<pl;j++)
    {
        fputc(parola[j],u);
    }
}

int confronta(int pl,char parola[pl],s diz,FILE *u)
{
    int trovato=0;
    int lastpos=0;
    while((diz.l+lastpos<=pl)&&(!trovato))
    {
        if(strncmp(&parola[lastpos],diz.orig,diz.l)==0)
        {
            trovato=1;
            scrivi(lastpos,pl,parola,u,diz);
        }
        lastpos++;
    }
    return trovato;
}

int main()
{
    FILE *f;
    FILE *d;
    FILE *u;
    char parola[dimp];
    char s_e;
    s diz[dimd];
    int r,pl,i,trovato,n;

    d=fopen("dizionario.txt","r");
    f=fopen("sorgente.txt","r");
    u=fopen("ricodificato.txt","w");

    if((d!=NULL)&&(f!=NULL))
    {
        fscanf(d,"%d\n",&r);

        filescan(d,r,diz);//memorizza il dizionario nel vettore di strutture s

        while((n=fscanf(f,"%s%c",parola,&s_e))>=1)//n serve per capire se il file è finito (n=1), s_e serve ad acquisire " " o "\n"
        {
            pl=strlen(parola);
            for(i=0,trovato=0;(i<r)&&(trovato==0);i++)
            {
                trovato=confronta(pl,parola,diz[i],u); //confronta stringhe di caratteri diz[i] e parola, se trova corrispondenza sostituisce
            }
            if(!trovato)
            {
                fprintf(u,"%s",parola);
            }
            if(n==2)    fprintf(u,"%s",(s_e==' ')?" ":"\n");
        }
    }
    else
    {
        printf("file non trovato");
    }
    fclose(f);
    fclose(d);
    fclose(u);
    return 0;
}
