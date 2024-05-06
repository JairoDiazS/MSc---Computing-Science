/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 11 Cabecera*********/
/***********Metodos Numericos**********/
/**************05/11/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea11.h"

double *least_sqr(double *x, double *y, double lambda, int sz, int k, int n, double (*function)(double, int)){
    //Se define espacio para la matriz B
    double **B = genMatriz(sz, n);
    
    //Se rellena la matriz
    int i,j;
    for(i=0; i<sz; i++){
        for(j=0; j<n; j++){
            if(k<0) B[i][j] = function(x[i], j);
            else B[i][j] = function(x[i]-x[j], j);
        }
    }
    //Se obtiene la traspuesta de la matriz
    double **BT = trans_mat(B, sz, n);

    //Se genera la multiplicacion de la matriz por su traspuesta
    double **A = mult_matxmat(BT, B, n, sz, n);

    //Se suma el valor de lambda a la matriz
    for(i=0; i<n; i++) A[i][i] += lambda;

    //Se obtiene la multiplicacion de B traspuesta con y
    double *b = mult_matxvec(BT, y, n, sz);

    //Se resuelve el sistema de ecuaciones
    //Se realiza la factorizacion QR
    Factor *qr = QR(A, n);
    //Se resuelve el sistema
    //Se obtiene la traspuesta de Q
    double **qt = trans_mat(qr->Left, n, n);
    //se realiza el producto
    double *b1 = mult_matxvec(qt, b, n, n);
    double *coef = uSolve(qr->Right, b1, n);

    //Liberando memoria
    free_factor(qr);
    free(b);
    free(A[0]); //Memoria contigua
    free(A);
    free(BT[0]); //Memoria contigua
    free(BT);
    free(B[0]); //Memoria contigua
    free(B);
    free(qt[0]); //Memoria contigua
    free(qt);
    free(b1);

    //Se retorna la solucion
    return coef;
}

double eval_exp(double *coef, double *x, double x0, int sz){
    double temp=0;
    double r;
    for(int i=0; i<sz; i++){
        r = x0 - x[i];
        temp += coef[i] * exp(- r * r);
    }
    return temp;
}

double eval_serie(double *coef, double x0, int sz, double (*function)(double, int)){
    //Variable temporal
    double temp=0;
    for(int i=0; i<sz; i++) temp += coef[i]*function(x0, i);
    return temp;
}

double exponencial(double r, int n){
    return exp(- r * r);
}

double trigonometrica(double x, int n){
    return cos( n * M_PI * x / 6);
}

double polinomial(double x, int n){
    return pow(x, n);
}

double sutherland(double t, double m0, double su, double t0){
    return m0 * pow((1000*t)/t0, 3.0/2.0) * ((t0+su) / ((1000*t)+su));
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

//Subrutina para factorizacion QR
Factor *QR(double **matriz, int sz){
	//Definimos un espacio para guardar la solucion
	Factor *sol = (Factor *)malloc(sizeof(Factor));
	//Se obtiene el valor de Q
	sol->Left = GramS(matriz, sz);
	//Se obtiene el valor de R
	//Se realiza la trasposicion de la matriz Q
	double **trans = trans_mat(sol->Left, sz, sz);
	sol->Right = mult_matxmat(trans, matriz, sz, sz, sz);
	//Liberamos la memoria
	free(trans[0]); //Memoria contigua
	free(trans);
	return sol;
}

//Subrutina para Gram - Schmidt
double **GramS(double **matriz, int sz){
	//Se genera el espacio para guardar la solucion
	double **Q = genMatriz(sz, sz);
	double *col = (double *)calloc(sz, sizeof(double));
	double *res = (double *)calloc(sz, sizeof(double));
	int cont = 0;
	double dot = 0, norm = 0;

	//Comenzamos la factorizacion
	for(int i=0; i<sz; i++){
		//Fijamos la columna y la guardamos
		for(int j=0; j<sz; j++) col[j] = matriz[j][i];
		//Realizamos la resta de las componentes
		for(int j=0; j<cont; j++){
			//Creamos una copia para cada columna de Q
			for(int k=0; k<sz; k++) res[k] = Q[k][j];
			//Calculamos el producto punto entre el vector a restar y la columna
			dot = mult_vecxvec(col, res, sz);
			//Restamos cada componente a la columna
			for(int k=0; k<sz; k++) col[k] -= dot * res[k];
		}

		//Normalizamos la columna
		norm = mult_vecxvec(col, col, sz);
		norm = sqrt(norm);

		//Le asignamos la columna a Q
		for(int j=0; j<sz; j++) Q[j][i] = col[j] / norm;
		cont++;
	}
	free(col);
	free(res);
	return Q;
}

// Subrutina de Matriz triangular inferior
double *lSolve(double **matriz, double *vec, int sz){
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

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
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
	if(fabs(matriz[sz-1][sz-1])<0.00000000001){
		printf("Valor cercano a 0 (uSolve 1).\n");
		free(X);
		return NULL;
	}
    X[sz-1] = vec[sz-1]/matriz[sz-1][sz-1];

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

//Subrutina para multiplicar una matriz por una matriz
double **mult_matxmat(double **m1, double **m2, int nRows, int nEqs, int nCols){
	//creamos espacio para la solucion
	double **sol = genMatriz(nRows, nCols);
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

//Subrutina para multiplicar dos vectores
double mult_vecxvec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double temp=0;
	for(int i=0; i<sz; i++){
		temp+=v1[i]*v2[i];
	}
	return temp;
}

//Subrutina para transponer una matriz
double **trans_mat(double **matriz, int nRows, int nCols){
	//Definimos espacio para la matriz
	double **trans = genMatriz(nCols, nRows);
	//Se realiza la trasposion
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			trans[j][i] = matriz[i][j];
		}
	}
	//Se retorna la solucion
	return trans;
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

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}

//Subrutina para liberar la estructura de Factor
void free_factor(Factor *sol){
	free(sol->Left[0]); //Memoria contigua
	free(sol->Left);
	free(sol->Right[0]); //Memoria contigua
	free(sol->Right);
	free(sol);
}
