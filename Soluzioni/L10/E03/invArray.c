#include "invArray.h"

typedef struct tabinv{
    inv_t* vettInv;
    int nInv;
}tabInv_t;

tabInvP invTinit()//inizializza il wrapper per l'inventario
{
    tabInvP tabInv;
    tabInv=(tabInv_t*)malloc(sizeof(tabInv_t));
    tabInv->nInv=0;
    return tabInv;
}

inv_t* sObjL1(tabInvP tabInv,int f)
{
    return &(tabInv->vettInv[f]);
}

int sObjL2(tabInvP tabInv)
{
    int i,n;
    char nomeoggetto[maxl];
    printf("scrivere il nome dell'oggetto\n");
    fgets(nomeoggetto,maxl,stdin);
    sscanf(nomeoggetto,"%s ",nomeoggetto);
    n=tabInv->nInv;
    for(i=0;i<n;i++)
        if(KeyisEq(nomeoggetto,&(tabInv->vettInv[i])))
        {
            printf("oggetto trovato\n");
            return i;
        }
    printf("oggetto non trovato\n");
    return -1;
}

void pObjL1(tabInvP tabInv,int f)
{
    int index;
    inv_t Obj;
    if(f==-1)
    {
        index=sObjL2(tabInv);
        if(index!=-1)
            Obj=tabInv->vettInv[index];
        else
            return;
    }
    else Obj=tabInv->vettInv[f];
    pObjL0(&Obj);
    return;
}

int aggiungiTabeq(tabInvP tabInv)
{
    int n,i;
    FILE* fp=NULL;
    n=0;
    char temp[200];
    printf("come si chiama il file?\n");
    fgets(temp,200,stdin);
    sscanf(temp,"%s ",temp);
    fp=fopen(temp,"r");
    if(fp==NULL)
    {
        printf("file non trovato!\n");
        return 0;
    }
    fscanf(fp,"%d ",&n);

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
    for(i=(tabInv->nInv)-n;(i<tabInv->nInv)&&(readstrEq(fp,&(tabInv->vettInv[i])));i++);
    fclose(fp);
    return (i==tabInv->nInv);
}

void liberaI(tabInvP tabInv)
{
    free(tabInv->vettInv);
    return;
}
