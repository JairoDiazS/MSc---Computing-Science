/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 5/EJ2*************/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tarea 5.h"

int main(){

	FILE *fpuntos = fopen("puntos.txt", "w+");

	int N=100; //Numero de nodos
	double **matrizA;
	double *vectorB;
	double *x;
	double temp=0;
	double epsilon=0.00001;

	//Resolvermos para el numero de nodos
	for(int i=3; i<=N; i++){

		//Generamos la matriz
		matrizA=gen_mat_possym(i);

		//Obtenemos el vector B
		vectorB=gen_vectorB(i);
//		for(int w=0; w<i; w++) printf("%g\n",vectorB[w]);

		//Resolvemos
		x=solve_cholesky(matrizA, vectorB, i);

		//Imprimimos el valor central
		if(i==4 || i%10==0) fprintf(fpuntos,"%d %g\n", i,x[i/2]);

		if(i>3 && abs(temp-x[i/2])<epsilon) exit(0);
		temp=x[i/2];

		//Liberando la memmoria
		free_mat(matrizA, i);
		free(vectorB);
		free(x);
	}

	printf("El algoritmo no converge despues de %d iteraciones.",N);

	fclose(fpuntos);
	//gnuplot
//	FILE *fp = popen("gnuplot -persist", "w");
//	fprintf(fp, "plot \"puntos.txt\" with points\n");
//	fclose(fp);

	return 0;
}
