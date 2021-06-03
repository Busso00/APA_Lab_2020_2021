#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define maxr 1000
#define maxl 30

typedef struct
{
   int gg;
   int mm;
   int aaaa;
}d;

typedef struct
{
    int ora;
    int min;
    int sec;
}h;

typedef struct
{
    char codice[maxl];
    char partenza[maxl];
    char destinazione[maxl];
    d data;
    h ora_partenza;
    h ora_arrivo;
    int ritardo;
}corsa;

typedef enum
{
    p_log, o_data, o_codice, o_partenza, o_arrivo, s_partenza, _fine
} comando_e;


comando_e leggiComando(void)
{
    comando_e r;
    char comando[maxl];
    char cmdtable[_fine][13]={"stampa","ordinad","ordinac","ordinap","ordinaa","cercapartenza","fine"};
    printf("digita un comando tra: stampa,ordinad,ordinac,ordinap,ordinaa,cercapartenza,fine\n");
    scanf("%s",comando);
    r=p_log;
    strlwr(comando);
    while((r<_fine)&&strcmp(cmdtable[r],comando)!=0)
        r++;
    return r;
}

int savefile(int nr,FILE *f,corsa C[])
{
    int i,err=0;
    if(f==NULL)
    {
        printf("impossibile aprire il file\n");
        return 0;
    }
    for(i=0;(i<nr)&&(!err);i++)
    {
        err=fscanf(f,"%s %s %s",C[i].codice,C[i].partenza,C[i].destinazione);
        err=err+fscanf(f,"%d/%d/%d",&C[i].data.aaaa,&C[i].data.mm,&C[i].data.gg);
        err=err+fscanf(f,"%d:%d:%d",&C[i].ora_partenza.ora,&C[i].ora_partenza.min,&C[i].ora_partenza.sec);
        err=err+fscanf(f,"%d:%d:%d %d\n",&C[i].ora_arrivo.ora,&C[i].ora_arrivo.min,&C[i].ora_arrivo.sec,&C[i].ritardo);
        if(err!=13)
        {
            printf("errore alla riga %d\n",i);
            return 0;
        }
        err=0;
    }
    return 1;
}

void stampa(corsa C)
{
    printf("%s %s %s",C.codice,C.partenza,C.destinazione);
    printf(" %d/%d/%d ",C.data.aaaa,C.data.mm,C.data.gg);
    printf(" %d:%d:%d ",C.ora_partenza.ora,C.ora_partenza.min,C.ora_partenza.sec);
    printf("%d:%d:%d %d \n",C.ora_arrivo.ora,C.ora_arrivo.min,C.ora_arrivo.sec,C.ritardo);
}

int datamagg(corsa* a,corsa* b)
{
    corsa A=*a,B=*b;
    if(A.data.aaaa>B.data.aaaa) return 1;
    else if((A.data.aaaa==B.data.aaaa)&&(A.data.mm>B.data.mm))  return 1;
    else if(A.data.aaaa<B.data.aaaa) return 0;
    else if((A.data.mm==B.data.mm)&&(A.data.gg>B.data.gg))  return 1;
    else if(A.data.mm<B.data.mm) return 0;
    else if((A.data.gg==B.data.gg)&&(A.ora_partenza.ora>B.ora_partenza.ora))    return 1;
    else if(A.data.gg<B.data.gg) return 0;
    else if((A.ora_partenza.ora==B.ora_partenza.ora)&&(A.ora_partenza.min>B.ora_partenza.min))  return 1;
    else if(A.ora_partenza.ora<B.ora_partenza.ora)  return 0;
    else if((A.ora_partenza.min==B.ora_partenza.min)&&(A.ora_partenza.sec>=B.ora_partenza.sec)) return 1;
    return 0;
}

void swap(corsa** A,corsa** B)
{
    corsa *temp;
    temp=*A;
    *A=*B;
    *B=temp;
}

void ordina(int nr,corsa* C[],comando_e f,corsa* Cdest[])//bubblesort
{

    int i,j,flag=1;
    corsa* Ccopy[nr];
    for(i=0;i<nr;i++)
    {
        Ccopy[i]=C[i];
    }
    for(i=0;(i<(nr-1))&&flag;i++)
    {
        flag=0;
        for(j=0;j<(nr-1-i);j++)
        {
            switch(f)
            {
                case p_log:
                    break;
                case o_data:
                    if(datamagg(C[j],C[j+1]))
                    {
                        swap(&C[j],&C[j+1]);
                        flag=1;
                    }
                    break;
                case o_codice:
                    if(strcmp(strlwr(C[j]->codice),strlwr(C[j+1]->codice))>0)
                    {
                        swap(&C[j],&C[j+1]);
                        flag=1;
                    }
                    break;
                case o_partenza:
                    if(strcmp(strlwr(C[j]->partenza),strlwr(C[j+1]->partenza))>0)
                    {
                        swap(&C[j],&C[j+1]);
                        flag=1;
                    }
                    break;
                case o_arrivo:
                    if(strcmp(strlwr(C[j]->destinazione),strlwr(C[j+1]->destinazione))>0)
                    {
                        swap(&C[j],&C[j+1]);
                        flag=1;
                    }
                    break;
                case s_partenza:
                    break;
                case _fine:
                    break;
            }
        }
    }
    for(i=0;i<nr;i++)
    {
        Cdest[i]=C[i];
    }
    for(i=0;i<nr;i++)
    {
        C[i]=Ccopy[i];
    }
}

