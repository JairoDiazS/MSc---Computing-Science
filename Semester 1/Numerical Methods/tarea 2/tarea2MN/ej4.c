#include <stdio.h>
#include <math.h>

double biseccion(double a, double b, double epsilon, int n, double (*func)(double)){
	double fa,fp,p;
	fa=func(a);
	int i=0;
	while(i<n){
		p=a+((b-a)/2);
		fp = func(p);
		if(fp==0 || ((b-a)/2)<epsilon){
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
//	printf("El metodo fallo tras el numero de iteraciones.");
	return p;
}

double newton(double p0, double epsilon, int n, double (*func)(double),double (*der)(double)){

	int i=0;
	double p;
	while(i<n){
		p = (p0-(func(p0)/der(p0)));
		if(fabs(p-p0)<epsilon) {
			return p;
		}
		i++;
		p0=p;
	}
//	printf("El metodo fallo.");
	return p;
}

double secante(double p0, double p1, double epsilon, int n, double (*func)(double)){

	int i=1;
	double p;
	double q0 = func(p0);
	double q1 = func(p1);
	while(i<n){
		p = p1 - q1*((p1-p0)/(q1-q0));
		if(fabs(p-p1)<epsilon) {
			return p;
		}
		i++;
		p0=p1;
		q0=q1;
		p1=p;
		q1=func(p);
	}
//	printf("El metodo fallo");
	return p;
}

double rfalsi(double p0, double p1, double epsilon, int n, double (*func)(double)){

	int i=1;
	double p,q;
	double q0 = func(p0);
	double q1 = func(p1);
	while(i<n){
		p = p1 - q1*((p1-p0)/(q1-q0));
		if(fabs(p-p1)<epsilon){
			return p;
		}
		i++;
		q = func(p);
		if((q*q1)<0){
			p0=p1;
			q0=q1;
		}
		p1=p;
		q1=q;
	}
//	printf("El metodo fallo.");
	return p;
}

double polinomio(double x){
	return ((1000000*exp(x))+((435000/x)*(exp(x)-1))-1564000);
}

double derivada(double x){
	return ((((1000000*pow(x,2))+(435000*x)-435000)*exp(x))/(pow(x,2)));
}

int main(){
	//Parametros generales
	double epsilon = 0.0001;
	//parametros biseccion
	double p0=0.1;
	double p1=0.2;
	printf("iter \t biseccion\tnewton\t\tsecante\t\tfalsi \n");
	for(int i=1;i<=15;i++){
		printf("%d \t %.8f \t",i,biseccion(p0,p1,epsilon,i,polinomio));
		printf("%.8g \t",newton(p0,epsilon,i,polinomio,derivada));
		printf("%.8g \t",secante(p0,p1,epsilon,i,polinomio));
		printf("%.8g \n",rfalsi(p0,p1,epsilon,i,polinomio));
	}
	return 0;
}
