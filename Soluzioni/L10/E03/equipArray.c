#include "equipArray.h"

typedef struct eq{
    int inUso;
    int vettEq[NINV];
}tabEquip_t;

Eq Eqinit()
{
    int i;
    Eq x;
    x=malloc(sizeof(tabEquip_t));
    x->inUso=0;
    for(i=0;i<NINV;i++)
        x->vettEq[i]=-1;
    return x;
}

static int findInvplace(int* x,int ind)
{
    int i;
    for(i=0;i<NINV;i++)
        if((x[i])==ind)
            return i;
    return -1;
}

int modeqL0(Eq x,tabInvP tabInv)
{
    int i;
    int add=-1;
    int index=-1,primoposto=-1;
    char temp[200];
    printf("vuoi aggiungere o togliere l'oggetto? <1 per aggiungere 0 per togliere>\n");
    fgets(temp,200,stdin);
    if((sscanf(temp,"%d ",&add))!=1)
        return 0;
    if(add==1)
    {
        if((primoposto=findInvplace(x->vettEq,-1))==-1)//equipArray
            return 0;
        if((index=sObjL2(tabInv))!=-1)//invArray.c
        {
            x->vettEq[primoposto]=index;
            x->inUso++;
            return 1;
        }
    }
    else if(add==0)
    {
        if((index=sObjL2(tabInv))!=-1)//invArray.c
        {
            if((primoposto=findInvplace(x->vettEq,index))==-1)//equipArray
                return 0;
            (x->vettEq[primoposto])=-1;
            x->inUso--;
            return 1;
        }
    }
    else printf("il flag dev'essere 0 o 1\n");
    return 0;
}

int equipArray_getEquipByIndex(Eq equipArray, int index)
{
    return equipArray->vettEq[index];
}

void printEq(Eq x,tabInvP tabInv)
{
    int i;
    for(i=0;(i<NINV);i++)
    {
        if(x->vettEq[i]>=0)
        {
            pObjL1(tabInv,x->vettEq[i]);//equipArray.c
        }
    }
    return;
}

int equipArray_inUse(Eq equipArray)
{
    return equipArray->inUso;
}

void equipArray_free(Eq equip)
{
    free(equip);
    return;
}
