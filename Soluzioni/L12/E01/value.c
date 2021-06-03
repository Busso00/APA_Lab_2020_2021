
#include "value.h"
typedef struct BSTnode* linkBST;
struct BSTnode {Tquote nodeq;linkBST l; linkBST  r;int N;};

typedef struct BST{
	linkBST root;
	linkBST z;
};

typedef struct{
	timep date;
	int value;
	int n;
}transaction;

static linkBST NEW(Tquote item, linkBST l, linkBST r, int N) {
  	linkBST x = malloc(sizeof *x);
  	x->nodeq = item; x->l = l; x->r = r; x->N=N;
  	return x;
}

static linkBST insertR(linkBST h,Tquote x, linkBST z) {
    if (h == z)
        return NEW(x, z, z, 1);
    h->N++;
    if (KEYcmp(x.date,h->nodeq.date)==-1)
        h->l = insertR(h->l, x, z);
    else if(KEYcmp(x.date,h->nodeq.date)==1)
        h->r = insertR(h->r, x, z);
    return h;
}

BSTP BSTinsert(BSTP bst,Tquote x) {
    bst->root=insertR(bst->root, x, bst->z);
    return bst;
}

Tquote ITEMsetNull(){
    Tquote T;
    T.Q=0.0;
    T.n=0;
    T.date=ITEMsetNullD();
    return T;
}

int ITEMcheckNull(Tquote T){
    if((T.Q==0.0)&&(ITEMcheckNullD(T.date)))
        return 1;
    return 0;
}

BSTP BSTinit(void){
  	BSTP bst = malloc(sizeof *bst) ;
  	bst->root = ( bst->z = NEW(ITEMsetNull(), NULL, NULL, 0));
  	return bst;
}

