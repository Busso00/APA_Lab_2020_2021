#include "pgList.h"

typedef struct pg{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
}tabPg_t;

typedef struct nodo{
    caratteristiche pg_t;
    linkPg next;
}nodoPg_t;

tabPgP pgTinit()
{
    tabPgP tabPg;
    tabPg=(tabPg_t*)malloc(sizeof(tabPg_t));
    tabPg->headPg=NULL;
    tabPg->tailPg=NULL;
    tabPg->nPg=0;
    return tabPg;
}

static linkPg newnode(linkPg nextpg,caratteristiche val)
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

static int addintail(linkPg* head,linkPg* tail,int* nPg,linkPg t)
{
    if(t==NULL)
        return 0;
    if((*head)==NULL)//se non ci sono elementi gli indirizzi di testa e coda coincidono con quello del nuovo nodo
        *head=t;
    else//se invece ce ne sono devo agganciare alla coda il nodo t
        (*tail)->next=t;
    *tail=t;
    (*nPg)=(*nPg)+1;
    return 1;
}

static int scanpg(linkPg* head,linkPg* tail,int* nPg,FILE* fp,int f)
{
    caratteristiche* pg;
    linkPg t;
    pg=malloc(sizeof(caratteristiche));
    if(f)
        printf("scrivi le caratteristiche in ordine: codice nome classe hp mp atk def mag spr\n");
    if(readstrPg(fp,pg))
    {
        t=newnode(NULL,*pg);
        if(!addintail(head,tail,nPg,t))
            return 0;
        return 1;
    }
    return 0;
}

int aggiungiTabpg(tabPgP tabPg)
{
    FILE* fp=NULL;
    int flag=0;
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
    while (scanpg(&(tabPg->headPg),&(tabPg->tailPg),&(tabPg->nPg),fp,0))//scanpg()
        flag=1;
    fclose(fp);
    return flag;
}

int aggiungipg(tabPgP tabPg)
{
    return (scanpg(&(tabPg->headPg),&(tabPg->tailPg),&(tabPg->nPg),stdin,1));
}

static int scod(linkPg head,linkPg* xp,linkPg* pp)
{
    int l;
    char key[7];
    char temp[200];
    printf("scrivi il codice del personaggio\n");
    fgets(temp,201,stdin);
    if(sscanf(temp,"%7s ",key)!=1)
    {
        printf("codice non valido\n");
        return 0;
    }
    for(*xp=head,*pp=NULL;(*xp)!=NULL;*pp=*xp,*xp=(*xp)->next)
    {
        if(codisEq(&((*xp)->pg_t),key))  // codisEq funzionava anche passando coome primo parametro *xp non so perchè
        {
            printf("personaggio trovato!\n");
            return 1;
        }
    }
    printf("personaggio non trovato\n");
    return 0;
}

/*static caratteristiche* scod(linkPg head,linkPg* xp,linkPg* pp)
{
    int l;
    char key[7];
    char temp[200];
    printf("scrivi il codice del personaggio\n");
    fgets(temp,200,stdin);
    if(sscanf(temp,"%7s ",key)!=1)
    {
        printf("codice non valido\n");
        return NULL;
    }
    for(*xp=head,*pp=NULL;(*xp)!=NULL;*pp=*xp,*xp=(*xp)->next)
    {
        if(codisEq(&((*xp)->pg_t),key))   //codisEq funzionava anche passando coome primo parametro *xp non so perchè
        {
            printf("personaggio trovato!\n");
            return &((*xp)->pg_t);
        }
    }
    printf("personaggio non trovato\n");
    return NULL;
}*/

/*caratteristiche* searchcod(tabPgP tabPg);
{
    linkPg x,p;
    x=malloc(sizeof(linkPg));
    p=malloc(sizeof(linkPg));

    return scod(tabPg->headPg,&x,&p);
}
*/

int searchcod(tabPgP tabPg)
{
    linkPg x,p;
    x=malloc(sizeof(linkPg));
    p=malloc(sizeof(linkPg));
    if(scod(tabPg->headPg,&x,&p))
        return 1;
    return 0;
}

int modeq(tabPgP tabPg,tabInvP tabInv)
{
    linkPg x,p;
    if((tabPg->nPg)<=0)
    {
        printf("non ci sono personaggi in lista!\n");
        return 0;
    }
    if(!scod(tabPg->headPg,&x,&p))
        return 0;
    if(modeqL1(&(x->pg_t),tabInv))
        return 1;
    return 0;
}

void printPg(tabPgP tabPg,tabInvP tabInv)
{

    linkPg x,p;
    int i;

    if(!scod(tabPg->headPg,&x,&p))
        return;

    pPgL1(x,tabInv);

    return;
}

static void DelNode(linkPg* head,linkPg* tail,linkPg x,linkPg p)
{
    if(x==(*head))
        *head=x->next;
    else
        p->next = x->next;
    if(x==(*tail))
        *tail=p;
    pg_clean(&(x->pg_t));
    return;
}

int listDelrKey(tabPgP tabPg)
{
    linkPg x,p;
    x=malloc(sizeof(linkPg));
    p=malloc(sizeof(linkPg));
    if((tabPg->nPg)<=0)
    {
        printf("non ci sono personaggi in lista!\n");
        return tabPg->nPg;
    }
    if(scod(tabPg->headPg,&x,&p)) // !=NULL
    {
        DelNode(&(tabPg->headPg),&(tabPg->tailPg),x,p);
        free(x);
        tabPg->nPg--;
    }
    return tabPg->nPg;
}

linkPg listfreeR(linkPg* i)
{
    if((*i)->next==NULL)
    {
        free(*i);
        return NULL;
    }
    pg_clean(&((*i)->pg_t));
    (*i)->next=listfreeR(&((*i)->next));
    free(*i);
    return NULL;
}

void liberaP(tabPgP tabPg)
{
    listfreeR(&(tabPg->headPg));
    return;
}

