#include "pg.h"
#include "inv.h"

static int scanStatPg(char* str,stat_t* stat)
{
    char temp1[7],temp2[50],temp3[50];
    if(sscanf(str,"%7s%51s%51s%d%d%d%d%d%d ",temp1,temp2,temp3,&(stat->hp),&(stat->mp),&(stat->atk),&(stat->def),&(stat->mag),&(stat->spr))!=9)
        return 0;
    return 1;
}

static stat_t addStat(stat_t ad,stat_t add)
{
    add.hp+=ad.hp;
    add.mp+=ad.mp;
    add.atk+=ad.atk;
    add.def+=ad.def;
    add.mag+=ad.mag;
    add.spr+=ad.spr;
    return add;
}

static stat_t oppStat(stat_t invStat)
{
    invStat.hp=-invStat.hp;
    invStat.mp=-invStat.mp;
    invStat.atk=-invStat.atk;
    invStat.def=-invStat.def;
    invStat.mag=-invStat.mag;
    invStat.spr=-invStat.spr;
    return invStat;
}

int readstrPg(FILE* fp,caratteristiche* pt)
{
    char temp[200];
    if(fgets(temp,200,fp)==NULL)
    {
        printf("file di acquisizione terminato\n");
        return 0;
    }
    if(sscanf(temp,"%7s%51s%51s",pt->codice,pt->nome,pt->classe)!=3)
    {
        printf("errore nell'acquisizione\n");
        return 0;
    }
    if(!scanStatPg(temp,&(pt->statb)))
    {
        printf("errore nell'acquisizione\n");
        return 0;
    }
    pt->stateq=pt->statb;
    pt->equip=Eqinit();
    return 1;
}


int codisEq(caratteristiche* P,char* key)
{
    if(strcmp(P->codice,key)==0)
        return 1;
    return 0;
}

int modeqL1(caratteristiche* x,tabInvP tabInv)
{
    return modeqL0(x->equip,tabInv);
}

void pPgL1(caratteristiche* x,tabInvP tabInv)
{
    int i,index;
    printf("il nome è: %s, la classe e: %s\n",x->nome,x->classe);
    printf("le statistiche base sono: ");
    printStat(&(x->statb),1);
    printf("\n");
    if(equipArray_inUse(x->equip))
    {
        printf("le statistiche con equipaggiamenti sono: \n");
        x->stateq=x->statb;
        for(i=0;i<NINV;i++)
        {
            index=equipArray_getEquipByIndex(x->equip,i);
            if(index!=-1)
                x->stateq=addStat(sObjL1(tabInv,index)->stat,x->stateq);
        }
        printStat(&(x->stateq),1);
        printf("\n");
        printf("gli oggetti equipaggiati sono:\n");
        printEq(x->equip,tabInv);
    }
    else
        printf("il personaggio non ha equipaggiamenti\n");
    return;
}

void pg_clean(caratteristiche* pgc)
{
    equipArray_free(pgc->equip);
    return;
}
