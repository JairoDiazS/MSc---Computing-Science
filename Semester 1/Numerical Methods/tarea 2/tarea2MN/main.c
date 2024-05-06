#include <stdio.h>
#include <math.h>

double euler(int);

int main()
{
	double e,e_abs,e_rel;
	double e_real=exp(1);
    printf("k \t e(k) \t \t e \t \t e_abs \t \t e_rel \n");
    for(int i=1;i<=20;i++){
		e=euler(i);
		e_abs=fabs(e-e_real);
		e_rel=e_abs/e_real;
		printf("%d \t %.8lf \t %.8lf \t %.8lf \t %.8lf \n",i,e,e_real,e_abs,e_rel);
    }
    return 0;
}

double euler(int k){
	double n=pow(10,k);
	return pow((1+(1/n)),n);
}
