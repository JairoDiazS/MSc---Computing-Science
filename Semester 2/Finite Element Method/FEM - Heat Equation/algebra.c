/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/***************Algrebra***************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de algebra con programacion dinamica*/

#include "algebra.h"
#include "tools.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Función para calcular la inversa de una matriz
double **inverseMatrix(double **inversa, double **matriz_org, int sz){
    //Se crea una copia de la matriz para no modificar la original
    double **matriz = (double **)malloc(sz*sizeof(double *));
    for(int i=0; i<sz; i++){
        matriz[i] = (double *)calloc(sz, sizeof(double));
        for(int j=0; j<sz; j++){
            matriz[i][j] = matriz_org[i][j];
        }
    }
    
    // Inicializamos la matriz inversa como la matriz identidad
    for(int i=0; i<sz; i++) inversa[i][i] = 1.0;

    // Comenzar con el proceso de eliminacion
    for (int i = 0; i < sz; i++) {
        // Encontrar el pivote parcial
        double maxPivote = fabs(matriz[i][i]);
        int filaPivote = i;

        for (int k = i + 1; k < sz; k++) {
            if (fabs(matriz[k][i]) > maxPivote) {
                maxPivote = fabs(matriz[k][i]);
                filaPivote = k;
            }
        }

        // Intercambiar filas si es necesario (pivoteo parcial)
        if (filaPivote != i) {
            double *temp = matriz[i];
            matriz[i] = matriz[filaPivote];
            matriz[filaPivote] = temp;

            temp = inversa[i];
            inversa[i] = inversa[filaPivote];
            inversa[filaPivote] = temp;
        }

        // Escalar la fila para tener un pivote de 1
        double pivotValue = matriz[i][i];
        for (int j = 0; j < sz; j++) {
            matriz[i][j] /= pivotValue;
            inversa[i][j] /= pivotValue;
        }

        // Eliminacion hacia abajo
        for (int j = i + 1; j < sz; j++) {
            double m = matriz[j][i];
            for (int k = 0; k < sz; k++) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }

    // Eliminacion hacia arriba
    for (int i = sz - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double m = matriz[j][i];
            for (int k = 0; k < sz; k++) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }
    for(int i=0;i<sz;i++) free(matriz[i]);
    free(matriz);
    return inversa;
}

//Subrutina para multiplicar una matriz por una matriz
double **mult_matxmat(double **sol, double **m1, double **m2, int nRows, int nEqs, int nCols){
	double temp;
	
	//Se realiza la multiplicacion
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			temp=0;
			for(int k=0; k<nEqs; k++){
				temp+=m1[i][k] * m2[k][j];
			}
			sol[i][j] = temp;
		}
	}
	return sol;
}

//Subrutina para multiplicar una matriz inversa por una matriz
double **mult_matinvxmat(double **sol, double **m1, double **m2, int nRows, int nEqs, int nCols){
	double temp;
	
	//Se realiza la multiplicacion
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			temp=0.0;
			for(int k=0; k<nEqs; k++){
				temp+=m1[k][i] * m2[k][j];
			}
			sol[i][j] = temp;
		}
	}
	return sol;
}

/*Subrutina para obtener el determinante de una matriz*/
double detMatrix(double **Mat, int sz){
    if(sz == 1) return fabs(Mat[0][0]);
    else if(sz == 2) return (Mat[0][0]*Mat[1][1]) - (Mat[0][1]*Mat[1][0]);
    else return 55.0;
}

//Subrutina para calcular la norma propuesta
double norma_tol(double *x, double *x0, int sz){
	//Obtenemos la norma de la resta de vectores
	double *res = rest_vec(x, x0, sz);
	//Se obtiene la norma
	double norma = sqrt(mult_vecxvec(res, res, sz));
	//Se obtiene la norma del vector actual
	norma /= sqrt(mult_vecxvec(x, x, sz));
	//Liberando la memoria
	free(res);
	return norma;
}

//Subrutina para multiplicar una matriz por un vector
double *mult_matxvec(double *x, double **matriz, double *vector, int nRows, int nCols){
	double temp=0;
	for(int i=0; i<nRows; i++){
		temp=0;
		for(int j=0; j<nCols; j++){
			temp+=matriz[i][j]*vector[j];
		}
		x[i]=temp;
	}
	return x;
}

//Subrutina para multiplicar dos vectores
double mult_vecxvec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double temp=0;
	for(int i=0; i<sz; i++){
		temp+=v1[i]*v2[i];
	}
	return temp;
}

//Subrutina para realizar una multiplicacion de un vector fila por un vector columna
double ** mult_vecfxvecc(double **sol, double *v1, double *v2, int nRows, int nCols){
    for(int i =0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            sol[i][j] = v1[i] * v2[j];
        }
    }
}

//Subrutina para restar 2 vectores
double *rest_vec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++) x[i]=v1[i]-v2[i];
	return x;
}
