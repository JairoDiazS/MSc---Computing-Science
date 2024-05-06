/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 7 Cabecera**********/
/***********Metodos Numericos**********/
/**************01/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea7.h"

//Declaraciones

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
    double *x, *w0;
    //definimos un contador
    int n=0;
    //auxiliares
    double nw0, alpha;
    double lambda, lambda_v;
	double *temp = (double *)calloc(sz, sizeof(double));

	//definimos un contador para saber cuantos lambda se han obtenido ya
	int count = 0;

	//Creamos un ciclo para obetener los n mayores eigenvalores
	for(int k=0; k<*z; k++){
		//Creamos una copia del vector inical
		for(int i=0; i<sz; i++) x0[i] = x00[i];
		//Asignamos un valor inicial de la lambda anterior
		lambda_v=0;
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
    double *x, *w0;
    //definimos un contador
    int n=0;
    //auxiliares
    double nw0, alpha;
    double lambda, lambda_v;
	double *temp = (double *)calloc(sz, sizeof(double));

	//Factorizamos la matriz
	double **LU = fact_LuCrout(matriz, sz);

	//definimos un kontador para saber cuantos lambda se han obtenido ya
	int count = 0;

	//Creamos un ciclo para obetener los n mayores eigenvalores
	for(int k=0; k<*z; k++){
		//Creamos una copia del vector inical
		for(int i=0; i<sz; i++) x0[i] = x00[i];
		//Asignamos un valor inicial para la lambda vieja
		lambda_v=10000000000;
		while(n<NMax){
			/*Se le quita al vector las componentes que ya se han encontrado*/
			for(int y=0; y<k; y++){
				//Calculando el vector a restar
				alpha = mult_vecxvec(sol[y].vector, x0, sz);
				for(int c=0; c<sz; c++) temp[c] = alpha*sol[y].vector[c];
				x0 = rest_vec(x0, temp, sz);
			}
			//Resolvemos el problema de Ax_k+1=x_k
			w0 = solver_lu(LU, x0, sz,0);

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

//Metodo de Jacobi para eigenvalores
Eigenv *eigen_jacobi(double **matriz, int sz, double TOL, int NMax){
	
	/*Definimos el espacio donde se va a guardar la solucion*/
	Eigenv *sol = (Eigenv *)malloc(sz * sizeof(Eigenv));
	/*Definimos el espacio para la matriz donde se tendran los eigenvectores*/
	double **rep = genMatriz(sz, sz);
	/*Se define el espacio para la matriz de rotacion*/
	double **rot = genMatriz(sz, sz);

	for(int i=0; i<sz; i++){
		sol[i].vector = (double *)calloc(sz, sizeof(double));
		//Iniciamos con la diagonal en 1
		rep[i][i] = 1.0;
		rot[i][i] = 1.0;
	}

	//Auxiliares
	double max, c, s, theta, **temp, **temp1, **temp2;
	int ii, jj, n=0;

	while(n<NMax){
		//Buscamos el valor maximo fuera de la diagonal
		max = 0;
		for(int i=0; i<sz; i++){
			for(int j=i+1; j<sz; j++){
				if(fabs(max)<fabs(matriz[i][j])){
					max = matriz[i][j];
					ii=i;
					jj=j;
				}
			}
		}

		//Se verifica la convergencia
		if(fabs(max)<TOL){
			break;
		}

		//Se obtiene el angulo de rotacion
		if(matriz[ii][ii] == matriz[jj][jj]) theta = M_PI_4;
		else theta =0.5 * atan2(2.0 * matriz[ii][jj], matriz[ii][ii]-matriz[jj][jj]);

		//Se modifica la matriz de rotacion
		c = cos(theta);
		s = sin(theta);

		//Se realiza la matriz diagonal a partir de la matriz identidad

		for(int i=0; i< sz; i++){
			for(int j=0; j<sz; j++){
				rot[i][j] = 0.0;
			}
			rot[i][i] = 1.0;
		}

		//Originalmente tenemos la traspuesta
		rot[ii][ii] = c;
		rot[jj][jj] = c;
		rot[ii][jj] = -s;
		rot[jj][ii] = s;

		//Trasponemos la matriz
		for(int i=0; i<sz; i++){
			for(int j=i+1; j<sz; j++){
				rot[i][j] = -rot[i][j];
				rot[j][i] = -rot[j][i];
			}
		}

		//Actualizamos las matrices realizando la rotacion
		temp = mult_matxmat(rot, matriz, sz);

		//Se tiene la matriz de rotacion sin trasponer
		for(int i=0; i<sz; i++){
			for(int j=i+1; j<sz; j++){
				rot[i][j] = -rot[i][j];
				rot[j][i] = -rot[j][i];
			}
		}

		temp1 = mult_matxmat(temp, rot, sz);

		//Actualizamos el vector de respuesta
		temp2 = mult_matxmat(rep, rot, sz);

		//Liberamos la memoria que ha sido creada
		free(temp[0]);
		free(matriz[0]);
		free(rep[0]);
		for(int i=0; i<sz; i++){
			//Actualizando los valores
			matriz[i] = temp1[i];
			rep[i] = temp2[i];

		}
		printf("vuelta\n");
		n++;
	}
	//Si la convergencia no se alcanza retornamos nulo
	if(n == NMax){
		printf("El algoritmo no ha convergido tras %d iteraciones.\n",NMax);
		//Si la convergencia se alcanza llenamos la solcion
		for(int i=0; i<sz; i++){
			sol[i].lambda = matriz[i][i];
			sol[i].vector = rep[i];
		}
		return sol;
	}
	//Si la convergencia se alcanza llenamos la solcion
	printf("La convergencia se encontro tras %d iteraciones.\n", n);
	for(int i=0; i<sz; i++){
		sol[i].lambda = matriz[i][i];
		for(int j=0; j<sz; j++){
			sol[i].vector[j] = rep[j][i];
		}
	}
	//Liberando espacio
	//free_mat(temp, sz);
	//free_mat(temp1, sz);
	//free_mat(temp2, sz);
	free(rep[0]);
	free(rep);
	free(rot[0]);
	free(rot);
	
	return sol;
}

