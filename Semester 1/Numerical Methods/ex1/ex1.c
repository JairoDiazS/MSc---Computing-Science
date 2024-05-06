/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Examen 1 Cabecera**********/
/***********Metodos Numericos**********/
/**************16/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ex1.h"

//Subrutina del metodo del gradiente conjugado con el precondicionado de Jacobi
double *gradienteJacobi(double **matriz, double *vector, int sz, double TOL){
	//Se define el maximo de iteraciones
	int iter = 4*sz;
	//Se define el vector inicial
	double *x0 = (double *)calloc(sz, sizeof(double));
	//Se define el residuo inicial
	double *r0 = (double *)calloc(sz, sizeof(double));
	//Se define P
	double *p0 = (double *)calloc(sz, sizeof(double));
	//Auxiliares
	double *w0, alpha, beta;
	//Se define un vector viejo
	double *x_viejo = (double *)calloc(sz, sizeof(double));
	//Creamos la pseudo inversa
	double *M = (double *)calloc(sz, sizeof(double));
	//Creamos el vector y0
	double *y0 = (double *)calloc(sz, sizeof(double));
	//Contador del bucle
	int count = 0;
	//Inicializacion
	for(int i=0; i<sz; i++){
		r0[i] = vector[i];
		if(fabs(matriz[i][i])<1e-10){
			printf("La matriz tiene un valor de 0 en la diagonal.\n");
			i = sz;
			count = iter+1; //Se evita el bucle pero se libera memoria
		}
		M[i] = 1/matriz[i][i];
		y0[i] = M[i]*vector[i];
		p0[i] = -y0[i];
	}

	//Iniciamos el bucle
	while(count < iter){
		//Se calcula el producto matriz vector
		if(count > 0) free(w0);
		w0 = mult_matxvec(matriz, p0, sz);

		//Se obtiene la perturbacion
		alpha = mult_vecxvec(p0, r0, sz);
		alpha /= mult_vecxvec(p0, w0, sz);

		//Se obtiene la actualizacion
		for(int i=0; i<sz; i++){
			x_viejo[i] = x0[i];
			x0[i] = x0[i] + (alpha * p0[i]);
		}

		//Se calcula el nuevo residuo
		for(int i=0; i<sz; i++){
			r0[i] = r0[i] - (alpha * w0[i]);
		}

		//Verificamos la tolerancia
		if(sqrt(mult_vecxvec(r0, r0, sz))<TOL){
			printf("El metodo convergio tras %d iteraciones.\n", count+1);
			break;
		}

		//Calculamos la y de la siguiene iteracion
		for(int i=0; i<sz; i++) y0[i] = M[i]*r0[i];

		//Calculamos la perturbacion para P
		beta = mult_vecxvec(w0, y0, sz);
		beta /= mult_vecxvec(w0, p0, sz);

		//Se actualiza P
		for(int i=0; i<sz; i++) p0[i] = y0[i] - (beta * p0[i]);

		//Se incrementa el contador
		count++;
	}
	if(count == iter) printf("El algoritmo no convergio tras %d iteraciones.\n", count);
	//Liberando la memoria
	free(r0);
	free(p0);
	free(w0);
	free(M);
	free(y0);
	free(x_viejo);
	return x0;
}

//Subrutina para multiplicar una matriz por un vector
double *mult_matxvec(double **matriz, double *vector, int sz){
	//Reservamos espacio
	double *x=(double *)calloc(sz, sizeof(double));

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

//Subrutina para multiplicar dos vectores
double mult_vecxvec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double temp=0;
	for(int i=0; i<sz; i++){
		temp+=v1[i]*v2[i];
	}
	return temp;
}

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

//Subrutina para resolver sistema ax=b por facotrizacion crout
double *solver_lured(double **LU, double *vectorb, int sz, int o){

	//Resolvemos Ly=b
	double *y = lSolve(LU, vectorb, sz);

	//Resolvemos Ux=y
	double *x = uSolve(LU, y, sz, o);

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
double *lSolve(double **matriz, double *vec, int sz) {
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
double *uSolve(double **matriz, double *vec, int sz, int o) {
    // Definimos una variable temporal
    double temp = 0.0;

    // Definimos el espacio para la solucion
    double *X;
    X = (double *)malloc(sz * sizeof(double));

    // Asignamos el valor del ultimo elemento, la parte trivial
    if(o==0) X[sz-1] = vec[sz-1]; //caso crout
    else X[sz-1] = vec[sz-1]/matriz[sz-1][sz-1];

    // Recorremos para los valores de cada renglon
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
    // Regresamos la direccion de memoria donde se almacena
    return X;
}

//Subrutina para restar 2 vectores
double *rest_vec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++) x[i]=v1[i]-v2[i];
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

//Metodo de la potencia
Eigenv *potencia(double **matriz, double *x00, int *z, int sz, double TOL, int NMax){
    /*Se define el espacio para guardar el eigenvalor y los eigenvectores, estos
    se almacenaran en una estructura, donde lambda representa al eigenvalor
    mientras que vector almacenara los eigenvectores*/

	//Se verifica el tamanio de los eigen valores
	if(*z>sz) *z=sz;
	if(*z<0) *z=1;

	//Se crea espacio para almacenar los eigenvalores y vectores
	Eigenv *sol = (Eigenv *)malloc((*z) * sizeof(Eigenv));
	for(int r=0; r<*z; r++) sol[r].vector = (double *)calloc(sz, sizeof(double));

	//Creamos espacio para la copia del vector inical
	double *x0 = (double *)malloc(sz * sizeof(double));

    //se define un vector
    double *w0;
    //definimos un contador
    int n=0;
    //auxiliares
    double nw0, alpha;
    double lambda, lambda_v;
	double *temp = (double *)calloc(sz, sizeof(double));

	//Creamos un ciclo para obetener los n mayores eigenvalores
	for(int k=0; k<*z; k++){
		//Creamos una copia del vector inical
		for(int i=0; i<sz; i++) x0[i] = x00[i];
		//Asignamos un valor inicial de la lambda anterior
		lambda_v=0;
        n=0;
		while(n<NMax){
			/*Se le quita al vector las componentes que ya se han encontrado*/
			for(int y=0; y<k; y++){
				//Calculando el vector a restar
				alpha = mult_vecxvec(sol[y].vector, x0, sz);
				for(int c=0; c<sz; c++) temp[c] = alpha*sol[y].vector[c];
				x0 = rest_vec(x0, temp, sz);
			}
			//Realizamos el producto de Ax_0
			w0 = mult_matxvec(matriz, x0, sz);

			//Normalizamos el vector
			nw0 = mult_vecxvec(w0,w0, sz);
			nw0=sqrt(nw0);
			for(int i=0; i<sz; i++) w0[i]/=nw0;

			//Se obtiene el eigenvalor
			lambda = mult_vecxvec(w0, mult_matxvec(matriz, w0, sz), sz);

			//Verificamos la convergencia
			if(fabs(lambda-lambda_v)<TOL){
				printf("La solucion del %d eigenvalor se encontro tras %d iteraciones.\n",k+1,n);
				sol[k].lambda = lambda;
				for(int d=0; d<sz; d++) sol[k].vector[d] = w0[d];
				break;
			}

			//Actualizamos los valores
			lambda_v = lambda;
			for(int p=0; p<sz; p++) x0[p]=w0[p];
			n++;
    	}
		if(n==NMax){
			printf("El algoritmo no convergio para el %d eigenvalor tras %d iteraciones.\n", k+1, NMax);
			sol[k].lambda = lambda;
			for(int d=0; d<sz; d++) sol[k].vector[d] = w0[d];
			//*z = k;
			//return sol;
		}
	}
	free(temp);
	free(x0);
	free(w0);
    return sol;
}

