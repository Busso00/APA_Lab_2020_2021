#ifndef PGLIST_H_INCLUDED
#define PGLIST_H_INCLUDED
#include "pg.h"

typedef struct pg* tabPgP;

//inizializza e libera
tabPgP pgTinit();
void liberaP(tabPgP tabPg);

//lettura da file (nomefile acquisito nella funzione)
int aggiungiTabpg(tabPgP tabPg);
//aggiunge solo un personaggio da stdin
int aggiungipg(tabPgP tabPg);
//output presonaggio con dato codice (codice acquisito all'interno della funzione)
void printPg(tabPgP tabPg,tabInvP tabInv);
//caratteristiche* searchcod(tabPgP tabPg);
//ricerca per codice ritorna 1 se trova 0 altrimenti(la ricerca con spostamento lungo gli indirizzi dei personaggi è una funzione interna del .c)
int searchcod(tabPgP tabPg);
//cancellazione personaggio con ritorno del numero di personaggi restanti
int listDelrKey(tabPgP tabPg);
//cerca il personaggio in lista e chiama modEqL1
int modeq(tabPgP tabPg,tabInvP tabInv);
#endif // PGLIST_H_INCLUDED
