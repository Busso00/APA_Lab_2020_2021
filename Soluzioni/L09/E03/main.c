#define DBG 1
#if DBG

#include "pg.h"

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
    tabPg_t* tabPg;
    tabInv_t* tabInv;
    comando_c codcmd=c_addpgT;

    pgTinit(&tabPg);
    invTinit(&tabInv);

    while (codcmd!=c_fine)
    {
        codcmd=getcommand();
        switch(codcmd)
        {
            case c_addpgT:
                aggiungiTabpg(tabPg);
                break;
            case c_addeq:
                aggiungiTabeq(tabInv);
                break;
            case c_addpg:
                aggiungipg(tabPg);
                break;
            case c_delpg:
                elimpg(tabPg);
                break;
            case c_modeq:
                modeq(tabPg,tabInv);
                break;
            case c_searchpg:
                searchcod(tabPg);
                break;
            case c_printpg:
                printPg(tabPg);
                break;
            case c_searchobj:
                searchobj(tabInv);
                break;
            case c_printobj:
                printObj(tabInv);
                break;
            case c_fine:
                break;
            case c_notfound:
                printf("comando non trovato\n");
                break;
        }
    }
    liberaP(tabPg);
    free(tabPg);
    liberaI(tabInv);
    free(tabInv);
    return 0;
}
#endif // DBG
