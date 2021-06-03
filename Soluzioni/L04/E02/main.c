#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    int freq;
}maj;

maj Rmajority(int *a,int i,int f)
{
    maj majsx,majdx;
    majsx.n=-1;
    majdx.n=-1;
    majsx.freq=0;
    majdx.freq=0;
    int half=((i+f)/2);
    int dim=(f-i)+1;
    int count;

    if(i==f)//terminazione (un unico elemento è maggioritario di sè stesso)
    {
        majsx.n=a[i];
        majsx.freq=1;
        return  majsx;
    }

    majsx=Rmajority(a,i,half);//divide O(1)
    majdx=Rmajority(a,half+1,f);
    //unione risultati O(n/2)
    if(((majsx.n)==(majdx.n))&&((majsx.n)!=(-1)))//O(1)
    {
        majsx.freq=majsx.freq+majdx.freq;
        if(majsx.freq>dim/2)   return majsx;
    }
    else if((majsx.n!=-1)||(majdx.n!=-1))
    {
        if(majsx.freq>majdx.freq)
        {
            for(count=half+1;count<=f;count++)//O(dim/2)
            {
                if(a[count]==majsx.n)   majsx.freq++;
            }
            if(majsx.freq>dim/2) return majsx;
        }
        if(majsx.freq<=majdx.freq)
        {
            for(count=i;count<=half;count++)//O(dim/2)
            {
                if(a[count]==majdx.n)   majdx.freq++;
            }
            if(majdx.freq>dim/2) return majdx;
        }
    }
    majsx.n=-1;
    majsx.freq=0;
    return majsx;
}/*
T(n)=n/2+2T(n/2)
T(n/2)=n/4+2T(n/4)
T(n/4)=n/8+2T(n/8)
...
T(n/2^i)=T(1)=1  se n=2^i
T(n)=n/2+2*n/4+4*n/8+... = (n/2)*log(n) --> O(nlogn)
se il vettore fosse di lunghezza n=2^i, in caso contrario lo considero arrotondato per dimensioni alla potenza di 2 successiva
*/

int majority(int *a, int N)
{
    maj n;
    n=Rmajority(a,0,N-1);
    return n.n;
}

int main()
{
    const int N=10;
    int V[N];
    int j;
    int M;
    printf("inserire i %d elementi del vettore\n",N);
    for(j=0;j<N;j++)
    {
        scanf("%d",&V[j]);
    }
    M=majority(V,N);
    printf("l'elemento maggioritario e %d",M);
    return 0;
}
