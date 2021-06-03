#include <stdio.h>
#include <stdlib.h>
#include <float.h>
int big_little(void *a)
{
    unsigned char* part;
    part=a;
    unsigned char byte[1];
    int i;
    byte[0]=*part;
    if (byte[0]==0) return 1;
    else return 0;
}

int cto2(int r[128],int c,int j)
{
    int k=0;
    int t=256;
    while(k<8)
    {
        k++;
        t=t/2;
        if(j>=t)
        {
            j=j-t;
            r[c]=1;
            c++;
        }
        else
        {
            r[c]=0;
            c++;
        }
    }
    return c;
}

void stampaCodifica (void *p, int size, int bigEndian)
{
    unsigned char* puc;
    puc=p;
    int i,j=0,c=0;
    int r[128];
    unsigned char V[16];
    if(bigEndian)
    {
        for(i=0;i<size;i++)
        {
            V[i]=*(puc+i);
            j=(int)V[i];
            c=cto2(r,c,j);
        }
    }
    else
    {
        for(i=(size-1);i>=0;i--)
        {
            V[i]=*(puc+i);
            j=(int)V[i];
            c=cto2(r,c,j);
        }
    }
    if(size<=8)
    {
        for(i=0;i<size*8;i++)
        {
            printf("%d",r[i]);
            if(i==0)    printf(" ");
            if((size==4)&&(i==8))   printf(" ");
            if((size==8)&&(i==11))  printf(" ");
        }
    }
    else
    {
        for(i=48;i<size*8;i++)//per codifica su 80bit e strutture di 16byte
        {
            printf("%d",r[i]);
            if(i==48)   printf(" ");
            if(i==48+15) printf(" ");
        }
    }

    printf("\n");
}

int main()
{
    float af;
    double ad;
    __float80 ald=2000L;
    int a=1;
    char number[20];
    int size;
    int bigEndian=0;

    bigEndian=big_little(&a);

    size=sizeof(af);
    printf("la dimensione del tipo float e di: %d\n",size);
    size=sizeof(ad);
    printf("la dimensione del tipo double e di: %d\n",size);
    size=sizeof(ald);
    printf("la dimensione del tipo long double e di: %d\n",size);

    printf("scrivi un numero decimale con virgola ed eventuale esponente\n");
    scanf("%s",&number);
    sscanf(number,"%e",&af);
    sscanf(number,"%le",&ad);
    sscanf(number,"%Le",&ald);//non funziona con questo compilatore--->
    ald=(long double)ad;

    stampaCodifica(&af,sizeof(af),bigEndian);

    stampaCodifica(&ad,sizeof(ad),bigEndian);

    stampaCodifica(&ald,sizeof(ald),bigEndian);

    return 0;
}
