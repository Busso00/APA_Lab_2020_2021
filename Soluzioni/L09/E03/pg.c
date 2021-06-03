#include "pg.h"

linkPg newnode(linkPg nextpg,caratteristiche val)
{
    linkPg x=(nodoPg_t*)malloc(sizeof(nodoPg_t));
    if(x==NULL)
    {
        printf("non c'è spazio in memoria per nuovi personaggi\n");
        return NULL;
    }
    else
    {
        x->next=nextpg;//il nodo, essendo aggiunto in coda punta a NULL
        x->pg_t=val;
    }
    return x;
}

void pgTinit(tabPg_t** tabPg)
{
    *tabPg=(tabPg_t*)malloc(sizeof(tabPg_t));
    (*tabPg)->headPg=NULL;
    (*tabPg)->tailPg=NULL;
    (*tabPg)->nPg=0;
    return;
}

int addintail(tabPg_t* tabPg,linkPg t)
{
    if(t==NULL)
        return 0;
    if((tabPg->nPg)==0)//se non ci sono elementi gli indirizzi di testa e coda coincidono con quello del nuovo nodo
        tabPg->headPg=t;
    else//se invece ce ne sono devo agganciare alla coda il nodo t
        tabPg->tailPg->next=t;
    tabPg->tailPg=t;
    tabPg->nPg++;
    return 1;
}

int scanpg(tabPg_t* tabPg,FILE* fp,int f)
{
    caratteristiche* pg;
    int i;
    linkPg t;
    pg=malloc(sizeof(caratteristiche));
    if(f)
        printf("scrivi le caratteristiche in ordine: codice nome classe hp mp atk def mag spr\n");
    if(readstr(fp,pg,'p'))
    {
        t=newnode(NULL,*pg);
        if(!addintail(tabPg,t))
            return 0;
        tabPg->tailPg->pg_t.equip.inUso=0;//inizializzo tutti gli equipaggiamenti
        for(i=0;i<NINV;i++)
            tabPg->tailPg->pg_t.equip.vettEq[i]=Eqsetvoid();
        return 1;
    }
    return 0;
}

int aggiungiTabpg(tabPg_t* tabPg)
{
    FILE* fp=NULL;
    int flag=0;
    if((fp=getfilep(fp))==NULL) return 0;
    while (scanpg(tabPg,fp,0))
        flag=1;
    fclose(fp);
    return flag;
}

int aggiungipg(tabPg_t* tabPg)
{
    if(scanpg(tabPg,stdin,1));
        return 1;
    return 0;
}

int scod(linkPg head,linkPg* xp,linkPg* pp)
{
    int l;
    char k[7];
    printf("scrivi il codice del personaggio\n");

    if(!(readstr(stdin,k,'c')))
        return 0;

    for(*xp=head,*pp=NULL;(*xp)!=NULL;*pp=*xp,*xp=(*xp)->next)
    {
        if(strcmp(((*xp)->pg_t.codice),k)==0)
        {
            printf("personaggio trovato!\n");
            return 1;
        }
    }
    printf("personaggio non trovato\n");
    return 0;
}

int searchcod(tabPg_t* tabPg)
{
    linkPg x,p;
    x=malloc(sizeof(nodoPg_t));
    p=malloc(sizeof(nodoPg_t));
    if(scod(tabPg->headPg,&x,&p))
        return 1;
    else
        return 0;
}

int listDelrKey(tabPg_t* tabPg)
{
    linkPg x,p;
    x=malloc(sizeof(nodoPg_t));
    p=malloc(sizeof(nodoPg_t));
    if(scod(tabPg->headPg,&x,&p))
    {
        if(x==tabPg->headPg)
            tabPg->headPg=x->next;
        else
            p->next = x->next;

        if(x==tabPg->tailPg)
            tabPg->tailPg=p;

        free(x);
        tabPg->nPg--;
        return 1;
    }
    return 0;
}

int elimpg(tabPg_t* tabPg)
{
    if((tabPg->nPg)<=0)
    {
        printf("non ci sono personaggi in lista!\n");
        return 0;
    }
    if(listDelrKey(tabPg));
        return 1;
    return 0;
}

int modeq(tabPg_t* tabPg,tabInv_t* tabInv)
{
    linkPg x,p;
    int add=-1;
    int index=-1,primoposto=-1;

    if((tabPg->nPg)<=0)
    {
        printf("non ci sono personaggi in lista!\n");
        return 0;
    }
    if((tabInv->nInv)<=0)
    {
        printf("non ci sono oggetti in lista!\n");
        return 0;
    }

    printf("vuoi aggiungere o togliere l'oggetto? <1 per aggiungere 0 per togliere>\n");
    if(!(readstr(stdin,&add,'n')))
        return 0;
    if(!scod(tabPg->headPg,&x,&p))
        return 0;
    if(add==1)
    {
        if(((index=sobj(tabInv->vettInv,tabInv->nInv,0))!=-1)&&((primoposto=sobj(x->pg_t.equip.vettEq,NINV,1))!=-1))
        {
            x->pg_t.equip.vettEq[primoposto]=tabInv->vettInv[index];
            x->pg_t.equip.inUso++;
            return 1;
        }
    }
    else if(add==0)
    {
        if((index=sobj(x->pg_t.equip.vettEq,NINV,0))!=-1)
        {
            (x->pg_t.equip.vettEq[index])=Eqsetvoid();
            x->pg_t.equip.inUso--;
            return 1;
        }
    }
    else printf("il flag dev'essere 0 o 1\n");
    return 0;
}

void printPg(tabPg_t* tabPg)
{
    stat_t res;
    linkPg x,p;
    int i;

    if(!scod(tabPg->headPg,&x,&p))
        return;

    printf("il nome è: %s, la classe e: %s\n",x->pg_t.nome,x->pg_t.classe);
    res=x->pg_t.stat;
    printf("le statistiche base sono: hp: %d mp:%d atk: %d def: %d mag: %d spr: %d\n",res.hp,res.mp,res.atk,res.def,res.mag,res.spr);
    printf("gli oggetti equipaggiati sono:\n");
    for(i=0;(i<NINV);i++)
    {
        if(strcmp((x->pg_t.equip.vettEq[i].nome),"none")!=0)
        {
            pObj(x->pg_t.equip.vettEq,i,NINV);

            res.hp+=x->pg_t.equip.vettEq[i].stat.hp;
            res.mp+=x->pg_t.equip.vettEq[i].stat.mp;
            res.atk+=x->pg_t.equip.vettEq[i].stat.atk;
            res.def+=x->pg_t.equip.vettEq[i].stat.def;
            res.mag+=x->pg_t.equip.vettEq[i].stat.mag;
            res.spr+=x->pg_t.equip.vettEq[i].stat.spr;
        }
    }
    printf("le statistiche con equipaggiamenti sono: ");
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
    if(res.spr>=0) printf("spr: %d ",res.spr);
    else printf("spr: 0 ");
    printf("\n");
    return;
}

linkPg listfreeR(linkPg i)
{
    if(i->next==NULL)
    {
        free(i);
        return NULL;
    }
    i->next=listfreeR(i->next);
    free(i);
    return NULL;
}

void liberaP(tabPg_t* tabPg)
{
    listfreeR(tabPg->headPg);
    return;
}
