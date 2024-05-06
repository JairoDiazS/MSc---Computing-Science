#include <stdio.h>
#include <math.h>

double biseccion(double, double, double, int);
double polinomio(double);

int main(){
	double a=1.55, b=1.75, epsilon=0.0001;
	double p = biseccion(a,b,epsilon,20);
	return 0;
}

double biseccion(double a, double b, double epsilon, int n){
	double fa,fp,p;
	fa=polinomio(a);
	int i=0;
	while(i<n){
		p=a+((b-a)/2);
		fp = polinomio(p);
		if(fp==0 || ((b-a)/2)<epsilon){
			printf("%lf \t %d",p,i);
			return p;
		}
		i++;
		if(fa*fp>0){
			a=p;
			fa=fp;
		} else {
			b=p;
		}
	}
	printf("El metodo fallo tras el numero de iteraciones.");
	return p;
}

double polinomio(double x){

	return (pow(x,3)+x-6);
}
