#include "Graph.h"

typedef enum{
    printEdge,adjPairsM,adjPairsL,buildLadj,End,notfound
}command;

command leggicomando()
{
    command cmd;
    char cmdTable[End][MAXC]={"stampaArchi","3adiacentiM","3adiacentiL","lista","fine"};
    char temp[MAXC];
    printf("scrivi un comando tra: stampaArchi,3adiacentiM,3adiacentiL,lista,fine\n");
    fgets(temp,MAXC,stdin);
    sscanf(temp,"%s",temp);
    for(cmd=printEdge;cmd<notfound;cmd++)
        if(strcmp(temp,cmdTable[cmd])==0)
            return cmd;
    return cmd;
}

int main(int argv,char** argc) {
    FILE *finp;
    Graph G;
    command cmd;
    if((finp=fopen(argc[1],"r"))==NULL){
        printf("errore nell apertura file\n");
        return 0;
    }
    G=GRAPHload(finp);
    while((cmd=leggicomando())<notfound)
    {
        if(cmd==buildLadj)
            GRAPHbuildlist(G);
        else if(cmd==printEdge)
            GRAPHstore(G,stdout);
        else if(cmd==adjPairsM)
            if(GRAPHadjPairs(G,1))
                printf("sono adiacenti a coppie\n");
            else
                printf("non sono adiacenti a coppie\n");
        else if(cmd==adjPairsL)
            if(GRAPHadjPairs(G,0))
                printf("sono adiacenti a coppie\n");
            else
                printf("non sono adiacenti a coppie\n");
    }
    GRAPHfree(G);
    return 0;
}
