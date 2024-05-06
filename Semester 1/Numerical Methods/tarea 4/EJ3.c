/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ3*************/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "tarea4.h"

int main(){

	//Definimos el tamanio de la amtriz
	int sz=4;
	//Obtenemos la matriz y su vector conforme a los nombre obtenidos anteriormente
	double **matriz=gen_mat_possym(sz);
	printf("La matriz es:\n");
	imprimirMatriz(matriz,sz,sz);

	//Obtenemos la factorizacion
	printf("La factorizacion de la matriz es:\n");
	double **LU=fact_Cholesky(matriz,sz);
	imprimirMatriz(LU, sz, sz);

	//Liberando la memoria
	free_mat(matriz, sz);
	free_mat(LU, sz);
	return 0;
}
