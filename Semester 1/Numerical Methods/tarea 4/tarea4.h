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

//Prototipos
double **fact_Cholesky(double **, int);
double **fact_LuCrout(double **, int);
double **leerMatriz(char *);
void imprimirMatriz(double **matriz, int nRows, int nCols);
void free_mat(double **, int);
double **gen_mat_possym(int);
double *lSolve(double **, double *, int);
double *solver_lu(double **, double *, int, int);
double *uSolve(double **, double *, int, int);
double *rest_vec(double *, double *, int);
double *mult_matxvec(double **, double *, int);

/*Declaraciones*/

double *solver_lu(double **matriz, double *vectorb, int sz, int o){

	//factorizamos la matriz
	double **LU;
	if(o==0) {LU=fact_LuCrout(matriz, sz);}
	else {LU=fact_Cholesky(matriz, sz);}

	//Resolvemos Ly=b
	double *y = lSolve(LU, vectorb, sz);

	//Resolvemos Ux=y
	double *x = uSolve(LU, y, sz, o);

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
			LU[i][j]=(matriz[i][j]-temp)/LU[i][i];
		}
	}
	return LU;
}

// Subrutina de Matriz triangular inferior
double *lSolve(double **matriz, double *vec, int sz) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del primer elemento, la parte trivial
    X[0] = vec[0]/matriz[0][0];

    // Recorremos para los valores de cada rengl�n
    for (int i = 1; i < sz; i++) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = 0; j < i; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
        X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la direcci�n de memoria donde se almacena
    return X;
}
// Subrutina de matriz triangular superior
double *uSolve(double **matriz, double *vec, int sz, int o) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
    if(o==0) X[sz-1] = vec[sz-1]; //caso crout
    else X[sz-1] = vec[sz-1]/matriz[sz-1][sz-1];

    // Recorremos para los valores de cada rengl�n
    for (int i = sz-2; i >= 0; i--) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = i; j < sz; j++) {
			if(o==0 && i==j) temp += X[j];
            else temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
        if(o==0) X[i] = (vec[i] - temp);
        else X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la direcci�n de memoria donde se almacena
    return X;
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

//Subrutina para generar una matriz simetrica
double **gen_mat_possym(int sz){

	//Reservamos el espacio
	double **matriz = (double **)malloc(sz * sizeof(double *));
	for(int i=0; i<sz; i++){
		matriz[i] = (double *)malloc(sz * sizeof(double));
		for(int j=0; j<sz; j++){
			matriz[i][j] = 0.0;
			if(abs(j-i)==1) matriz[i][j] = -1;
			if(j==i) matriz[i][j] = 2;
		}
	}
	return matriz;
}

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}

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

double *rest_vec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++) x[i]=v1[i]-v2[i];
	return x;
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
