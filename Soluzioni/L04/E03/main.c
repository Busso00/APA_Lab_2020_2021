#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *cercaRegexp(char* src,char* regexp)
{
    int slsrc=strlen(src);
    int slregexp=strlen(regexp);
    int pos=0,i,j,interrupt;
    while(pos<slsrc)
    {
        interrupt=0;
        j=0;
        i=pos;
        while((j<slregexp)&&(!interrupt))
        {
            if(regexp[j]=='[')
            {
                j++;
                if(regexp[j]=='^')
                {
                    while((regexp[j]!=']')&&(!interrupt))
                    {
                        j++;
                        if(regexp[j]==src[i])   interrupt=1;
                    }
                }
                else
                {
                    interrupt=1;
                    while(regexp[j]!=']')
                    {
                        if(regexp[j]==src[i])   interrupt=0;
                        j++;
                    }
                }
            }
            if(regexp[j]=='\\')
            {
                j++;
                if(regexp[j]=='a')
                {
                    if(islower(src[i])==0)  interrupt=1;
                }
                if(regexp[j]=='A')
                {
                    if(isupper(src[i])==0)  interrupt=1;
                }
            }
            if((src[i]!=regexp[j])&&(regexp[j]!='.')&&(regexp[j]!=']')&&(regexp[j-1]!='\\'))    interrupt=1;
            j++;
            i++;
        }
        if(interrupt==0)   return &src[pos];
        pos++;
    }
    return NULL;
}

int main()
{
    char Src[200],regexp[200];
    char* isthere;
    printf("scrivi la stringa contenente solo caratteri alfabetici\n");
    scanf("%s",Src);
    printf("scrivi l'espressione regolare da cercare\n");
    scanf("%s",regexp);
    isthere=cercaRegexp(Src,regexp);
    printf("inizio: %s\n",isthere);
    return 0;
}
