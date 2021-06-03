#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "titoli.h"
typedef enum{
    getfile,search,searchval,sMmint,sMm,balance,fine,notfound
}comando;

comando getcmd(){
	char cmdT[7][MAXL]={"getfile","searcht","searchval","sMmint","sMm","balance","fine"};
	char temp[MAXL];
	comando cmd;
	printf("scrivi il comando tra getfile,searcht,searchval,sMmint,sMm,balance,fine\n");
	scanf("%s",temp);
	for(cmd=getfile;cmd<notfound;cmd++)
		if(strcmp(temp,cmdT[cmd])==0)
			return cmd;
	return cmd;
}

int main(){
	FILE* fp;
	tTab T;
	link titolo;
	timep k,k1;
	Tquote Q,QMm[2];
	int f=0,fn=0;
	float RH;
	char nomefile[MAXL],cod[MAXL];
	comando cmd=getfile;
	T=Tinit();
	while(cmd!=fine)
	{
		cmd=getcmd();
		switch(cmd){
			case getfile:
				printf("scrivi il nome del file\n");
				scanf("%s",nomefile);
				fp=fopen(nomefile,"r");
				if(fp==NULL){
                    printf("file non trovato\n");
                    return 0;
				}
				if(f!=0){
                    printf("vuole tenere memorizzati i dati? 1 per tenere 0 per togliere\n");
                    scanf("%d",&fn);
                    if(fn==0){
                        freeT(T);
                        T=Tinit();
                    }
				}
				T=getT(T,fp);
				f=1;
				break;
			case search:
				printf("scrivi il nome del titolo cercato\n");
				scanf("%s",cod);
				titolo=searcht(T,cod);
				if(titolo!=NULL)
					printf("titolo trovato\n");
                break;
			case searchval:
				printf("scrivi il nome del titolo cercato\n");
				scanf("%s",cod);
				titolo=searcht(T,cod);
				if(titolo!=NULL){
                    printf("scrivi la data della quale vedere la quotazione\n");
                    k=getdate(stdin);
                    Q=BSTsearchL2(titolo,k);
                    if(!ITEMcheckNull(Q)){
                        printf("il valore nella data specificata e\n");
                        printQuote(Q);
                    }
				}
				break;
			case sMmint:
                printf("scrivi il nome del titolo cercato\n");
				scanf("%s",cod);
				titolo=searcht(T,cod);
				if(titolo!=NULL){
				    printf("scrivi l'intervallo nel quale vedere la quotazione max e min\n");
                    k=getdate(stdin);
                    k1=getdate(stdin);
                    if(!islater(k,k1)){
                        BSTsearchMmL2(titolo,k,k1,QMm);
                        if(!ITEMcheckNull(QMm[0])){
                            printf("il max e:\n");
                            printQuote(QMm[0]);
                            printf("il min e:\n");
                            printQuote(QMm[1]);
                        }
                    }
                    else
                        printf("intervallo non valido\n");
				}
				break;
			case sMm:
                printf("scrivi il nome del titolo cercato\n");
				scanf("%s",cod);
				titolo=searcht(T,cod);
				if(titolo!=NULL){
                    k=ITEMsetNullD();
                    k1=ITEMsetNullD();
                    BSTsearchMmL2(titolo,k,k1,QMm);
                    if(!ITEMcheckNull(QMm[0])){
                        printf("il max e:\n");
                        printQuote(QMm[0]);
                        printf("il min e:\n");
                        printQuote(QMm[1]);
                    }
				}
                break;
			case balance:
                printf("scrivi il nome del titolo cercato\n");
				scanf("%s",cod);
				titolo=searcht(T,cod);
				if(titolo!=NULL){
				    printf("quale dev essrere il rapporto fra il cammino più lungo e quello più corto?\n");
                    scanf("%f",&RH);
				    if(BSTunbheightL2(titolo,RH))
                        BSTbalanceL2(titolo);
				}
                break;
		}
	}
	freeT(T);
}
