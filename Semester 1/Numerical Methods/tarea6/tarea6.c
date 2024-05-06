/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 6/Cabecera**********/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include "tarea6.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Subrutina para el metodo de Jacobi
double *jacobi(double **matriz, double *vector, double *x0, int sz, double TOL, int N){
    //declaramos el espacio para la solucion
    double *x = (double *)malloc(sz * sizeof(double));

    double sum;

    for(int k=0; k<N; k++){
        for(int i=0; i<sz; i++){
            sum=0;
            for(int j=0; j<sz; j++){
                if(j!=i) sum+=matriz[i][j]*x0[j];
            }
            x[i]=(1/matriz[i][i])*(vector[i]-sum);
        }
        if(norm_vec(rest_vec(x, x0, sz), sz)<TOL){
			printf("El metodo converge tras %d iteraciones.\n", k);
			return x;
		} 
        for(int n=0; n<sz; n++) x0[n]=x[n];
    }
    printf("Despues de %d iteraciones el metodo no converge.", N);
    return x;
}

//Subrutina para el metodo de Gauss - Seidel
double *gauss_seidel(double **matriz, double *vector, double *x0, int sz, double TOL, int N){
    //declaramos el espacio para la solucion
    double *x = (double *)malloc(sz * sizeof(double));

    double sum;

    for(int k=0; k<N; k++){
        for(int i=0; i<sz; i++){
            sum=0;
            for(int j=0; j<i; j++) sum+=matriz[i][j]*x[j];
			for(int j=i+1; j<sz; j++) sum+=matriz[i][j]*x0[j];
            x[i]=(1/matriz[i][i])*(vector[i]-sum);
        }
        if(norm_vec(rest_vec(x, x0, sz), sz)<TOL){
			printf("El metodo converge tras %d iteraciones.\n", k);
			return x;
		} 
        for(int n=0; n<sz; n++) x0[n]=x[n];
    }
    printf("Despues de %d iteraciones el metodo no converge.", N);
    return x;
}

//Subrutina para leer una matriz desde un archivo
double **leerMatriz(char *nFile){

	//Abrir archivo en modo lectura
	FILE *file = fopen(nFile, "r");

	//verificar que el archivo se abrio correctamente
	if(file==NULL) return NULL;

	//Se define el tamanio de la matriz
	int nCols, nRows;
	fscanf(file, "%d %d", &nRows, &nCols);

	//Reservamos memoria para la matriz
	double **matriz = (double **)malloc(nRows * sizeof(double *));
	for(int i=0; i<nRows; i++){
		matriz[i]=(double *)malloc(nCols * sizeof(double));
	}

	int i;
	//Rellenando la matriz
	for(i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			fscanf(file, "%lf",&matriz[i][j]);
		}
	}

	fclose(file);

	return matriz;
}

//Subrutina apra calcular la norma de un vector
double norm_vec(double *vector, int sz){
	//Reservamos espacio
	double temp=0;
	for(int i=0; i<sz; i++){
		temp+=vector[i]*vector[i];
	}
	return sqrt(temp);
}

//Subrutina para restar 2 vectores
double *rest_vec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++) x[i]=v1[i]-v2[i];
	return x;
}

//Subrutina para multiplicar una matriz por un vector
double *mult_matxvec(double **matriz, double *vector, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));

	double temp=0;
	for(int i=0; i<sz; i++){
		temp=0;
		for(int j=0; j<sz; j++){
			temp+=matriz[i][j]*vector[j];
		}
		x[i]=temp;
	}
	return x;
}

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}

//Subrutina para imprimir una matriz
void imprimirMatriz(double **matriz, int nRows, int nCols){
	if(nRows>10) nRows=10;
	if(nCols>10) nCols=10;
	if(nCols >10 || nRows>10) printf("Dado el tamanio, solo se juestra las primeras 10 filas/columnas.\n");
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			printf("%g\t",matriz[i][j]);
		}
		printf("\n");
	}
}