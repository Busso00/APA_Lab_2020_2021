#include "inv.h"

void printStat(stat_t* res,int soglia)
{
    if(res->hp>=soglia) printf("hp: %d ",res->hp);
    else printf("hp: %d ",soglia);
    if(res->mp>=soglia) printf("mp: %d ",res->mp);
    else printf("mp: %d ",soglia);
    if(res->atk>=soglia) printf("atk: %d ",res->atk);
    else printf("atk: %d ",soglia);
    if(res->def>=soglia) printf("def: %d ",res->def);
    else printf("def: %d ",soglia);
    if(res->mag>=soglia) printf("mag: %d ",res->mag);
    else printf("mag: %d ",soglia);
    if(res->spr>=soglia) printf("spr: %d ",res->spr);
    else printf("spr: %d ",soglia);
    return;
}


int scanStatObj(char* str,stat_t* stat)
{
    char temp1[50],temp2[50];
    if(sscanf(str,"%51s%51s%d%d%d%d%d%d ",temp1,temp2,&(stat->hp),&(stat->mp),&(stat->atk),&(stat->def),&(stat->mag),&(stat->spr))!=8)
        return 0;
    return 1;
}

stat_t inv_getStat(inv_t* invp)
{
    return invp->stat;
}

void pObjL0(inv_t* Obj)
{
    printf("nome: %s tipo: %s\n",Obj->nome,Obj->tipo);
    printf("bonus stat:  ");
    printStat(&(Obj->stat),-2147483647);
    printf("\n");
    return;
}

int KeyisEq(char* nomeoggetto,inv_t* Obj)
{
    if(strcmp(nomeoggetto,Obj->nome)==0)
        return 1;
    return 0;
}

int readstrEq(FILE* fp,inv_t* it)
{
    char temp[200];
    if(fgets(temp,200,fp)==NULL)
    {
        printf("file di acquisizione terminato\n");
        return 0;
    }
    if(sscanf(temp,"%51s%51s ",it->nome,it->tipo)!=2)
    {
        printf("errore nell'acquisizione\n");
        return 0;
    }
    if(!scanStatObj(temp,&(it->stat)))
        return 0;
    return 1;
}