//Metodo de la potencia inversa
Eigenv *potencia_inv(double **matriz, double *x00, int *z, int sz, double TOL, int NMax){
    /*Se define el espacio para guardar el eigenvalor y los eigenvectores, estos
    se almacenaran en una estructura, donde lambda representa al eigenvalor
    mientras que vector almacenara los eigenvectores*/

	//Se verifica el tamanio de los eigen valores
	if(*z>sz) *z=sz;
	if(*z<0) *z=1;

	//Se crea espacio para almacenar los eigenvalores y vectores
	Eigenv *sol = (Eigenv *)malloc((*z) * sizeof(Eigenv));
	for(int r=0; r<*z; r++) sol[r].vector = (double *)calloc(sz, sizeof(double));

	//Creamos espacio para la copia del vector inical
	double *x0 = (double *)malloc(sz * sizeof(double));

    //se define un vector
    double *w0;
    //definimos un contador
    int n=0;
    //auxiliares
    double nw0, alpha;
    double lambda, lambda_v;
	double *temp = (double *)calloc(sz, sizeof(double));

	//Factorizamos la matriz
	double **LU = fact_Cholesky(matriz, sz);

	//Creamos un ciclo para obetener los n mayores eigenvalores
	for(int k=0; k<*z; k++){
		//Creamos una copia del vector inical
		for(int i=0; i<sz; i++) x0[i] = x00[i];
		//Asignamos un valor inicial para la lambda vieja
		lambda_v=10000000000;
        n=0;
		while(n<NMax){
			/*Se le quita al vector las componentes que ya se han encontrado*/
			for(int y=0; y<k; y++){
				//Calculando el vector a restar
				alpha = mult_vecxvec(sol[y].vector, x0, sz);
				for(int c=0; c<sz; c++) temp[c] = alpha*sol[y].vector[c];
				x0 = rest_vec(x0, temp, sz);
			}
			//Resolvemos el problema de Ax_k+1=x_k
			w0 = solver_lured(LU, x0, sz,1); //Cholesky

			//Normalizamos el vector
			nw0 = mult_vecxvec(w0,w0, sz);
			nw0=sqrt(nw0);
			for(int i=0; i<sz; i++) w0[i]/=nw0;

			//Se obtiene el eigenvalor
			lambda = mult_vecxvec(w0, mult_matxvec(matriz, w0, sz), sz);

			//Verificamos la convergencia
			if(fabs(lambda-lambda_v)<TOL){
				printf("La solucion del %d eigenvalor se encontro tras %d iteraciones.\n",k+1,n);
				sol[k].lambda = lambda;
				for(int d=0; d<sz; d++) sol[k].vector[d] = w0[d];
				break;
			}

			//Actualizamos los valores
			lambda_v = lambda;
			for(int p=0; p<sz; p++) x0[p]=w0[p];
			n++;
    	}
		if(n==NMax){
			printf("El algoritmo no convergio para el %d eigenvalor tras %d iteraciones.\n", k+1, NMax);
			sol[k].lambda = lambda;
			for(int d=0; d<sz; d++) sol[k].vector[d] = w0[d];
			//*z = k;
			//return sol;
		}
	}
	free(temp);
	free(x0);
	free(w0);
	free(LU[0]);
	free(LU);
    return sol;
}

