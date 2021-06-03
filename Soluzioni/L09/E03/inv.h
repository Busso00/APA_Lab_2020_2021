#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED
#include "gestioneio.h"
typedef struct{
    inv_t* vettInv;
    int nInv;
}tabInv_t;

inv_t Eqsetvoid();
void invTinit(tabInv_t** tabInv);
int aggiungiTabeq(tabInv_t* tabInv);
int sobj(inv_t* Inv,int n,int f);
int searchobj(tabInv_t* tabInv);
void pObj(inv_t* vettInv,int f,int n);
void printObj(tabInv_t* tabInv);
void liberaI(tabInv_t* tabInv);
#endif // INV_H_INCLUDED
