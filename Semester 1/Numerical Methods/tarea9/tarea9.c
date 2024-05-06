/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 9 Cabecera**********/
/***********Metodos Numericos**********/
/**************22/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea9.h"

//Rutina para evaluar polinomio interpolante de Newton
solInterpol *eval_newtonDD(double *x, double *y, double z, int n){
    //Iteradores
    int i,j;
    //Reservamos espacio para la matriz
    double **F = genMatriz(n,n), sol, prod;
    //Reservamos espacio para la solucion
    solInterpol *stc = (solInterpol *)malloc(sizeof(solInterpol));
    
    //Rellenamos la primer columna
    for(i=0; i<n; i++) F[i][0] = y[i];

    //Se rellena la matriz
    for(i=1; i<n; i++){
        for(j=1; j<=i; j++){
            F[i][j] = (F[i][j-1] - F[i-1][j-1]) / (x[i]-x[i-j]);
        }
    }

    //Calculamos la evaluacion
    sol = F[0][0];
    for(i=1; i<n; i++){
        prod = 1.0;
        for(j=0; j<i; j++) prod *= (z-x[j]);
        sol += F[i][i]*prod;
    }

    stc->matriz = F;
    stc->sol = sol;

    return stc;
}

//Rutina para evaluar polinomio de Neville
solInterpol *eval_neville(double *x, double *y, double z, int n){
    //Iteradores
    int i, j;
    //Reservamos espacio para la matriz
    double **Q = genMatriz(n, n);
    //Reservamos espacio para la solucion
    solInterpol *stc = (solInterpol *)malloc(sizeof(solInterpol));

    //Rellenamos la primer columna
    for(i=0; i<n; i++) Q[i][0] = y[i];

    //Se rellena la tabla
    for(i=1; i<n; i++){
        for(j=1; j<=i; j++){
            Q[i][j] = (((z - x[i-j])*Q[i][j-1]) - ((z - x[i])*Q[i-1][j-1])) / (x[i] - x[i-j]);
        }
    }

    stc->matriz = Q;
    stc->sol = Q[n-1][n-1];

    return stc;
}

//Rutina para evaluar el polinomio de Lagrange
double eval_lagrange(double *x, double *y, double z, int n){
    int i,j;
    double prod, sol=0;
    //Ciclo para recorrer todos los puntos
    for(i=0; i<=n; i++){
        //ciclo para calcular el numerador/denominador
        prod = 1.0;
        for(j=0; j<=n; j++){
            if(j != i){
                prod *= (z - x[j])/(x[i] - x[j]);
            }
        }
        sol += y[i]*prod;
    }
    return sol;
}

//Rutina para evaluar el polinomio de Taylor
double eval_taylor(double *eval, double z, double x0, int n){
    int i;
    double dif = z-x0;
    double res = eval[0];
    double prod = 1.0;
    for(i=1; i<n; i++){
        prod *= dif/i;
        res += eval[i]*prod;
    }
    return res;
}

//Subrutina para leer pares de puntos
double **r_pairs(const char *fn, int *sz){
    //Abrimos el archivo en modo lectura
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Error de apertura de archivo.\n");
        return NULL;
    }
    //Se lee la primer linea del archivo que debe tener el numero de evaluaciones
    fscanf(file, "%d", sz);

    //Se crea espacio para el arreglo
    double **arr = (double **)malloc(2 * sizeof(double *));
    if(arr == NULL){
        printf("Error de asignacion de memoria.\n");
        fclose(file);
        return NULL;
    }
    //Se crea memoria contigua
    double *temp = (double *)calloc(2*(*sz), sizeof(double));
    if(temp == NULL){
        printf("Error de asignacion de memoria.\n");
        free(arr);
        fclose(file);
        return NULL;
    }
    //Se asigna el espacio
    arr[0] = temp;
    arr[1] = temp + (*sz);

    //Se rellena el arreglo
    for(int i=0; i<*sz; i++) fscanf(file, "%lf %lf", arr[0] + i, arr[1] + i);

    fclose(file);

    return arr;
}

//Subrutina para leer las evaluaciones del polinomio y sus respectivas derivadas
double *r_points(const char *fn, int *sz){
    //Abrimos el archivo en modo lectura
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Error de apertura de archivo.\n");
        return NULL;
    }
    //Se lee la primer linea del archivo que debe tener el numero de evaluaciones
    fscanf(file, "%d", sz);

    //Se crea espacio para el arreglo
    double *arr = (double *)calloc(*sz, sizeof(double));
    if(arr == NULL){
        printf("Error de asignacion de memoria.\n");
        fclose(file);
        return NULL;
    }

    //Se rellena el arreglo
    for(int i=0; i<*sz; i++) fscanf(file, "%lf", arr + i);

    fclose(file);

    return arr;
}

void sortPairs(double **mat, int sz){
    double tempx, tempy;
    for(int i=0; i<sz-1; i++){
        for(int j=0; j<sz-1; j++){
            if(mat[j][0] > mat[j+1][0]){
                tempx = mat[j][0];
                tempy = mat[j][1];
                mat[j][0] = mat[j+1][0];
                mat[j][1] = mat[j+1][1];
                mat[j+1][0] = tempx;
                mat[j+1][1] = tempy;
            }
        }
    }
}

void free_interpol(solInterpol *stc){
    free(stc->matriz[0]); //Memoria contigua
    free(stc->matriz);
    free(stc);
}

//Subrutina para generar una matriz en 0's
double **genMatriz(int nRows, int nCols){
	//Definimos el espacio para la matriz
	double **matriz, *temp;
	matriz = (double **)malloc(nRows * sizeof(double *));
	if(matriz == NULL){
		printf("Error de asignacion de memoria.\n");
		return NULL;
	}
	temp = (double *)calloc(nRows * nCols, sizeof(double));
	if(temp == NULL){
		printf("Error de asignacion de memoria.\n");
		free(matriz);
		return NULL;
	}
	for(int i = 0; i< nRows; i++){
		matriz[i] = &temp[i * nCols];
	}
	return matriz;
}

//Subrutina para imprimir una matriz
void imprimirMatriz(double **matriz, int nRows, int nCols){
	if(nCols >10 || nRows>10) printf("Dado el tamanio, solo se muestra las primeras 10 filas/columnas.\n");
	if(nRows>10) nRows=10;
	if(nCols>10) nCols=10;
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			printf("%g\t",matriz[i][j]);
		}
		printf("\n");
	}
}

//Subrutina para imprimir una matriz a un archivo
void print_mat(double **matriz, char *name, int nRows, int nCols){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nCols; j++){
            fprintf(file, "%lf\t", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
}
