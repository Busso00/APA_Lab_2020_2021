#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxl 50

typedef struct
{
    int g,m,a;
}data;

typedef struct
{
    char nome[maxl];
    char cognome[maxl];
    char codice[maxl];
    data data_di_nascita;
    char via[maxl];
    char citta[maxl];
    int cap;
}Item;

typedef struct node* link;

struct node
{
    Item val;
    link next;
};

typedef enum
{
    c_new,c_newfile,c_searchcod,c_deletecod,c_deletedates,c_printfile,c_end
}cmd;

cmd selectcode(void)
{
    char comando[30];
    char cmdtable[c_end][30]={"nuovo","nuovodafile","cercacodice","canccodice","cancdate","stampafile","fine"};
    cmd codcmd;
    printf("inserisci un comando tra nuovo,nuovodafile,cercacodice,canccodice,cancdate,stampafile,fine\n");
    fgets(comando,30,stdin);
    sscanf(comando,"%s",comando);
    codcmd=c_new;
    while((codcmd<c_end)&&(strcmp(cmdtable[codcmd],comando)!=0))    codcmd++;
    return codcmd;
}

Item getins()
{
    FILE* fp=stdin;
    Item ins;
    char temp[maxl];
    printf("scrivi codice\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%s",&ins.codice);
    printf("scrivi nome\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%s",&ins.nome);
    printf("scrivi cognome\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%s",&ins.cognome);
    printf("scrivi giorno di nascita\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%d",&ins.data_di_nascita.g);
    printf("scrivi mese di nascita\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%d",&ins.data_di_nascita.m);
    printf("scrivi anno di nascita\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%d",&ins.data_di_nascita.a);
    printf("scrivi via di residenza\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%s",&ins.via);
    printf("scrivi citta' di residenza\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%s",&ins.citta);
    printf("scrivi il cap\n");
    fgets(temp,maxl,fp);
    sscanf(temp,"%d",&ins.cap);
    return ins;
}

int datamagg(data a,data b)
{
    if(a.a>b.a) return 1;
    else if((a.a==b.a)&&(a.m>b.m))  return 1;
    else if(a.a<b.a) return 0;
    else if((a.m==b.m)&&(a.g>b.g))  return 1;
    return 0;
}


link newnode(Item val,link next)
{
    link x=malloc(sizeof(*x));
    if(x==NULL) return NULL;
    else
    {
        x->val=val;
        x->next=next;
    }
    return x;
}

link sortlistOrd(Item val,link h)
{
    link x,p;
    data k= val.data_di_nascita;
    if((h==NULL)||(datamagg(k,(h->val.data_di_nascita)))) return newnode(val,h);//magggiore nella data significa pi  recente
    for(x=h->next,p=h;(x!=NULL)&&(datamagg(x->val.data_di_nascita,k));p=x,x=x->next);
    p->next=newnode(val,x);
    return h;
}

Item ItemSetVoid()
{
    Item temp;
    temp.cap=0;
    strcpy(temp.nome,"");
    strcpy(temp.cognome,"");
    strcpy(temp.citta,"");
    strcpy(temp.codice,"");
    strcpy(temp.via,"");
    temp.data_di_nascita.a=0;
    temp.data_di_nascita.m=0;
    temp.data_di_nascita.g=0;
    return temp;
}

Item listSearch(char* key,link h)
{
    link x;
    for(x=h;x!=NULL;x=x->next)
        if(strcmp(key,x->val.codice)==0)
            return x->val;
    return ItemSetVoid();
}

Item sortListDel(char* key,link* h)
{
    link x,p;
    Item temp;
    if(*h==NULL) return ItemSetVoid();
    for(x=*h,p=NULL;x!=NULL;p=x,x=x->next)
    {
        if(strcmp(key,x->val.codice)==0)
        {
            if(x==*h)
            {
                *h=x->next;
                temp=x->val;
                free(x);
                return temp;
            }
            else
            {
                p->next=x->next;
                temp=x->val;
                free(x);
                return temp;
            }
        }
    }
    return  ItemSetVoid();
}

