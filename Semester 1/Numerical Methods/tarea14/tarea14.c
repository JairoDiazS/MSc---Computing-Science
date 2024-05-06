/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/**********Tarea 14 Cabecera***********/
/**********Metodos Numericos***********/
/**************01/12/2023**************/
/**************************************/
/**************************************/

#include "tarea14.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **theta_method(double u0(double), double theta, double T, double a, double b, double alpha, int n, int m){
    //Se establecen el tamano de paso
    double K = T / n;
    double h = (b - a) / m;
    double lambda = alpha * K / (h*h);

    //Se obtiene la matriz tridiagonal
    double **B = genMatriz3d(m-2);
    print_mat(B, "bmat.txt", m-2, m-2);

    //Se crea espacio para la matriz A
    double **A = genMatriz(m-2, m-2);

    double *r;
    double *w = (double *)calloc(m-2, sizeof(double));
    for(int i = 0; i<m-2; i++) w[i] = u0(a + ((i+1)*h));

    //Se define la matriz de solucion
    double **sol = genMatriz(n - 2, m - 2);

    //Se inicia el metodo
    int i = 1;
    int j, k;
    while(i < n - 1){
        //Se obtiene la actualizacion
        //la matriz A se copia de la matriz B
        for(j =0; j<m-2; j++){
            for(k = 0; k<m-2; k++){
                A[j][k] = (theta - 1) * lambda * B[j][k];
                if(j == k) A[j][k]++;
            }
        }

        r = mult_matxvec(A, w, m-2, m-2);

        //la matriz A se copia de la matriz B
        for(j =0; j<m-2; j++){
            for(k = 0; k<m-2; k++){
                A[j][k] = theta * lambda * B[j][k];
                if(j == k) A[j][k]++;
            }
        }

        //Se resuelve el sistema de ecuaciones
        free(w);
        w = solver_lu(A, r, m-2, 0);
        //Se guarda el valor obtenido en la matriz de solucion
        for(j=0; j<m-2; j++) sol[i-1][j] = w[j];
        free(r);

        i++;
    }
    free(A[0]); //Memoria contigua
    free(B[0]); //Memoria contigua
    free(A);
    free(B);
    free(w);
    
    return sol;
}

double *solver_lu(double **matriz, double *vectorb, int sz, int o){

	//factorizamos la matriz
	double **LU;
	if(o==0) {LU=fact_LuCrout(matriz, sz);}
	else {LU=fact_Cholesky(matriz, sz);}

	//Resolvemos Ly=b
	double *y = lSolve(LU, vectorb, sz);

	//Resolvemos Ux=y
	double *x = uSolve(LU, y, sz);

	//liberando memoria
	free_mat(LU, sz);
	free(y);

	return x;
}

//Factorizacion Cholesky
double **fact_Cholesky(double **matriz, int sz){

	//Reservamos el espacio para la solucion
	double **LLt=(double **)malloc(sz * sizeof(double *));
	for(int i=0; i<sz; i++){
		LLt[i]=(double *)malloc(sz * sizeof(double));
		for(int j=0; j<sz; j++){
			LLt[i][j]=0.0;
		}
	}

	//Se realiza la factorizacion
	double temp;
	for(int i=0; i<sz; i++){
		for(int j=0; j<=i; j++){
			temp=0;
			if(j==i){
				for(int k=0; k<i; k++){
					temp+=LLt[i][k]*LLt[i][k];
				}
				LLt[i][j]=sqrt(matriz[i][j]-temp);
			} else {
				for(int k=0; k<j; k++){
					temp+=LLt[i][k]*LLt[j][k];
				}
                if(LLt[j][j]==0) printf("(Cholesky)Cuidado division por 0.\n");
				LLt[i][j]=(matriz[i][j]-temp)/LLt[j][j];
				LLt[j][i]=LLt[i][j];
			}
		}
	}
	return LLt;
}

//Factorizacion Crout
double **fact_LuCrout(double **matriz, int sz){

	//Reservamos el espacio para la solucion
	double **LU=(double **)malloc(sz * sizeof(double *));
	for(int i=0; i<sz; i++){
		LU[i]=(double *)malloc(sz * sizeof(double));
		//Se inicializa la matriz en 0
		for(int j=0;j<sz;j++){
			LU[i][j]=0.0;
			if(i==j) LU[i][j]=1.0;
		}
	}

	//Se realiza la factorizacion
	int temp;
	for(int i=0; i<sz; i++){
		for(int j=i; j<sz; j++){
			temp=0;
			for(int k=0; k<j; k++){
				temp+=LU[j][k]*LU[k][i];
			}
			LU[j][i]=matriz[j][i]-temp;
		}
		for(int j=i+1;j<sz;j++){
			temp=0;
			for(int k=0; k<i;k++){
				temp+=LU[i][k]*LU[k][j];
			}
            if(LU[i][i]==0) printf("(Crout)Cuidado, division por 0.\n");
			LU[i][j]=(matriz[i][j]-temp)/LU[i][i];
		}
	}
	return LU;
}

// Subrutina de Matriz triangular inferior
double *lSolve(double **matriz, double *vec, int sz){
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)calloc(sz, sizeof(double));

    // Asignamos el valor del primer elemento, la parte trivial
    X[0] = vec[0]/matriz[0][0];

    // Recorremos para los valores de cada renglon
    for (int i = 1; i < sz; i++) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = 0; j < i; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
        X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la direccion de memoria donde se almacena
    return X;
}

// Subrutina de matriz triangular superior
double *uSolve(double **matriz, double *vec, int sz){
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)calloc(sz, sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
	if(fabs(matriz[sz-1][sz-1])<0.00000000001){
		printf("Valor cercano a 0 (uSolve 1).\n");
		free(X);
		return NULL;
	}
    X[sz-1] = vec[sz-1] / matriz[sz-1][sz-1];
    // X[sz-1] = vec[sz-1];

    // Recorremos para los valores de cada renglon
    for (int i = sz-2; i >= 0; i--) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = i; j < sz; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
		if(fabs(matriz[sz-1][sz-1])<0.00000000001){
			printf("Valor cercano a 0 (uSolve 2).\n");
			free(X);
			return NULL;
		}
        X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la direccion de memoria donde se almacena
    return X;
}

//Subrutina para multiplicar una matriz por un vector
double *mult_matxvec(double **matriz, double *vector, int nRows, int nCols){
	//Reservamos espacio
	double *x=(double *)calloc(nRows, sizeof(double));

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

// Subrutina para generar la matriz del problema
double **genMatriz3d(int sz) {
    // Declaraciones
    int i;

    // Se define espacio para la matriz
    double **matriz = genMatriz(sz, sz);

    // Se rellena la matriz
    for (i = 0; i < sz; i++) {
        if (i > 0) {
            matriz[i][i - 1] = -1.0;
        }
        matriz[i][i] = 2.0;
        if (i < sz - 1) {
            matriz[i][i + 1] = -1.0;
        }
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
    fclose(file);
}

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}
