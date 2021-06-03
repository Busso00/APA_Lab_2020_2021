#ifndef EQUIPARRAY_H_INCLUDED
#define EQUIPARRAY_H_INCLUDED
#include "invArray.h"

typedef struct eq* Eq;

//int sizeEquip();
//inizializza e libera
Eq Eqinit();
void equipArray_free(Eq equip);


int equipArray_inUse(Eq equipArray);
//modifica equipaggiamento
int modeqL0(Eq x,tabInvP tabInv);
//stampa l'equipaggiamento *res serve a immagazzinare le statistiche originali del personaggio in modo da addizionare ad esse i bonus
void printEq(Eq x,tabInvP tabInv);
//ritorna l'indice nell'inventario dell'oggetto cercato (di indice ind) -1 se non c'è
int equipArray_getEquipByIndex(Eq equipArray, int index);
#endif // EQUIPARRAY_H_INCLUDED
