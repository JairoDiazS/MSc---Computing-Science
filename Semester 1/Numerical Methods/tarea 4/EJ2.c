/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ2*************/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "tarea4.h"

int main(){

	//Definicion de los nombres a trabajar
//	char nFile_Mat[]="BigMatrix.txt"; //Nombre del archivo de la matriz
//	char nFile_Vec[]="BigVector.txt"; //Nombre dek archivo del vector

	char nFile_Mat[]="SmallMatrix.txt"; //Nombre del archivo de la matriz
	char nFile_Vec[]="SmallVector.txt"; //Nombre del archivo del vector

	//Obtencion del tamanio del sistema
	FILE * mat_file;
	mat_file = fopen(nFile_Mat, "r");
	if(mat_file==NULL) printf("Error al abrir archivo\n");
	int sz; //Solo se lee un valor, ya que el vector, tiene este tamanio y la matriz es cuadrada
	if(fscanf(mat_file, "%d %d", &sz, &sz)<1) printf("Error de lectura\n");
	fclose(mat_file);

	//Obtenemos la matriz y su vector conforme a los nombre obtenidos anteriormente
	double **matriz=leerMatriz(nFile_Mat);
	double **vect=leerMatriz(nFile_Vec);
	printf("La matriz es:\n");
	imprimirMatriz(matriz,sz,sz);
	printf("El vector es:\n");
	imprimirMatriz(vect,sz,1);

	//Obtenemos la solucion del sistema
	double *x=solver_lu(matriz,vect, sz, 0);
	printf("La solucion al sistema es:\n");
	for(int i=0; i<sz; i++) printf("%g\n",x[i]);

	//obtenemos el resultado de la resta para saber si se aproxima a 0
	double *cero = rest_vec(mult_matxvec(matriz, x, sz),vect,sz);
	printf("El resultadod e la resta es:\n");
	for(int i=0; i<sz; i++) printf("%g\n",cero[i]);

	//Liberando la memoria
	free_mat(matriz, sz);
	free(x);
	free(cero);
	free(vect);
	return 0;
}