//Subrutina para resolver sistema ax=b por facotrizacion crout
double *solver_lu(double **LU, double *vectorb, int sz, int o){

	//Resolvemos Ly=b
	double *y = lSolve(LU, vectorb, sz);

	//Resolvemos Ux=y
	double *x = uSolve(LU, y, sz, o);

	free(y);

	return x;
}

//Factorizacion Crout
double **fact_LuCrout(double **matriz, int sz){

	//Reservamos el espacio para la solucion
	double **LU=genMatriz(sz, sz);

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
double *uSolve(double **matriz, double *vec, int sz, int o){
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

//Subrutina para multiplicar una matriz por una matriz
double **mult_matxmat(double **m1, double **m2, int sz){
	//creamos espacio para la solucion
	double **sol = genMatriz(sz, sz);
	double temp=0.0;
	
	//Se realiza la multiplicacion
	for(int i=0; i<sz; i++){
		for(int j=0; j<sz; j++){
			temp=0;
			for(int k=0; k<sz; k++){
				temp+=m1[i][k] * m2[k][j];
			}
			sol[i][j] = temp;
		}
	}
	return sol;
}

//Subrutina para multiplicar una matriz por un vector
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

//Subrutina para multiplicar dos vectores
double mult_vecxvec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double temp=0;
	for(int i=0; i<sz; i++){
		temp+=v1[i]*v2[i];
	}
	return temp;
}

//Subrutina para restar 2 vectores
double *rest_vec(double *v1, double *v2, int sz){
	//Reservamos espacio
	double *x=(double *)malloc(sz * sizeof(double));
	for(int i=0; i<sz; i++) x[i]=v1[i]-v2[i];
	return x;
}

//Subrutina para leer una matriz desde un archivo
double **leerMatriz(char *nFile, int* sz){

	//Abrir archivo en modo lectura
	FILE *file = fopen(nFile, "r");

	//verificar que el archivo se abrio correctamente
	if(file==NULL) return NULL;

	//Se define el tamanio de la matriz
	int nCols, nRows;
	fscanf(file, "%d %d", &nRows, &nCols);

	//Reservamos memoria para la matriz
	double **matriz = genMatriz(nRows, nCols);
	int i;
	//Rellenando la matriz
	for(i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			fscanf(file, "%lf",&matriz[i][j]);
		}
	}

	fclose(file);

    *sz=nRows;

	return matriz;
}

//Subrutina para imprimir una matriz
void imprimirMatriz(double **matriz, int nRows, int nCols){
	if(nRows>10) nRows=10;
	if(nCols>10) nCols=10;
	if(nCols >10 || nRows>10) printf("Dado el tamanio, solo se muestra las primeras 10 filas/columnas.\n");
	for(int i=0; i<nRows; i++){
		for(int j=0; j<nCols; j++){
			printf("%g\t",matriz[i][j]);
		}
		printf("\n");
	}
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
