#include "titoli.h"
typedef struct titoli{
	int N;
	link head;
}Titles;

typedef struct{
	char codice[MAXL];
	BSTP quotes;
}Item;

typedef struct titolo{
	Item val;
	link next;
}Title;

tTab Tinit(){
	tTab T;
	T=(tTab)malloc(sizeof(Titles));
	T->N=0;
	T->head=NULL;
	return T;
}

void freelist(link P){
    if(P->next==NULL){
        BSTfree(P->val.quotes);
        free(P);
        return;
    }
    freelist(P->next);
    BSTfree(P->val.quotes);
    free(P);
    return;
}

void freeT(tTab T){
    if(T->head!=NULL){
        freelist(T->head);
    }
    free(T);
    return;
}

static link newNode(Item val, link next) {
 	link x =(link) malloc(sizeof(*x));
	if (x==NULL)
		return NULL;
 	else {
 		x->val = val;
 		x->next = next;
 	}
 	return x;
}

static link search(link head,char* cod){
    link t;
    for(t=head;(t!=NULL)&&(strcmp(t->val.codice,cod)!=0);t=t->next);
	return t;
}

static Item getval(FILE* fp,link node,char* codice){
	Item val;
	strcpy(val.codice,codice);
	if(node==NULL){
        val.quotes=BSTinit();
        val.quotes=getquotes(fp,val.quotes);
	}
	else
        val.quotes=getquotes(fp,node->val.quotes);
	return val;
}

static link addT(link head,int N,int* Neff,FILE* fp){
	int i;
	link ins,t=head;
	Item val;
	fscanf(fp,"%s ",val.codice);
	ins=search(head,val.codice);
    val=getval(fp,ins,val.codice);
    if(head==NULL){
        head=newNode(val,NULL);
        t=head;
        (*Neff)++;
    }
    else{
        while((t->next)!=NULL)
            t=t->next;
        if(ins!=NULL)
            ins->val=val;
        else{
            t->next=newNode(val,NULL);
            t=t->next;
            (*Neff)++;
        }
    }
	for(i=0;i<N-1;i++){
		fscanf(fp,"%s ",val.codice);
        ins=search(head,val.codice);
        val=getval(fp,ins,val.codice);
		if((ins=search(head,val.codice))!=NULL)
            ins->val=val;
        else{
            t->next=newNode(val,NULL);
            t=t->next;
            (*Neff)++;
        }
	}
	return head;
}

tTab getT(tTab T,FILE* fp){
	int N;
	fscanf(fp,"%d",&N);
	T->head=addT(T->head,N,&(T->N),fp);
	return T;
}



link searcht(tTab T,char* cod){
	return search(T->head,cod);
}

Tquote BSTsearchL2(link T,timep k){
    return BSTsearch(T->val.quotes,k);
}

void BSTsearchMmL2(link titolo,timep k,timep k1,Tquote* QMm){
    BSTsearchMm(titolo->val.quotes,k,k1,QMm);
    return;
}

int BSTunbheightL2(link titolo,float RH){
    return BSTunbheight(titolo->val.quotes,RH);
}

void BSTbalanceL2(link titolo){
    BSTbalance(titolo->val.quotes);
    return;
}
