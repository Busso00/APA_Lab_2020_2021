#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxl 50
#define ninv 8

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}stat_t;

typedef struct{
    char nome[maxl];
    char tipo[maxl];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

typedef struct{
    int inUso;
    inv_t vettEq[ninv];
}tabEquip_t;

typedef struct{
    char codice[7];
    char nome[maxl];
    char classe[maxl];
    tabEquip_t equip;
    stat_t stat;
}caratteristiche;

typedef struct nodo* linkPg;

typedef struct nodo{
    caratteristiche pg_t;
    linkPg next;
}nodoPg_t;

typedef struct{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
}tabPg_t;

typedef enum{
    c_addpgT,c_addeq,c_addpg,c_delpg,c_modeq,c_calcstats,c_fine,c_notfound
}comando_c;

comando_c getcommand()
{
    comando_c i;
    char temp[20];
    char cmdtab[c_notfound][20]={"newPgT","newInvT","newPg","delPg","modEq","calcStat","fine",""};
    printf("per caricare una tabella di personaggi digitare: newPgT\n");
    printf("per caricare una tabella di oggetti digitare: newInvT\n");
    printf("per caricare un personaggio digitare: newPg\n");
    printf("per eliminare un personaggio digitare: delPg\n");
    printf("per aggiungere/togliere oggetti all'equipaggiamento del personaggio digitare: modEq\n");
    printf("per calcolare le statistiche di un personaggio digitare: calcStat\n");
    printf("per terminare digitare: fine\n");
    fgets(temp,20,stdin);
    sscanf(temp,"%s ",temp);
    for(i=c_addpgT;i<c_notfound&&(strcmp(temp,cmdtab[i])!=0);i++);
    return i;

}

linkPg newnodeT(linkPg newpg,caratteristiche val)
{
    linkPg x=(nodoPg_t*)malloc(sizeof(nodoPg_t));
    if(x==NULL) return NULL;
    else{
        x->next=NULL;
        x->pg_t=val;
    }
    return x;
}

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

void aggiungiTabpg(FILE* fp,tabPg_t* tabPg)
{
    int i;
    linkPg newpg,t;
    caratteristiche pg;
    char temp[200];

    while(fgets(temp,200,fp)!=NULL)
    {
        if(!(sscanf(temp,"%7s %s %s %d %d %d %d %d %d ",&(pg.codice),&(pg.nome),&(pg.classe),&(pg.stat.hp),&(pg.stat.mp),&(pg.stat.atk),&(pg.stat.def),&(pg.stat.mag),&(pg.stat.spr))==9))
        {
            printf("errore nell'acquisizione\n");
            return;
        }
        t=newnodeT(tabPg->tailPg,pg);
        if(tabPg->nPg==0)
        {
            tabPg->headPg=t;
            tabPg->tailPg=t;
        }
        else
        {
            tabPg->tailPg->next=t;
        }
        tabPg->tailPg=t;
        tabPg->nPg++;
        tabPg->tailPg->pg_t.equip.inUso=0;
        for(i=0;i<ninv;i++)
        {
            tabPg->tailPg->pg_t.equip.vettEq[i]=Eqsetvoid();
        }
    }
}

void aggiungiTabeq(FILE* fp,tabInv_t* tabInv)
{
    int n,i;
    char temp[200];
    fgets(temp,200,fp);
    sscanf(temp,"%d ",&(tabInv->nInv));
    tabInv->vettInv=(inv_t*)malloc((tabInv->nInv)*sizeof(inv_t));

    for(i=0;i<(tabInv->nInv);i++)
    {
        fgets(temp,200,fp);
        if(!(sscanf(temp,"%s %s %d %d %d %d %d %d ",&(tabInv->vettInv[i].nome),&(tabInv->vettInv[i].tipo),&(tabInv->vettInv[i].stat.hp),&(tabInv->vettInv[i].stat.mp),&(tabInv->vettInv[i].stat.atk),&(tabInv->vettInv[i].stat.def),&(tabInv->vettInv[i].stat.mag),&(tabInv->vettInv[i].stat.spr))==8))
        {
            printf("errore nell'acquisizione\n");
            return;
        }
    }
    return;
}

void aggiungipg(tabPg_t* tabPg)
{
    linkPg newpg,t;
    char temp[200];
    int i;
    caratteristiche pg;

    printf("scrivi le caratteristiche in ordine: codice nome classe hp mp atk def mag spr\n");
    fgets(temp,200,stdin);
    if(!(sscanf(temp,"%7s %s %s %d %d %d %d %d %d ",&(pg.codice),&(pg.nome),&(pg.classe),&(pg.stat.hp),&(pg.stat.mp),&(pg.stat.atk),&(pg.stat.def),&(pg.stat.mag),&(pg.stat.spr))==9))
    {
        printf("errore nell'acquisizione\n");
        return;
    }

    t=newnodeT(tabPg->tailPg,pg);
    if(tabPg->nPg==0)
    {
        tabPg->headPg=t;
        tabPg->tailPg=t;
    }
    else
    {
        tabPg->tailPg->next=t;
    }
    tabPg->tailPg=t;
    tabPg->nPg++;
    tabPg->tailPg->pg_t.equip.inUso=0;
    for(i=0;i<ninv;i++)
    {
        tabPg->tailPg->pg_t.equip.vettEq[i]=Eqsetvoid();
    }
    return;
}

void listDelrKey(tabPg_t* tabPg,char k[7]) {
    linkPg *xp, t,p;
    caratteristiche i;
    int f=0;
    for (xp=&(tabPg->headPg),p=NULL;(*xp)!=NULL;p=(*xp),xp=&((*xp)->next))
    {
        if (strncmp((*xp)->pg_t.codice,k,6)==0)
        {
            t = *xp;
            if((*xp)==tabPg->tailPg)
                tabPg->tailPg=p;
            *xp = (*xp)->next;
            i = t->pg_t;
            free(t);
            if((*xp)==tabPg->headPg)
                tabPg->headPg=*xp;
            f=1;
            tabPg->nPg--;
            break;
        }
    }
    if(!f)  printf("codice personaggio non presente\n");
    return;
}

void elimpg(tabPg_t* tabPg)
{
    char codice[7],temp[200];
    printf("scrivere il codice del personaggio da eliminare\n");
    fgets(temp,200,stdin);
    if(!(sscanf(temp,"%7s ",codice)==1))
    {
        printf("codice in formato errato\n");
        return;
    }

    listDelrKey(tabPg,codice);

    return;
}

void modeq(tabPg_t* tabPg,tabInv_t* tabInv)
{
    char nomeoggetto[maxl],codpg[7],temp[200]={'\0'};
    linkPg x;
    int add=1;
    int i,j;
    int primoposto=-1;
    int index=-1;

    printf("vuoi aggiungere o togliere l'oggetto? <1 per aggiungere 0 per togliere> <nome dell'oggetto> <codice personaggio>\n");
    fgets(temp,200,stdin);

    if(!(sscanf(temp,"%d %s %7s",&add,nomeoggetto,codpg)==3))
    {
        printf("istruzione non corretta\n");
        return;
    }

    if(add==1)
    {
        for(x=tabPg->headPg;(x!=NULL)&&(!(strncmp((x->pg_t.codice),codpg,6)==0));x=x->next);
        if(x==NULL)
        {
            printf("personaggio non presente\n");
            return;
        }

        for(i=0;i<(tabInv->nInv)&&(index==-1);i++){
            if(strcmp(nomeoggetto,tabInv->vettInv[i].nome)==0)
            {
                index=i;
            }
        }

        if(index==-1)
        {
            printf("oggetto non trovato\n");
            return;
        }

        for(j=0;(j<ninv)&&(primoposto==-1);j++) if(strcmp((x->pg_t.equip.vettEq[j].nome),"none")==0) primoposto=j;

        if(primoposto!=-1)
        {
            x->pg_t.equip.vettEq[primoposto]=tabInv->vettInv[index];
            x->pg_t.equip.inUso++;
        }
        else    printf("l'inventario è gia pieno\n");
    }
    else if(add==0)
    {
        for(x=tabPg->headPg;(x!=NULL)&&(!(strncmp((x->pg_t.codice),codpg,6)==0));x=x->next);
        if(x==NULL)
        {
            printf("personaggio non presente\n");
            return;
        }

        for(j=0;(j<ninv)&&(index==-1);j++) if(strcmp((x->pg_t.equip.vettEq[j].nome),nomeoggetto)==0) index=j;

        if(index!=-1)
        {
            x->pg_t.equip.vettEq[index]=Eqsetvoid();
            x->pg_t.equip.inUso--;
        }
        else
        {
            printf("oggetto non trovato\n");
            return;
        }
    }
    return;
}

void calcs(tabPg_t* tabPg)
{
    stat_t res;
    char cod[7],temp[200];
    linkPg x;
    int i;

    printf("scrivere il codice del personaggio di cui vedere le statistiche\n");
    fgets(temp,200,stdin);
    if(!(sscanf(temp,"%7s ",cod)==1))
    {
        printf("codice in formato errato\n");
        return;
    }
    for(x=tabPg->headPg;(x!=NULL)&&(!(strncmp(x->pg_t.codice,cod,6)==0));x=x->next);
    if(x==NULL)
    {
        printf("personaggio non trovato\n");
        return;
    }

    res=x->pg_t.stat;

    for(i=0;(i<ninv);i++)
    {
        res.hp+=x->pg_t.equip.vettEq[i].stat.hp;
        res.mp+=x->pg_t.equip.vettEq[i].stat.mp;
        res.atk+=x->pg_t.equip.vettEq[i].stat.atk;
        res.def+=x->pg_t.equip.vettEq[i].stat.def;
        res.mag+=x->pg_t.equip.vettEq[i].stat.mag;
        res.spr+=x->pg_t.equip.vettEq[i].stat.spr;
    }

    if(x!=NULL)
    {
        if(res.hp>=0) printf("hp: %d ",res.hp);
        else printf("hp: 0 ");
        if(res.mp>=0) printf("mp: %d ",res.mp);
        else printf("mp: 0 ");
        if(res.atk>=0) printf("atk: %d ",res.atk);
        else printf("atk: 0 ");
        if(res.def>=0) printf("def: %d ",res.def);
        else printf("def: 0 ");
        if(res.mag>=0) printf("mag: %d ",res.mag);
        else printf("mag: 0 ");
        if(res.spr>=0) printf("spr: %d \n",res.spr);
        else printf("spr: 0 \n");

    }
    return;
}

int main()
{
    FILE *fppg,*fpinv;
    tabPg_t* tabPg;
    tabInv_t* tabInv;
    comando_c codcmd=c_addpgT;
    tabPg=(tabPg_t*)malloc(sizeof(tabPg_t));
    tabInv=(tabInv_t*)malloc(sizeof(tabInv_t));
    tabPg->headPg=NULL;
    tabPg->tailPg=NULL;
    tabPg->nPg=0;
    tabInv->nInv=0;
    while (codcmd!=c_fine)
    {
        codcmd=getcommand();
        switch(codcmd)
        {
            case c_addpgT:
                fppg=fopen("pg.txt","r");
                aggiungiTabpg(fppg,tabPg);
                fclose(fppg);
                break;
            case c_addeq:
                fpinv=fopen("inventario.txt","r");
                aggiungiTabeq(fpinv,tabInv);
                fclose(fpinv);
                break;
            case c_addpg:
                aggiungipg(tabPg);
                break;
            case c_delpg:
                if((tabPg->nPg)>0)
                    elimpg(tabPg);
                else
                    printf("non ci sono personaggi in lista!\n");
                break;
            case c_modeq:
                if((tabPg->nPg)>0)
                    if((tabInv->nInv)>0)
                        modeq(tabPg,tabInv);
                    else    printf("non ci sono oggetti in lista!\n");
                else    printf("non ci sono personaggi in lista!\n");
                break;
            case c_calcstats:
                if((tabPg->nPg)>0)
                    calcs(tabPg);
                else
                    printf("non ci sono personaggi in lista!\n");
                break;
            case c_fine:
                break;
            case c_notfound:
                printf("comando non trovato\n");
                break;
        }
    }
    return 0;
}
