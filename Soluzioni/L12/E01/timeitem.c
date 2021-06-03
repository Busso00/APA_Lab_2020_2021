#include "timeitem.h"
typedef struct time{
	int aaaa;
	int mm;
	int gg;
	int h;
	int m;
};

int islater(timep A,timep B){
	if((A->aaaa)>(B->aaaa)) return 1;
   	else if(((A->aaaa)==(B->aaaa))&&((A->mm)>(B->mm)))  return 1;
    else if((A->aaaa)<(B->aaaa)) return 0;
    else if(((A->mm)==(B->mm))&&((A->gg)>(B->gg)))  return 1;
    return 0;
}

int isequal(timep A,timep B){
	if(((A->aaaa==B->aaaa)&&(A->mm==B->mm))&&(A->gg==B->gg))
		return 1;
	return 0;
}

timep getdate(FILE* fp){
	timep date=malloc(sizeof(*date));
	fscanf(fp,"%d/%d/%d %d:%d",&(date->aaaa),&(date->mm),&(date->gg),&(date->h),&(date->m));
	return date;
}

int KEYcmp(timep A,timep B){
	if(islater(A,B))
		return 1;
	if(isequal(A,B))
		return 0;
	return -1;
}

timep ITEMsetNullD(){
	timep date=malloc(sizeof(*date));
	date->aaaa=0;
	date->mm=0;
	date->gg=0;
	date->h=0;
	date->m=0;
	return date;
}

int ITEMcheckNullD(timep date){
    if(date->gg==0)
        return 1;
    return 0;
}

void freedate(timep date){
    free(date);
    return;
}
