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
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine
} comando_e;

comando_e leggiComando(void)
{
    comando_e r;
    char comando[maxl];
    char cmdtable[r_fine][maxl]={"date","partenza","capolinea","ritardo","ritardo_tot"};
    printf("digita un comando tra: date,partenza,capolinea,ritardo,ritardo_tot,fine\n");
    scanf("%s",comando);
    r=r_date;
    strlwr(comando);
    while((r<r_fine)&&strcmp(cmdtable[r],comando)!=0)
        r++;
    return r;
}

int savefile(int nr,FILE *f,corsa C[nr])
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

void verificadata(d data0,d data1,corsa C)
{
    if(((C.data.aaaa)>=data0.aaaa)&&((C.data.aaaa)<=data1.aaaa))
    {
        if((data0.aaaa)<(data1.aaaa))
        {
            if((data0.aaaa<C.data.aaaa)&&(data1.aaaa>C.data.aaaa))    stampa (C);
            else
            {
                if(data0.aaaa==C.data.aaaa)
                {
                    if(data0.mm<C.data.mm)
                    {
                        stampa(C);
                    }
                    if(data0.mm==C.data.mm)
                    {
                        if(data0.gg<=C.data.mm)  stampa(C);
                    }
                }
                if(data1.aaaa==C.data.aaaa)
                {
                    if(data1.mm>C.data.mm)
                    {
                        stampa(C);
                    }
                    if(data1.mm==C.data.mm)
                    {
                        if(data1.gg>=C.data.mm)  stampa(C);
                    }
                }
            }
        }
        else if(((C.data.mm)>=data0.mm)&&((C.data.mm)<=data1.mm))
        {
            if((data0.mm)<(data1.mm))
            {
                if((data0.mm<C.data.mm)&&(data1.mm>C.data.mm))    stampa(C);
                else
                {
                    if((data0.mm==C.data.mm)&&(data0.gg<=C.data.gg))    stampa(C);
                    if((data1.mm==C.data.mm)&&(data1.gg>=C.data.gg))    stampa(C);
                }
            }
            else if(((C.data.gg)>=data0.gg)&&((C.data.gg)<=data1.gg))
            {
                stampa(C);
            }
        }
    }
}

void date(int nr,corsa C[nr],d data0,d data1)
{
    int i;
    printf("le corse partite nell'intervallo di date sono:\n");
    for(i=0;i<nr;i++)
    {
        verificadata(data0,data1,C[i]);
    }
}

void partenze(int nr,corsa C[nr],char part[maxl])
{
    int i;
    printf("le corse partite dalla fermata sono:\n");
    for(i=0;i<nr;i++)
    {
        if(strcmp(C[i].partenza,part)==0)  stampa(C[i]);
    }
}

void arrivi(int nr, corsa C[nr], char arr[maxl])
{
    int i;
    printf("le corse arrivate alla fermata sono:\n");
    for(i=0;i<nr;i++)
    {
        if(strcmp(C[i].destinazione,arr)==0)  stampa(C[i]);
    }
}

void ritardi(int nr,corsa C[nr],d data0,d data1)
{
    int i;
    printf("le corse con ritardo partite nell'intervallo di date sono:\n");
    for(i=0;i<nr;i++)
    {
        if(C[i].ritardo>0)  verificadata(data0,data1,C[i]);
    }
}

void rittot(int nr,corsa C[nr],char codice_tr[maxl])
{
    int i;
    int rtot=0;
    for(i=0;i<nr;i++)
    {
        if(strcmp(C[i].codice,codice_tr)==0)    rtot+=C[i].ritardo;
    }
    printf("il ritardo accumulato e: %d minuti\n",rtot);
}

void selezionaDati(int nr,corsa C[nr],comando_e codcmd)
{
    d data0,data1;
    char partenza[maxl];
    char capolinea[maxl];
    char codice_tr[maxl];
    switch (codcmd)
    {
        case r_date:
            printf("inserire un intervallo di date in formato aaaa/mm/gg:aaaa/mm/gg\n");
            scanf("%d/%d/%d:%d/%d/%d",&data0.aaaa,&data0.mm,&data0.gg,&data1.aaaa,&data1.mm,&data1.gg);
            date(nr,C,data0,data1);
            break;
        case r_partenza:
            printf("inserire la fermata da cui vedere le corse partite\n");
            scanf("%s",partenza);
            partenze(nr,C,partenza);
            break;
        case r_capolinea:
            printf("inserire la fermata a cui sono arrivate le corse da visualizzare\n");
            scanf("%s",capolinea);
            arrivi(nr,C,capolinea);
            break;
        case r_ritardo:
            printf("inserire l'intervallo di date in cui verificare quelle in ritardo in formato aaaa/mm/gg:aaaa/mm/gg\n");
            scanf("%d/%d/%d:%d/%d/%d",&data0.aaaa,&data0.mm,&data0.gg,&data1.aaaa,&data1.mm,&data1.gg);
            ritardi(nr,C,data0,data1);
            break;
        case r_ritardo_tot:
            printf("inserire il codice di tratta di cui si desidera visualizzare il ritardo complessivo \n");
            scanf("%s",codice_tr);
            rittot(nr,C,codice_tr);
            break;
        case r_fine:
            break;
    }
}

int main()
{
    FILE *f;
    corsa C[maxr];
    int nr;
    f=fopen("corse.txt","r");
    fscanf(f,"%d\n",&nr);
    comando_e codcmd=r_date;
    if (savefile(nr,f,C))
    {
        while(codcmd!=r_fine)
        {
            codcmd=leggiComando();
            selezionaDati(nr,C,codcmd);
        }
    }
    fclose(f);
    return 0;
}
