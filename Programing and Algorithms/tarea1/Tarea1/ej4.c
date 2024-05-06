/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ4*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <math.h>

double coseno(double, int, double);

int main(){
	double x, epsilon;
	int n;
	printf("Este programa obtiene una aproximacion de coseno ");
	printf("Ingrese el valor de x para calcular su coseno y ");
	printf("ademas un valor de iteraciones y por ultimo valor de aproximacion, separados por espacio: ");
	scanf("%lf %d %lf", &x, &n, &epsilon);
	printf("El resultado es %lf", coseno(x, n, epsilon));

	return 0;
}

double coseno(double x, int n, double epsilon){
	double r=1,x0=1,r0=0;
	double delta=1000;
	int i0=1;
	int i=1;
	while(i<=n && delta>=epsilon){
		i0*=(2*i)*(2*i-1);
		x0*=(-1)*pow(x,2);
		r+=(x0)/(i0);
		delta =fabs(r-r0);
		r0=r;
		i++;
	}
	return r;
}

