#include "gestioneio.h"

FILE* getfilep(FILE* fp)
{
    char temp[200];
    printf("come si chiama il file?\n");
    fgets(temp,200,stdin);
    sscanf(temp,"%s ",temp);
    fp=fopen(temp,"r");
    if(fp==NULL)    printf("file non trovato!\n");
    return fp;
}

int readstr(FILE* fp,void* dest,int flag)
{
    char temp[200];
    caratteristiche* pt;
    inv_t* it;
    int* nt;
    char* nomeoggetto;
    char* cod;
    if(fgets(temp,200,fp)==NULL)
    {
        printf("file di acquisizione terminato\n");
        return 0;
    }
    switch(flag)
    {
    case 'p':
        pt=(caratteristiche*) dest;
        if(sscanf(temp,"%7s%51s%51s%d%d%d%d%d%d ",pt->codice,pt->nome,pt->classe,&(pt->stat.hp),&(pt->stat.mp),&(pt->stat.atk),&(pt->stat.def),&(pt->stat.mag),&(pt->stat.spr))!=9)
        {
            printf("errore nell'acquisizione\n");
            return 0;
        }
        break;
    case 'i':
        it=(inv_t*)dest;
        if(sscanf(temp,"%51s%51s%d%d%d%d%d%d ",it->nome,it->tipo,&(it->stat.hp),&(it->stat.mp),&(it->stat.atk),&(it->stat.def),&(it->stat.mag),&(it->stat.spr))!=8)
        {
            printf("errore nell'acquisizione\n");
            return 0;
        }
        break;
    case 'n':
        nt=(int*)dest;
        if(sscanf(temp,"%d",nt)!=1)
        {
            printf("errore nell'acquisizione\n");
            return 0;
        }
        break;
    case 'o':
        nomeoggetto=(char*)dest;
        if(sscanf(temp,"%51s ",nomeoggetto)!=1)
        {
            printf("errore nell'acquisizione\n");
            return 0;
        }
        break;
    case 'c':
        cod=(char*)dest;
        if(sscanf(temp,"%7s ",cod)!=1)
        {
            printf("errore nell'acquisizione\n");
            return 0;
        }
        break;
    }
    return 1;
}

