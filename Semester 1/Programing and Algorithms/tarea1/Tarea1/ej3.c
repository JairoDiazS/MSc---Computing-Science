/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ2*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>

int pot(int, int);

int main() {
    double n, r=0, j=0;

    printf("Este programa recoge n enteros y los imprime de forma inversa.\n");
    printf("Ingrese la cantidad de enteros que desea agregar: ");
    scanf("%lf", &n);
    printf("\nIngrese los numeros de uno en uno: ");

    for(int i=0; i<n; i++){
		double k;
		int b;
		scanf("%lf", &k);
		b=k*pot(10, i);
		j += k*pot(10, n-1 - i);
		r += b;
    }
    printf("Su numero es: %.0lf\n", j);
    printf("El numero invertido es: %.0lf", r);

    if(j==r) printf("\nSu numero es palindromo");
	else printf("\nSu numero no es palindromo");

    return 0;
}

int pot (int b, int p){
	int w=1;
	for(int i=0;i<p;i++) w*=b;
	return w;
}
