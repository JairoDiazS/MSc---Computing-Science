#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Prototipos
double *lSolve(double **, double *, int);
void imprimirMatrizC(double **, int, int);
double *uSolve(double **, double *, int);
double *gauss(double **, double *, int);

// Subrutina de Matriz triangular inferior
double *lSolve(double **matriz, double *vec, int sz) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del primer elemento, la parte trivial
    X[0] = vec[0]/matriz[0][0];

    // Recorremos para los valores de cada renglón
    for (int i = 1; i < sz; i++) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = 0; j < i; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
        X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la dirección de memoria donde se almacena
    return X;
}

// Subrutina de matriz triangular superior
double *uSolve(double **matriz, double *vec, int sz) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
    X[sz-1] = vec[sz-1]/matriz[sz-1][sz-1];

    // Recorremos para los valores de cada renglón
    for (int i = sz-2; i >= 0; i--) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = i; j < sz; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
        X[i] = (vec[i] - temp) / matriz[i][i];
    }
    // Regresamos la dirección de memoria donde se almacena
    return X;
}

//Subrutina de eliminacion gaussiana
double *gauss(double **matriz, double *vec, int sz){
    //Definimos el espacio donde se guarda la solucion
    double *X=(double *)malloc(sz*sizeof(double));
    //definimos el multiplicador
    double m=0.0;
    //Comenzamos con el proceso de eliminacion
    for(int i=0;i<sz-1;i++){
        for(int j=i+1; j<sz; j++){
            m=matriz[j][i]/matriz[i][i];
            for(int k=0;k<sz;k++){
                matriz[j][k]=matriz[j][k]-(m*matriz[i][k]);
            }
            vec[j]=vec[j]-(vec[i]*m);
        }
    }

    //Procedemos con la solucion
    X=uSolve(matriz,vec,sz);
    return X;
}

//subrutina de pivoteo parcial
double *gauss_parc(double **matriz, double *vec, int sz){
    //Definimos el espacio donde se guarda la solucion
    double *X=(double *)malloc(sz*sizeof(double));
    //definimos el multiplicador
    double m=0.0;
    //Comenzamos con el proceso de eliminacion
    for(int i=0;i<sz-1;i++){

        // Encontrar el pivote parcial (el elemento de mayor valor absoluto en la columna)
        double maxPivote = fabs(matriz[i][i]);
        int filaPivote = i;

        for (int k = i + 1; k < sz; k++) {
            if (fabs(matriz[k][i]) > maxPivote) {
                maxPivote = fabs(matriz[k][i]);
                filaPivote = k;
            }
        }

        // Intercambiar filas si es necesario (pivoteo parcial)
        double *temp;
        double temps;
        if (filaPivote != i) {
            temp = matriz[i];
            matriz[i] = matriz[filaPivote];
            matriz[filaPivote]=temp;
            temps = vec[i];
            vec[i] = vec[filaPivote];
            vec[filaPivote] = temps;
        }

        for(int j=i+1; j<sz; j++){
            m=matriz[j][i]/matriz[i][i];
            for(int k=0;k<sz;k++){
                matriz[j][k]=matriz[j][k]-(m*matriz[i][k]);
            }
            vec[j]=vec[j]-(vec[i]*m);
        }
    }

    //Procedemos con la solucion
    X=uSolve(matriz,vec,sz);
    return X;
}

//Subrutina para imrpimir matrices
void imprimirMatrizC(double **matriz, int nFils, int nCols){
	for(int i=0;i<nFils;i++){
		for(int j=0;j<nCols;j++){
			printf("%g\t",matriz[i][j]);
		}
		printf("\n");
	}
}
