#include <stdio.h>
#include <math.h>

double polinomio(double);
double polinomio_a(double);
double polinomio_b(double);
double polinomio_c(double);
double polinomio_d(double);
double p1(double);

double fpoint(double, double, int, double (*func)(double));
double biseccion(double, double, double,int, double (*func)(double));

int main(){

	double p0=1;
	int n=20;
	double epsilon = 0.0001;
		printf("g_a(x) \t\t g_b(x) \t g_c(x) \t\t g_d(x) \n");
	for(int i=1;i<=11;i++){
		printf("%g \t",fpoint(p0,epsilon,i,polinomio_a));
		printf("%.8g \t",fpoint(p0,epsilon,i,polinomio_b));
		printf("%.6g \t\t",fpoint(p0,epsilon,i,polinomio_c));
		printf("%.8g \n",fpoint(p0,epsilon,i,polinomio_d));
	}
//	printf("%.8lf \n",fpoint(p0,epsilon,n,polinomio));

//	printf("%lf \n",fpoint(p0,epsilon,n,p1));
//	printf("%lf",p1(0));
	biseccion(0,1,epsilon,20,polinomio);

	return 0;
}

double fpoint(double p0, double epsilon, int n, double (*func)(double)){
	double p;
	int i=0;
	while(i<n){
		p=func(p0);
		if(fabs(p-p0)<epsilon){
			return p;
		}
		i++;
		p0=p;
	}
	return p;
}

double biseccion(double a, double b, double epsilon, int n, double (*func)(double)){
	double fa,fp,p;
	fa=func(a);
	int i=0;
	while(i<n){
		p=a+((b-a)/2);
		fp = func(p);
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
	return pow(x,4)+3*pow(x,2)-2;
}

double polinomio_a(double x){
	return sqrt((2-pow(x,4))/3);
}

double polinomio_b(double x){
	return sqrt(sqrt((2-(3.0*pow(x,2)))));
}

double polinomio_c(double x){
	return (2-pow(x,4))/(3*x);
}

double polinomio_d(double x){
	return cbrt((2-(3*pow(x,2)))/x);
}

double p1(double x){
	return pow(6-x,1/3.0);
}
