/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 13 Cabecera*********/
/***********Metodos Numericos**********/
/**************19/11/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea13.h"

double **edos_ivp(double *(*f)(double *, int), double *(*m)(double *(*)(double *, int),\
                    double *, double, int), double a, double b, int N, double *alpha, int sz){
    double h = (b-a)/N;
    double **sol = genMatriz(N+1, sz+1);
    double *yi;
    sol[0][0] = a;
    for(int i=0; i<sz; i++) sol[0][i+1] = alpha[i];
    
    for(int i=0; i<N; i++){
        yi = m(f, sol[i], h, sz);
        for(int j=0; j<sz; j++){
            sol[i+1][j+1] = yi[j];
        }
        sol[i+1][0] = a + (i+1)*h;
        free(yi);
    }

    return sol;
}

double *euler(double *(*f)(double *, int sz), double *x, double h, int sz){
    double *fy = f(x, sz);
    double *sol = (double *)calloc(sz, sizeof(double));
    for(int i=0; i<sz; i++) sol[i] = x[i+1] + (h * fy[i]);

    free(fy);

    return sol;
}

double *heun(double *(*f)(double *, int sz), double *x, double h, int sz){
    //Se copia el vector de entrada
    double *xc = (double *)calloc(sz+1, sizeof(double));
    for(int i=0; i<sz+1; i++) xc[i] = x[i];
    //Euler yp
    double *yp = (double *)calloc(sz, sizeof(double));
    double *fy = f(xc, sz); //Evaluacion de la funcion
    for(int i=0; i<sz; i++) yp[i] = x[i+1] + (h * fy[i]);
    //Actualizamos la copia con los valores de euler
    xc[0] += h;
    for(int i=0; i<sz; i++) xc[i+1] = yp[i];
    //Evaluacion en los nuevos puntos
    double *fn = f(xc, sz);
    //Se actualiza la solucion
    for(int i=0; i<sz; i++) yp[i] = x[i+1] + ( (h/2.0) * (fy[i] + fn[i]) );

    free(xc);
    free(fy);
    free(fn);
    return yp;
}

double *taylor_2(double *(*f)(double *, int sz), double *x, double h, int sz){
    //Derivadas parciales para cada variable (sz+1)
    double **g = gradiente1(f, x, h/100.0, sz);

    //Euler yp
    double *yp = (double *)calloc(sz, sizeof(double));
    double *fy = f(x, sz); //Funcion en (x)
    for(int i=0; i<sz; i++) yp[i] = x[i+1] + (h * fy[i]);
    //Solucion
    double *sol = (double *)calloc(sz, sizeof(double));
    //Vector temporal
    double *temp = (double *)calloc(sz, sizeof(double));
    for(int i=0; i<sz; i++){
        temp[i] = g[i][0];
        //Parcial por su funcion
        for(int j=0; j<sz; j++) temp[i] += g[i][j+1]*fy[j]; 

        //Rellenando solucion
        sol[i] = yp[i] + (((h*h)/2.0) * (temp[i]));
    }

    //Liberando memoria
    free(temp);
    free(g[0]); //Memoria contigua
    free(g);
    free(yp);
    free(fy);

    return sol;
}

double *rk_4(double *(*f)(double *, int sz), double *x, double h, int sz){
    //Se copia el vector
    double *xc = (double *)calloc(sz+1, sizeof(double));
    for(int i=0; i<sz+1; i++) xc[i] = x[i];
    double *k1 = f(xc, sz);
    //Se actualiza para k2
    xc[0] += h/2.0;
    for(int i=0; i<sz; i++) xc[i+1] += (h/2.0) * k1[i];
    double *k2 = f(xc, sz);
    //Se regresa al vector original y se obtiene k3
    for(int i=0; i<sz+1; i++) xc[i] = x[i];
    xc[0] += h/2.0;
    for(int i=0; i<sz; i++) xc[i+1] += (h/2.0) * k2[i];
    double *k3 = f(xc, sz);
    //Se regresa al vector original y se obtiene k4
    for(int i=0; i<sz+1; i++) xc[i] = x[i];
    xc[0] += h;
    for(int i=0; i<sz; i++) xc[i+1] += h * k2[i];
    double *k4 = f(xc, sz);

    //Rellenando la solucion
    double *sol = (double *)calloc(sz, sizeof(double));
    for(int i=0; i<sz; i++) sol[i] = x[i+1] + (h/6.0) * (k1[i] + (2.0*k2[i]) + (2.0*k3[i]) +k4[i]);

    free(xc);
    free(k1);
    free(k2);
    free(k3);
    free(k4);

    return sol;
}

//Rutina de cuadratura gaussiana de 3 puntos
double GC3(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x1 = (1.0/35.0) * sqrt(525.0 - (70.0 * sqrt(30.0)));
    double x2 = (1.0/35.0) * sqrt(525.0 + (70.0 * sqrt(30.0)));
    double t1 = (((b-a)*(x1))+a+b)/2.0;
    double t2 = (((b-a)*(-x1))+a+b)/2.0;
    double t3 = (((b-a)*(x2))+a+b)/2.0;
    double t4 = (((b-a)*(-x2))+a+b)/2.0;

    double p1 = (1.0/36.0) * (18.0 + sqrt(30.0)) * (function(t1)+function(t2));
    double p2 = (1.0/36.0) * (18.0 - sqrt(30.0)) * (function(t3)+function(t4));

    return ((b-a)/2.0) * (p1 + p2);
}

double **gradiente1(double *(*f)(double *, int), double *x, double h, int sz){
    double **sol = genMatriz(sz +1, sz);
    double *fd, *fu;
    double *xc = (double *)calloc(sz+1, sizeof(double));
    //Se crea una copia
    for(int i=0; i<sz+1; i++) xc[i] = x[i];
    for(int i=0; i<sz+1; i++){
        xc[i] -= h;
        fd = f(xc, sz);
        xc[i] += 2.0*h;
        fu = f(xc, sz);
        xc[i] -= h;
        //Se calcula la derivada
        for(int j=0; j<sz; j++){
            sol[i][j] = (1.0/(2.0*h))*(fu[j]-fd[j]);
        }
        free(fd);
        free(fu);
    }
    return sol;
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

//Subrutina para leer matrices desde la terminal
double **r_mat(const char *fn, int *nRows, int *nCols){
    //Abrimos el archivo en modo lectura
    FILE *file = fopen(fn, "r");
    if(file == NULL){
        printf("Error de apertura de archivo.\n");
        return NULL;
    }
    //Se lee la primer linea del archivo que debe tener el numero de evaluaciones
    fscanf(file, "%d %d", nRows, nCols);

    //Se crea espacio para el arreglo
    double **matriz = genMatriz(*nRows, *nCols);
    if(matriz == NULL){
        printf("Error de asignacion de memoria.\n");
        fclose(file);
        return NULL;
    }

    // Se rellena la matriz
    for (int i = 0; i < *nRows; i++) {
        for (int j = 0; j < *nCols; j++) {
            fscanf(file, "%lf", &matriz[i][j]);  // Corregir cómo se accede a la matriz
        }
    }

    fclose(file);

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
    fclose(file);
}