void binsearch(int nr,corsa* Cpart[],char key[])
{
    int i=0,f=nr-1,I=-1,F=-1;
    int kl;
    int half;
    half=(i+f)/2;
    kl=strlen(key);
    while(strncmp(key,Cpart[half]->partenza,kl)!=0)
    {
        if(i>=f)    return;
        if(strncmp(key,Cpart[half]->partenza,kl)<0)
            f=half-1;
        else
            i=half+1;

        half=(i+f)/2;
    }
    if((half-1)>=0)
    {
        while(strncmp(Cpart[half-1]->partenza,key,kl)==0)
        {
            half--;
            if((half-1)<0) break;
        }
    }
    I=half;
    if((half+1)<=(nr-1))
    {
        while(strncmp(Cpart[half+1]->partenza,key,kl)==0)
        {
            half++;
            if((half+1)>(nr-1)) break;
        }
    }
    F=half;
    for(;I<=F;I++)  stampa(*(Cpart[I]));
}

void linsearch(int nr,corsa C[],char key[])
{
    int i;
    int kl=strlen(key);
    for(i=0;i<nr;i++)
    {
        if(strncmp(strlwr(key),strlwr(C[i].partenza),kl)==0)
        {
            stampa(C[i]);
        }
    }
}

void selezionaDati(int nr,corsa* C,comando_e codcmd,int flag[],comando_e lastcmd, corsa* Carr[],corsa* Cpart[],corsa* Ccod[],corsa* Cdata[])
{
    int i;
    char key[maxl];
    corsa* Ci[nr];
    comando_e searchin;
    searchin=lastcmd;
    if(codcmd==p_log)
    {
        printf("quale ordine si desidera visualizzare?\n");
        searchin=leggiComando();
    }
    switch (searchin)
    {
        case p_log:
            for(i=0;i<nr;i++)   Ci[i]=&C[i];
            break;
        case o_data:
            for(i=0;i<nr;i++)   Ci[i]=Cdata[i];
            break;
        case o_codice:
            for(i=0;i<nr;i++)   Ci[i]=Ccod[i];
            break;
        case o_partenza:
            for(i=0;i<nr;i++)   Ci[i]=Cpart[i];
            break;
        case o_arrivo:
            for(i=0;i<nr;i++)   Ci[i]=Carr[i];
            break;
        case s_partenza:
            break;
        case _fine:
            break;
    }
    switch (codcmd)
    {
        case p_log:
            if(flag[searchin]==1)
            {
                for(i=0;i<nr;i++)   stampa(*(Ci[i]));
            }
            else
            {
                printf("il vettore non è stato ancora ordinato secondo l' ordinamento scelto\n");
            }
            break;
        case o_data:
            ordina(nr,Ci,o_data,Cdata);
            break;
        case o_codice:
            ordina(nr,Ci,o_codice,Ccod);
            break;
        case o_partenza:
            ordina(nr,Ci,o_partenza,Cpart);
            break;
        case o_arrivo:
            ordina(nr,Ci,o_arrivo,Carr);
            break;
        case s_partenza:
            printf("quale stazione di partenza vuole visualizzare?\n");
            scanf("%s",key);
            if(flag[o_partenza]==1)    binsearch(nr,Cpart,key);
            else    linsearch(nr,C,key);
            break;
        case _fine:
            break;
    }
}

int main()
{
    FILE *f;
    int nr,flag[_fine]={0},i;
    f=fopen("corse.txt","r");
    corsa C[maxr];
    corsa *Cdata[maxr],*Ccod[maxr],*Cpart[maxr],*Carr[maxr];
    fscanf(f,"%d\n",&nr);
    comando_e codcmd=p_log;
    comando_e lastcmd=p_log;

    if (savefile(nr,f,C))
    {
        for(i=0;i<nr;i++)
        {
            Carr[i]=Cpart[i]=Ccod[i]=Cdata[i]=&C[i];
        }
        while(codcmd!=_fine)
        {
            codcmd=leggiComando();
            flag[codcmd]=1;
            selezionaDati(nr,C,codcmd,flag,lastcmd,Carr,Cpart,Ccod,Cdata);
            if((codcmd!=p_log)&&(codcmd!=s_partenza))   lastcmd=codcmd;
        }
    }
    fclose(f);
    return 0;
}
