/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 4/Cabecera**********/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdio.h>
#include <math.h>

//Parametros
#define Q 1000.0	//Cantidad de calor
#define K 1.0		//Constante de difusion
#define phi0 0.0	//Condicion de frontera
#define phiN 100.0	//Condicion de frontera
#define L 10.0		//Tamanio de la barra

//Prototipos
double **fact_Cholesky(double **, int);
void imprimirMatriz(double **matriz, int nRows, int nCols);
void free_mat(double **, int);
double **gen_mat_possym(int);
double **gen_vectorB(int);
void free_mat(double **, int);
double *uSolve(double **, double *, int);
double *lSolve(double **, double *, int);

/*Declaraciones*/

//Resolver sistema de ecuaciones mediante factorizacion cholesky
double *solve_cholesky(double **matriz, double *vectorB, int sz){

	//Factorizamos la matriz
	double **LDLt = fact_Cholesky(matriz, sz);
	//Resolvemos Ly=b
	double *y = lSolve(LDLt, vectorB, sz);

	//Resolvemos Dz=y
	double *z = (double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++){
		z[i]=y[i]/LDLt[i][i];
	}

	//Resolvemos Ltx=z
	double *x = uSolve(LDLt, z, sz);

	//Liberamos la memoria
	free_mat(LDLt, sz);
	free(y);
	free(z);

	return x;
}

//Factorizacion Cholesky
double **fact_Cholesky(double **matriz, int sz){

	//Reservamos el espacio para la solucion
	double **LDLt=(double **)malloc(sz * sizeof(double *));
	for(int i=0; i<sz; i++){
		LDLt[i]=(double *)malloc(sz * sizeof(double));
		for(int j=0; j<sz; j++){
			LDLt[i][j]=0.0;
		}
	}

	//Se realiza la factorizacion
	double temp;
	for(int i=0; i<sz; i++){
		for(int j=0; j<=i; j++){
			temp=0;
			if(j==i){
				for(int k=0; k<j; k++){
					temp+=LDLt[j][k]*LDLt[j][k]*LDLt[k][k];
				}
				LDLt[i][j]=matriz[i][j]-temp;
			} else {
				for(int k=0; k<j; k++){
					temp+=LDLt[i][k]*LDLt[j][k]*LDLt[k][k];
				}
				LDLt[i][j]=(matriz[i][j]-temp)/LDLt[j][j];
				LDLt[j][i]=LDLt[i][j];
			}
		}
	}
	return LDLt;
}

// Subrutina de Matriz triangular inferior
double *lSolve(double **matriz, double *vec, int sz) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del primer elemento, la parte trivial
//    X[0] = vec[0]/matriz[0][0];
	//Caso cholesky LDLt
    X[0] = vec[0];

    // Recorremos para los valores de cada renglón
    for (int i = 1; i < sz; i++) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = 0; j < i; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
//        X[i] = (vec[i] - temp) / matriz[i][i];
        //Caso Cholesky
        X[i] = (vec[i] - temp);
    }
    // Regresamos la dirección de memoria donde se almacena
    return X;
}

// Subrutina de matriz triangular superior
double *uSolve(double **matriz, double *vec, int sz){
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
//    X[sz-1] = vec[sz-1]/matriz[sz-1][sz-1];
    //caso Cholesky
    X[sz-1] = vec[sz-1];


    // Recorremos para los valores de cada renglón
    for (int i = sz-2; i >= 0; i--) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = i; j < sz; j++) {
			if(j==i) temp += X[j];
			else temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
//        X[i] = (vec[i] - temp) / matriz[i][i];
		//caso cholesky
        X[i] = (vec[i] - temp);

    }
    // Regresamos la dirección de memoria donde se almacena
    return X;
}

//Subrutina para generar el vector B
double **gen_vectorB(int sz){
	//reservamso el espacio
	double *vectorB = (double *)malloc(sz * sizeof(double));

	//Definimos el tammanio
	double dl = L/sz;

	//Rellenamos el vector
	vectorB[0] = (Q*dl) + ((K/dl)*phi0);
	vectorB[sz-1] = (Q*dl) + ((K/dl)*phiN);
	for(int i=1; i<sz-1; i++) vectorB[i]= (Q*dl);
	return vectorB;
}

//Subrutina para generar una matriz simetrica
double **gen_mat_possym(int sz){

	double dl=L/sz;
	//Reservamos el espacio
	double **matriz = (double **)malloc(sz * sizeof(double *));
	for(int i=0; i<sz; i++){
		matriz[i] = (double *)malloc(sz * sizeof(double));
		for(int j=0; j<sz; j++){
			matriz[i][j] = 0.0;
			if(abs(j-i)==1) matriz[i][j] = -1.0*(K/dl);
			if(j==i) matriz[i][j] = 2.0*(K/dl);
		}
	}
	return matriz;
}

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}

//Subrutina para imprimir una matriz
void imprimirMatriz(double **matriz, int nRows, int nCols){

	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			printf("%g\t",matriz[i][j]);
		}
		printf("\n");
	}
}
