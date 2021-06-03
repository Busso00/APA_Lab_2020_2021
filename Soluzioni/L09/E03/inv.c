#include "inv.h"

inv_t Eqsetvoid()
{
    inv_t Obj;
    strcpy(Obj.nome,"none");
    strcpy(Obj.tipo,"none");
    Obj.stat.hp=0;
    Obj.stat.mp=0;
    Obj.stat.atk=0;
    Obj.stat.def=0;
    Obj.stat.mag=0;
    Obj.stat.spr=0;
    return Obj;
}

void invTinit(tabInv_t** tabInv)
{
    *tabInv=(tabInv_t*)malloc(sizeof(tabInv_t));
    (*tabInv)->nInv=0;
}

int aggiungiTabeq(tabInv_t* tabInv)
{
    int n,i;
    FILE* fp=NULL;
    n=0;
    if((fp=getfilep(fp))==NULL) return 0;
    readstr(fp,&n,'n');

    if((tabInv->nInv)==0)
    {
        tabInv->vettInv=(inv_t*)malloc(n*sizeof(inv_t));
        tabInv->nInv+=n;
    }
    else
    {
        tabInv->nInv+=n;
        tabInv->vettInv=(inv_t*)realloc(tabInv->vettInv,(tabInv->nInv)*sizeof(inv_t));
    }

    for(i=(tabInv->nInv)-n;(i<tabInv->nInv)&&(readstr(fp,&(tabInv->vettInv[i]),'i'));i++);
    fclose(fp);
    return (i==tabInv->nInv);
}

int sobj(inv_t* Inv,int n,int f)
{
    int i;
    char nomeoggetto[maxl];
    if(f==0)
    {
        printf("scrivere il nome dell'oggetto\n");
        readstr(stdin,nomeoggetto,'o');
    }
    else
        memcpy(nomeoggetto,"none",5);

    for(i=0;i<n;i++)
        if(strcmp(nomeoggetto,Inv[i].nome)==0)
        {
            if(f==0)
                printf("oggetto trovato\n");
            return i;
        }
    if(f==0)
        printf("oggetto non trovato\n");
    return -1;
}

int searchobj(tabInv_t* tabInv)
{
    if(sobj(tabInv->vettInv,tabInv->nInv,0)!=-1)
        return 0;
    return 1;
}

void pObj(inv_t* vettInv,int f,int n)
{
    int index;
    inv_t Obj;
    if(f==-1)
    {
        index=sobj(vettInv,n,0);
        if(index!=-1)
            Obj=vettInv[index];
        else
            return;
    }
    else Obj=vettInv[f];
    printf("nome: %s tipo: %s\n",Obj.nome,Obj.tipo);
    printf("bonus stat:  hp: %d mp:%d atk: %d def: %d mag: %d spr: %d\n",Obj.stat.hp,Obj.stat.mp,Obj.stat.atk,Obj.stat.def,Obj.stat.mag,Obj.stat.spr);
    return;
}

void printObj(tabInv_t* tabInv)
{
    pObj(tabInv->vettInv,-1,tabInv->nInv);
    return;
}

void liberaI(tabInv_t* tabInv)
{
    free(tabInv->vettInv);
    return;
}
