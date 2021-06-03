#define DBG 1
#if DBG
#define maxl 50
#define NINV 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pgList.h"

typedef enum{
    c_addpgT,c_addeq,c_addpg,c_delpg,c_modeq,c_searchpg,c_printpg,c_searchobj,c_printobj,c_fine,c_notfound
}comando_c;

comando_c getcommand()
{
    comando_c i;
    char temp[20];
    char cmdtab[c_notfound][20]={"newPgT","newInvT","newPg","delPg","modEq","searchPg","printPg","searchObj","printObj","fine",""};
    printf("per caricare una tabella di personaggi digitare: newPgT\n");
    printf("per caricare una tabella di oggetti digitare: newInvT\n");
    printf("per caricare un personaggio digitare: newPg\n");
    printf("per eliminare un personaggio digitare: delPg\n");
    printf("per aggiungere/togliere oggetti all'equipaggiamento del personaggio digitare: modEq\n");
    printf("per sapere se un personaggio e in lista digitare: searchPg\n");
    printf("per sapere se un oggetto e in lista digitare: searchObj\n");
    printf("per stampare le caratteristiche di un personaggio digitare: printPg\n");
    printf("per stampare le caratteristiche di un oggetto digitare: printObj\n");

    printf("per terminare digitare: fine\n");
    fgets(temp,20,stdin);
    sscanf(temp,"%s ",temp);
    for(i=c_addpgT;i<c_notfound&&(strcmp(temp,cmdtab[i])!=0);i++);
    return i;
}

int main()
{
    tabPgP tabPg;
    tabInvP tabInv;
    comando_c codcmd=c_addpgT;
    tabPg=pgTinit();
    tabInv=invTinit();
    int f1=0,f2=0;
    while (codcmd!=c_fine)
    {
        codcmd=getcommand();
        switch(codcmd)
        {
            case c_addpgT:
                aggiungiTabpg(tabPg);
                f1=1;
                break;
            case c_addeq:
                aggiungiTabeq(tabInv);
                f2=1;
                break;
            case c_addpg:
                aggiungipg(tabPg);
                f1=1;
                break;
            case c_delpg:
                if(listDelrKey(tabPg)==0)
                    f1=0;
                break;
            case c_modeq:
                modeq(tabPg,tabInv);
                break;
            case c_searchpg:
                searchcod(tabPg);
                break;
            case c_printpg:
                printPg(tabPg,tabInv);
                break;
            case c_searchobj:
                sObjL2(tabInv);
                break;
            case c_printobj:
                pObjL1(tabInv,-1);
                break;
            case c_fine:
                break;
            case c_notfound:
                printf("comando non trovato\n");
                break;
        }
    }
    if(f1)
        liberaP(tabPg);
    free(tabPg);
    if(f2)
        liberaI(tabInv);
    free(tabInv);
    return 0;
}
#endif // DBG
