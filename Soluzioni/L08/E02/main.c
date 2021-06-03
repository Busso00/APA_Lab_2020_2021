#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define npietre 4

int componicollana(int pos,int* sol,int k,int* occ,int* found,int max_rip,int rip,int n_za,int n_sm,int* val,int val_a,int *max_val,int* Mval,int count)
{
    int i,currrip;

    if(pos>=k)
    {
        if(val_a>*max_val)
        {
            for (i=0; i<k; i++)
            {
                Mval[i]=sol[i];
            }
            *max_val=val_a;
            *found=1;
        }
        return count+1;
    }
    currrip=rip;
    for (i=1;i<(npietre+1);i++)
    {
        rip=currrip;
        if(occ[i-1]<=0)   continue;
        if(pos>=1)
        {
            switch(sol[pos-1])
            {
                case 1:
                if((i==3)||(i==4))   continue;
                if(i==sol[pos-1]) rip++;
                else rip=0;
                break;

                case 2:
                if((i==1)||(i==2))   continue;
                rip=0;
                break;

                case 3:
                if((i==3)||(i==4))   continue;
                rip=0;
                break;

                case 4:
                if((i==1)||(i==2))   continue;
                if(i==sol[pos-1]) rip++;
                else rip=0;
                break;
            }
        }
        if(i==1)    n_za++;
        if(i==4)    n_sm++;
        val_a+=val[i-1];
        occ[i-1]--;
        if(n_za>n_sm)
        {
            occ[i-1]++;
            val_a-=val[i-1];
            if(i==4)    n_sm--;
            if(i==1)    n_za--;
            continue;
        }
        if(rip>=max_rip)  //il >= serve poichè rip è numero di occorrenze consecutive nel vettore sol diminuito di 1
        {
            occ[i-1]++;
            val_a-=val[i-1];
            if(i==4)    n_sm--;
            if(i==1)    n_za--;
            continue;
        }
        sol[pos] = i;
        count=componicollana(pos+1, sol, k, occ, found, max_rip, rip, n_za, n_sm, val, val_a, max_val, Mval,count);

        occ[i-1]++;
        val_a-=val[i-1];
        if(i==4)    n_sm--;
        if(i==1)    n_za--;
    }

    return count;
}



int main()
{
    int Vocc[npietre]={0};
    int Val[npietre]={0};
    FILE *fp;

    int dim=0,lenght=0;
    int* sol;
    int* Mval;
    int i,j;
    int found,count=0;
    int max_rip;
    int max_val=0;
    int nset;
    char table[npietre][2]={"z","r","t","s"};

    char nomefile[50];
    printf("come si chiama il file?\n");
    scanf("%s",nomefile);

    fp=fopen(nomefile,"r");
    if(fp==NULL)
    {
        printf("file non trovato\n");
        return 0;
    }

    fscanf(fp,"%d",&nset);
    for(j=1;j<=nset;j++)
    {

        //printf("scrivere il numero di zaffiri\n");
        fscanf(fp,"%d ",&Vocc[0]);
        //printf("scrivere il numero di rubini\n");
        fscanf(fp,"%d ",&Vocc[1]);
        //printf("scrivere il numero di topazi\n");
        fscanf(fp,"%d ",&Vocc[2]);
        //printf("scrivere il numero di smeraldi\n");
        fscanf(fp,"%d ",&Vocc[3]);
        //printf("scrivere il valore di zaffiri\n");
        fscanf(fp,"%d ",&Val[0]);
        //printf("scrivere il valore di rubini\n");
        fscanf(fp,"%d ",&Val[1]);
        //printf("scrivere il valore di topazi\n");
        fscanf(fp,"%d ",&Val[2]);
        //printf("scrivere il valore di smeraldi\n");
        fscanf(fp,"%d ",&Val[3]);
        //printf("scrivere il numero massimo di pietre uguali consecutive:\n");
        fscanf(fp,"%d",&max_rip);

        dim=0;
        count=0;
        for(i=0;i<npietre;i++)  dim=dim+Vocc[i];
        sol=(int*)calloc(dim,sizeof(int));
        Mval=(int*)calloc(dim,sizeof(int));

        max_val=0;
        for(i=dim;i>=1;i--)
        {
            found=0;
            count=componicollana(0,sol,i,Vocc,&found,max_rip,0,0,0,Val,0,&max_val,Mval,count);
            if(found)
                lenght=i;
        }
        printf("le soluzioni esplorate sono %d",count);
        printf("set n: %d\n",j);
        printf("tot gemme: %d ",dim);
        printf("la lunghezza è %d\n",lenght);
        printf("il valore è %d\n",max_val);
        printf("composizione: ");
        for(i=0;i<lenght;i++)   printf("%s ",table[Mval[i]-1]);
        printf("\n");

        free(sol);
        free(Mval);
    }
    fclose(fp);
    return 0;
}
