#ifndef INVARRAY_H_INCLUDED
#define INVARRAY_H_INCLUDED
#include "inv.h"

typedef struct tabinv* tabInvP;//=invArray_t

//inizializza e libera
tabInvP invTinit();
void liberaI(tabInvP tabInv);

//legge da file gli oggettti (nomefile acquisito all'interno della funzione)
int aggiungiTabeq(tabInvP tabInv);
//stampa l'oggetto all'indice f se si passa come indice -1 stampa l'oggetto con il nome cercato
void pObjL1(tabInvP tabInv,int f);
//ricerca l'oggetto con un dato nome
int sObjL2(tabInvP tabInv);

//ritorna l'oggetto all'indice f per addizione stat
inv_t* sObjL1(tabInvP tabInv,int f);


#endif // INVARRAY_H_INCLUDED
