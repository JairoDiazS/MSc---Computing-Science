/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 10 Cabecera*********/
/***********Metodos Numericos**********/
/**************29/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea10.h"

double interpolCubicaFix(double *x, double *y, double f0, double fn, double x0, int sz){
    //Reservamos espacio para la matriz
    double **S = genMatriz(sz, 4);
    //Reservamos espacio para las h
    double *h = (double *)calloc(sz-1, sizeof(double));

    //Se rellena la primer columna de la matriz
    int i, j;
    for(i=0; i<sz; i++){
        S[i][0] = y[i];
        if(i<sz-1) h[i] = x[i+1]-x[i];
    }
    //Se obtienen las alphas
    double *alpha = (double *)calloc(sz-1, sizeof(double));
    alpha[0] = 3*(((S[1][0]-S[0][0])/h[0])-f0);
    alpha[sz-2] = 3*(fn-((S[sz-1][0]-S[sz-2][0])/h[sz-2]));
    for(i=1; i<sz-2; i++){
        alpha[i] = ((3*(S[i+1][0]-S[i][0]))/h[i]) - ((3*(S[i][0]-S[i-1][0]))/h[i-1]);
    }

    //Se resuelve el sistema
    double *l = (double *)calloc(sz, sizeof(double));
    double *z = (double *)calloc(sz, sizeof(double));
    double *mu = (double *)calloc(sz, sizeof(double));
    l[0] = 2*h[0];
    mu[0] = 0.5;
    z[0] = alpha[0]/l[0];

    for(i=1; i<sz-1; i++){
        l[i] = (2*(x[i+1]-x[i-1])) - (h[i-1]*mu[i-1]);
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - (h[i-1]*z[i-1])) / l[i];
    }

    l[sz-1] = h[sz-2]*(2-mu[sz-2]);
    z[sz-1] = (alpha[sz-1] - (h[sz-2]*z[sz-2])) / l[sz-1];
    S[sz-1][2] = z[sz-1];

    for(j=sz-2; j>=0; j--){
        S[j][2] = z[j] - (mu[j]*S[j+1][2]);
        S[j][1] = ((S[j+1][0]-S[j][0]) / h[j]) - ((h[j]*(S[j+1][2]+(2*S[j][2])))/3);
        S[j][3] = (S[j+1][2]-S[j][2]) / (3*h[j]);
    }

    i=0;
    while(x0>=x[i]) i++;
    if(i>0) i--;
    double temp = S[i][0] + (S[i][1]*(x0-x[i])) + (S[i][2]*(x0-x[i])*(x0-x[i])) + (S[i][3]*(x0-x[i])*(x0-x[i])*(x0-x[i]));

    //Liberando memoria
    free(l);
    free(mu);
    free(z);
    free(alpha);
    free(h);

    return temp;
}

double interpolCubicaNat(double *x, double *y, double x0, int sz){
    //Reservamos espacio para la matriz
    double **S = genMatriz(sz, 4);
    //Reservamos espacio para las h
    double *h = (double *)calloc(sz-1, sizeof(double));
    
    //Se rellena la primer columna de la matriz
    int i, j;
    for(i=0; i<sz; i++){
        S[i][0] = y[i];
        if(i<sz-1) h[i] = x[i+1]-x[i];
    }

    //Se obtienen las alphas
    double *alpha = (double *)calloc(sz-1, sizeof(double));
    for(i=1; i<sz-1; i++){
        alpha[i] = ((3*(S[i+1][0]-S[i][0]))/h[i]) - ((3*(S[i][0]-S[i-1][0]))/h[i-1]);
    }

    double *l = (double *)calloc(sz, sizeof(double));
    double *z = (double *)calloc(sz, sizeof(double));
    double *mu = (double *)calloc(sz, sizeof(double));

    l[0] = 1.0;
    z[0] = mu[0] = 0.0;
    for(i=1; i<sz-1; i++){
        l[i] = (2*(x[i+1]-x[i-1])) - (h[i-1]*mu[i-1]);
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - (h[i-1]*z[i-1])) / l[i];
    }
    l[sz-1] = 1.0;
    z[sz-1] = S[sz-1][2] = 0.0;
    for(j=sz-2; j>=0; j--){
        S[j][2] = z[j] - (mu[j]*S[j+1][2]);
        S[j][1] = ((S[j+1][0]-S[j][0]) / h[j]) - ((h[j]*(S[j+1][2]+(2*S[j][2])))/3);
        S[j][3] = (S[j+1][2]-S[j][2]) / (3*h[j]);
    }

    //Se rellena la solucion
    i=0;
    while(x0>=x[i]) i++;
    if(i>0) i--;
    double temp = S[i][0] + (S[i][1]*(x0-x[i])) + (S[i][2]*(x0-x[i])*(x0-x[i])) + (S[i][3]*(x0-x[i])*(x0-x[i])*(x0-x[i]));

    //Liberando memoria
    free(l);
    free(mu);
    free(z);
    free(alpha);
    free(h);

    return temp;
}

solInterpol *hermiteDD(double *x, double *y, double *evals, double x0, int sz){
    //Se reserva el espacio para la matriz Q
    double **Q = genMatriz((2*sz)+1, (2*sz)+1);
    //Se reserva espacio para el vector Z
    double *z = (double *)calloc((2*sz)+1, sizeof(double));
    if(z==NULL){
        printf("Error de asignacion de memoria.\n");
        free(Q[0]); //Memoria contigua
        free(Q);
        return NULL;
    } 

    int i, j;

    //Comenzamos el ciclo
    for(i=0; i<sz; i++){
        z[2*i] = x[i];
        z[(2*i)+1] = x[i];
        Q[2*i][0] = y[i];
        Q[(2*i)+1][0] = y[i];
        Q[(2*i)+1][1] = evals[i];
        if(i>0) Q[2*i][1] = (Q[2*i][0]-Q[(2*i)-1][0]) / (z[2*i]-z[(2*i)-1]);
    }
    for(i=1; i<(2*sz)+1; i++){
        for(j=1; j<i; j++) Q[i][j] = (Q[i][j-1]-Q[i-1][j-1]) / (z[i]-z[i-j]);
    }

    //Se almacena la solucion
    solInterpol *sol = (solInterpol *)malloc(sizeof(solInterpol));
    sol->matriz = Q;
    sol->sol = 0.0;
    double temp;
    for(i=0; i< (2*sz)+1; i++){
        temp = 1.0;
        for(j=0; j<i; j++) temp*=(x0-x[j]);
        for(j=0; j<i-1; j++) temp*=(x0-x[j]);
        sol->sol+=Q[i][i]*temp;
    }
    //liberando memoria
    free(z);

    return sol;
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