Item sortListDelRep(data di,data df,link* h,int *flag)
{
    link x,p;
    Item temp;
    if(*h==NULL) return ItemSetVoid();
    for(x=*h,p=NULL;x!=NULL&&(*flag);p=x,x=x->next)
    {
        if(datamagg(x->val.data_di_nascita,di)&&datamagg(df,x->val.data_di_nascita))
        {
            if(x==*h)
            {
                *h=x->next;
                temp=x->val;
                free(x);
                return temp;
            }
            else
            {
                p->next=x->next;
                temp=x->val;
                free(x);
                return temp;
            }
        }
    }
    *flag=0;
    return  ItemSetVoid();
}

FILE* printval(Item ins,FILE* fp)
{
    fprintf(fp,"%s %s %s %d/%d/%d %s %s %d\n",ins.codice,ins.nome,ins.cognome,ins.data_di_nascita.g,ins.data_di_nascita.m,ins.data_di_nascita.a,ins.via,ins.citta,ins.cap);
    return fp;
}

void selezionadati(link* h, cmd codcmd)
{
    Item ins,find;
    FILE *fp;
    int flag;
    char nomefile[maxl];
    char temp[250];
    char codkey[6];
    link x;
    data di,df;
    switch(codcmd)
    {
        case c_new:

            ins=getins();
            *h=sortlistOrd(ins,*h);
            break;

        case c_newfile:

            printf("nome del file anagrafica\n");
            fgets(nomefile,maxl,stdin);
            sscanf(nomefile,"%s",nomefile);
            fp=fopen(nomefile,"r");
            if(fp==NULL)    printf("file non trovato\n");

            while(fgets(temp,250,fp)!=NULL)
            {
                sscanf(temp,"%s %s %s %d/%d/%d %s %s %d",&ins.codice,&ins.nome,&ins.cognome,&ins.data_di_nascita.g,&ins.data_di_nascita.m,&ins.data_di_nascita.a,&ins.via,&ins.citta,&ins.cap);
                *h=sortlistOrd(ins,*h);
            }

            fclose(fp);
            break;

        case c_searchcod:

            printf("inserire il codice cercato\n");
            fgets(codkey,maxl,stdin);
            sscanf(codkey,"%s",codkey);

            find=listSearch(codkey,*h);
            printf("%s %s %s %d/%d/%d %s %s %d\n",find.codice,find.nome,find.cognome,find.data_di_nascita.g,find.data_di_nascita.m,find.data_di_nascita.a,find.via,find.citta,find.cap);
            break;

        case c_deletecod:

            printf("inserire il codice da eliminare\n");
            fgets(codkey,maxl,stdin);
            sscanf(codkey,"%s",codkey);

            find=sortListDel(codkey,h);
            printf("%s %s %s %d/%d/%d %s %s %d\n",find.codice,find.nome,find.cognome,find.data_di_nascita.g,find.data_di_nascita.m,find.data_di_nascita.a,find.via,find.citta,find.cap);
            break;

        case c_deletedates:

            printf("inserire l'intervallo di date da eliminare nei formati gg/mm/aaaa\ndata di inizio:\n");
            fgets(temp,maxl,stdin);
            sscanf(temp,"%d/%d/%d ",&di.g,&di.m,&di.a);
            printf("data di fine:\n");
            fgets(temp,maxl,stdin);
            sscanf(temp,"%d/%d/%d ",&df.g,&df.m,&df.a);
            flag=1;

            while(flag)
            {
                find=sortListDelRep(di,df,h,&flag);
                if(flag)
                    printf("%s %s %s %d/%d/%d %s %s %d\n",find.codice,find.nome,find.cognome,find.data_di_nascita.g,find.data_di_nascita.m,find.data_di_nascita.a,find.via,find.citta,find.cap);
            }
            break;

        case c_printfile:

            printf("inserire nome file destinazione\n");
            fgets(nomefile,maxl,stdin);
            sscanf(nomefile,"%s",nomefile);
            fp=fopen(nomefile,"w");
            if(fp==NULL) printf("errore nell'apertura file\n");

            for(x=*h;x!=NULL;x=x->next)
                fp=printval(x->val,fp);
            fclose(fp);
            break;

        case c_end:
            break;

    }
}

int main()
{
    link h=NULL;
    cmd codcmd=c_new;
    while(codcmd!=c_end)
    {
        codcmd=selectcode();
        selezionadati(&h,codcmd);
    }
    return 0;
}