static linkBST rotR(linkBST h) {
  linkBST x = h->l;
  h->l = x->r;
  x->r = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

static linkBST rotL(linkBST h) {
  linkBST x = h->r;
  h->r = x->l;
  x->l = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

static linkBST partR(linkBST h, int r) {
  int t  = h->l->N;
  if ( t > r) {
    h->l = partR(h->l, r);
    h = rotR(h);
  }
  if ( t < r) {
    h->r = partR(h->r, r-t-1);
    h = rotL(h);
  }
  return h;
}

linkBST joinLR(linkBST a, linkBST b, linkBST z) {
    if (b == z)
    return a;
    b = partR(b, 0);
    b->l = a;
    b->N = a->N + b->r->N +1;
    return b;
}

linkBST BSTsdel(linkBST h,linkBST z,timep k){
    int cmp;
    linkBST y;
  	if (h == z)
        return z;
  	cmp = KEYcmp(k, h->nodeq.date);
 	if (cmp==-1)
        h->l=BSTsdel(h->l, z, k);
  	else if(cmp==1)
        h->r=BSTsdel(h->r, z, k);
    h->N--;
  	if (cmp==0){
        y = h;
        h = joinLR(h->l, h->r, z);
        free(y);
  	}
    return h;
}

BSTP BSTdelete(BSTP quotes,timep D){
    quotes->root=BSTsdel(quotes->root,quotes->z,D);
    return quotes;
}

BSTP getquotes(FILE* fp,BSTP quotes){
	int N,i,j,k=0;
	transaction* T,*Tval;
	float valuetot=0.0;
	Tquote Q,TEMP;
	fscanf(fp,"%d",&N);
	T=malloc(N*sizeof(transaction));
	Tval=malloc(N*sizeof(transaction));
	for(i=0;i<N;i++){
		T[i].date=getdate(fp);
		fscanf(fp,"%d %d",&(T[i].value),&(T[i].n));
		for(j=0;(j<k)&&(!isequal(Tval[j].date,T[i].date));j++);
		if(j==k){
            k++;
			Tval[j].date=ITEMsetNullD();
			Tval[j].n=0;
			Tval[j].value=0;
		}
        Tval[j].date=T[i].date;
		Tval[j].value+=(T[i].value*T[i].n);
		Tval[j].n+=T[i].n;
	}
	for(j=0;j<k;j++)
	{
		Q.date=Tval[j].date;
		TEMP=BSTsearch(quotes,Q.date);
		Q.n=Tval[j].n+TEMP.n;
		valuetot=(TEMP.Q)*(TEMP.n)+Tval[j].value;
		Q.Q=(float)((valuetot)/(float)(Q.n));
		if(TEMP.n!=0)
            quotes=BSTdelete(quotes,Q.date);
		quotes=BSTinsert(quotes,Q);
	}
	return quotes;
}

void printQuote(Tquote Q){
    printf("%f\n",Q.Q);
    return;
}

static void treeFree(linkBST h, linkBST z) {
    if (h == z)
   		 return;
  	treeFree(h->l, z);
  	treeFree(h->r, z);
  	freedate(h->nodeq.date);
  	free(h);
  	return;
}

void BSTfree(BSTP bst) {
    if (bst == NULL)
    	return;
  	treeFree(bst->root, bst->z);
  	free(bst->z);
  	free(bst);
  	return;
}

static Tquote searchR(linkBST h, timep k, linkBST z){
  	int cmp;
  	if (h == z)
    		return ITEMsetNull();
  	cmp = KEYcmp(k, h->nodeq.date);
  	if (cmp==0)
    		return h->nodeq;
 	if (cmp==-1)
    		return searchR(h->l, k, z);
  	else
    		return searchR(h->r, k, z);
}

static void searchMm(linkBST h, timep k, timep k1, linkBST z,Tquote* QMm)
{
    if ((h == z))
        return;
    searchMm(h->l,k,k1,z,QMm);
    if((((KEYcmp(h->nodeq.date,k)==0)||(KEYcmp(h->nodeq.date,k)==1))&&(((KEYcmp(h->nodeq.date,k1)==0))||((KEYcmp(h->nodeq.date,k1)==-1))))||(ITEMcheckNullD(k)))
    {
        if((QMm[0].Q)<(h->nodeq.Q))
        {
            QMm[0]=h->nodeq;
        }
        if((QMm[1].Q)>(h->nodeq.Q))
        {
            QMm[1]=h->nodeq;
        }
    }
    searchMm(h->r,k,k1,z,QMm);
    return;
}

Tquote BSTsearch(BSTP bst, timep k){
  	return searchR(bst->root, k, bst->z);
}

void BSTsearchMm(BSTP bst, timep k,timep k1,Tquote* QMm){
    QMm[0].Q=0.0;
    QMm[1].Q=FLT_MAX;
    QMm[0].date=ITEMsetNullD();
    QMm[1].date=ITEMsetNullD();
    searchMm(bst->root,k,k1,bst->z,QMm);
    return;
}

void BSTMmheight(linkBST head,linkBST z,int* MH,int* mH,int h){
    if ((head == z))
        return;
    if((head->l==z)&&(head->r==z)){
        if(h>*MH)
            *MH=h;
        if(h<*mH)
            *mH=h;
    }
    BSTMmheight(head->l,z,MH,mH,h+1);
    BSTMmheight(head->r,z,MH,mH,h+1);
    return;
}

int BSTunbheight(BSTP titolo,float RH){
    int MH=0,mH=1000000000,h=0;
    float MmR=0.0;
    BSTMmheight(titolo->root,titolo->z,&MH,&mH,h+1);
    MmR=((float)(MH/(float)mH));
    if(MmR>RH)
        return 1;
    return 0;
}

static linkBST balanceR(linkBST h, linkBST z) {
  int r;
  if (h == z)
    return z;
  r = (h->N+1)/2-1;
  h = partR(h, r);
  h->l = balanceR(h->l, z);
  h->r = balanceR(h->r, z);
  return h;
}

void BSTbalance(BSTP bst) {
    bst->root = balanceR(bst->root, bst->z);
}