//Subrutina para genera la matriz del problema
double **gen_matProblema(){
    //Declaraciones
    int i, sz=2000;
    double  **matriz, *temp;

    //Se define espacio para la matriz
    matriz = (double **)malloc(sz * sizeof(double *));
    if(matriz ==  NULL){
        printf("(01) Error de asignacion de memoria.\n");
        return NULL;
    }

    //Se define como memoria contigua
    temp = (double *)calloc(sz*sz, sizeof(double));
    if(temp == NULL){
        printf("(02) Error de asignacion de memoria.\n");
        free(matriz);
        return NULL;
    }

    //Se asigna cada apuntaddor a la matriz
    for(i=0; i<sz; i++){
        matriz[i] = temp + (sz*i);
    }

    //Se rellena la matriz
    for(i=2; i<1998; i++){
        matriz[i][i-2] = -4.0;
        matriz[i][i-1] = -8.0;
        matriz[i][i] = 40.0;
        matriz[i][i+1] = -8.0;
        matriz[i][i+2] = -4.0;
    }

    matriz[0][0] = matriz[1][1] = 40.0;
    matriz[0][1] = matriz[1][0] = matriz[1][2] = -8.0;
    matriz[0][2] = matriz[1][3] = -4.0;
    matriz[1999][1999] = matriz[1998][1998] = 40.0;
    matriz[1999][1998] = matriz[1998][1997] = matriz[1998][1999] = -8.0;
    matriz[1999][1997] = matriz[1998][1996] = -4.0;

    return matriz;
}

//Subrutina para generar el vector del problema
double *gen_vec(){
    int sz =2000;
    //Se reserva la memoria
    double *x = (double *)calloc(sz, sizeof(double));
    //Se rellena
    for(int i=0; i<sz; i++) x[i] = 100.0;
    x[0] = x[1999] = 20.0;
    x[1] = x[1998] = 50.0;

    return x;
}

//Subrutina para imprimir una matriz a un archivo
void print_mat(double **matriz, char *name, int sz){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++){
            fprintf(file, "%lf\t", matriz[i][j]);
        }
        fprintf(file, "\n");
    }
}

//Subrutina para imprimir un vector a un archivo
void print_vec(double *vector, char *name, int sz){
    //Abrimos el archivo
    FILE *file = fopen(name, "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return;
    }
    //Se imprime en archivo
    for(int i =0; i<sz; i++) fprintf(file, "%lf\n", vector[i]);
}

//Subrutina para liberar memoria de una matriz
void free_mat(double **matriz, int sz){
	for(int i=0; i<sz; i++) free(matriz[i]);
	free(matriz);
}

//Subrutina para liberar Eigenv
void free_eigen(Eigenv *stc, int sz){
	for(int i=0; i<sz; i++){
		free(stc[i].vector);
	}
	free(stc);
}

//Subrutina para imrpimir en un archivo
void print_eigenv_file(Eigenv *sol, char *fn, int sz1, int sz2){
	FILE *archivo = fopen(fn, "w");
	if(archivo == NULL){
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	for(int i=0; i<sz1; i++){
		fprintf(archivo, "El valor del %d eigenvalor es %lf\n", i+1, sol[i].lambda);
		fprintf(archivo, "El eigenvector asociado es: \n");
		for(int j=0; j<sz2; j++){
			fprintf(archivo, "%lf\t", sol[i].vector[j]);
		}
		fprintf(archivo, "\n");
	}
}