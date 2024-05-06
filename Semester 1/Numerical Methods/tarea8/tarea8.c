/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 8 Cabecera**********/
/***********Metodos Numericos**********/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea8.h"

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

//Subrutina para solcuion de ecuaciones lineales a traves del metodo de gradiente conjuagdo
double *gradienteConjugado(double **matriz, double *vector, int sz, double TOL){
	int iter = 5*sz; 
	//Se define el vector inicial
	double *x0 = (double *)calloc(sz, sizeof(double));
	//Se define el residuo inicial
	double *r0 = (double *)calloc(sz, sizeof(double));
	//Se define P
	double *p0 = (double *)calloc(sz, sizeof(double));
	//Auxiliares
	double *w0, norma_p2, alpha, beta;
	//Se define un vector viejo
	double *x_viejo = (double *)calloc(sz, sizeof(double));


	//Inicializacion
	for(int i=0; i<sz; i++){
		r0[i] = vector[i];
		p0[i] = vector[i];
	}

	//Iniciamos el bucle
	int count = 0;
	while(count < iter){
		//Se calcula el producto matriz vector
		if(count > 0) free(w0);
		w0 = mult_matxvec(matriz, p0, sz);

		//Se obtiene la perturbacion
		norma_p2 = sqrt(mult_vecxvec(p0, p0, sz));
		alpha = norma_p2 / mult_vecxvec(p0, w0, sz);

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
		if(norma_tol(x0, x_viejo, sz)<TOL){
			printf("El metodo convergio tras %d iteraciones.\n", count+1);
			break;
		}

		//Calculamos la perturbacion para P
		beta = mult_vecxvec(p0, r0, sz) / norma_p2;

		//Se actualiza P
		for(int i=0; i<sz; i++){
			p0[i] = r0[i] - (beta * p0[i]);
		}

		//Se incrementa el contador
		count++;
	}
	if(count == iter) printf("El algoritmo no convergio tras %d iteraciones.\n", count);
	//Liberando la memoria
	free(r0);
	free(p0);
	free(w0);
	free(x_viejo);
	return x0;
}

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

//Subrutina del metodo de rayleigh para aproximacion de eigenvalores
Eigenv *rayleigh(double **matriz, int sz, double TOL, int NMax){
	//Inicializamos el vector semilla
	double *x0 = (double *)calloc(sz, sizeof(double));
	if(x0 ==NULL){
		printf("Error de asignacion de memoria.\n");
		return 0;
	}
	//Inicializando
	for(int i=0; i< sz; i++) x0[i] = 1.0;
	//Definimos sigma
	double sigma;
	//Reservamos espacio para la matriz
	double **matrizB = genMatriz(sz, sz);
	if(matrizB == NULL){
		free(x0);
		return 0;
	}
	//Declaramos el vector x de la siguiente iteracion
	double *x;
	//Declaramos la norma del vector
	double norm;
	//Declaramos un auxiliar
	double *res, *mult;

	//Iniciamos el bucle
	int count = 0;
	while(count <NMax){
		//Se calcula sigma
		mult = mult_matxvec(matriz, x0, sz);
		sigma = mult_vecxvec(x0, mult, sz);
		free(mult);

		//Obtenemos la matriz B
		for(int i=0; i<sz; i++){
			for(int j=0; j<sz; j++){
				matrizB[i][j] = matriz[i][j];
				if(i == j) matrizB[i][j] -= sigma;
			}
		}

		//Se obtiene el nuevo vector
		x = solver_lu(matrizB, x0, sz); //Factorizacion crout

		//Se nromaliza el vector
		norm = sqrt(mult_vecxvec(x, x, sz));
		for(int i=0; i<sz; i++) x[i] /= norm;

		//Se verifica la tolerancia
		res = rest_vec(x, x0, sz);
		if(mult_vecxvec(res, res, sz)<TOL){
			printf("El metodo convergio tras %d iteraciones.\n", count+1);
			break;
		}

		//Reasignamos valores
		for(int i=0; i<sz; i++) x0[i]=x[i];
		free(x);
		free(res);
		count++;
	}

	//Asignamos los valores
	Eigenv *sol = (Eigenv *)malloc(sizeof(Eigenv));
	sol->lambda = sigma;
	sol->vector = x;
	//Liberando la memoria
	free(matrizB[0]); //Memoria contigua
	free(matrizB);
	free(res);
	free(x0);

	return sol;
}

//Subrutina para aproximacion de eigenvalores por el metodo de iteracion de subespacio
Eigenv *subspace(double **matriz, int req, int sz, double TOL, int NMax){
	//Se define un vector inicial para obtener la matriz phi del metodo de la potencia inversa
	double **x0 = genMatriz(req, sz);
	//Se inicializa en 1's
	for(int i=0; i<req; i++){
		for(int j=0; j< sz; j++) x0[i][j] = 1.0;
	} 
	//Se define la matriz Phi
	double **tphi = (double **)malloc(sz * sizeof(double *));
	//Se define un auxiliar
	Eigenv *eigenp;
	//Matriz auxiliar
	double **prod, **Phi, **Q, max=0, *res;
	double *dq1 = (double *)calloc(req, sizeof(double));
	double *dq2 = (double *)calloc(req, sizeof(double));
	double *dq2v = (double *)calloc(req, sizeof(double));
	double **R = (double **)malloc(req * sizeof(double *));
	double **a1;
	Eigenv *sol = (Eigenv *)malloc(req*sizeof(Eigenv));

	//Obtenemos tantos eigenvectores como se solicita
	eigenp = potencia_inv(matriz, x0, &req, sz, TOL,1);
	//Se construye la matriz
	for(int i=0; i< req; i++) tphi[i] = eigenp[i].vector;
	//Se obtiene el valor de Q
	Phi = trans_mat(tphi, req, sz);

	//Se inicia el ciclo
	int count=0;
	while(count < NMax){
		//Obtenemos tantos eigenvectores como se solicita
		eigenp = potencia_inv(matriz, tphi, &req, sz, TOL, 3);
		//Se construye la matriz
		for(int i=0; i< req; i++) tphi[i] = eigenp[i].vector;
		//Se obtiene el valor de Q
		Phi = trans_mat(tphi, req, sz);
		//imprimirMatriz(Phi, sz, req);
		prod = mult_matxmat(tphi, matriz, req, sz, sz);
		Q = mult_matxmat(prod, Phi, req, sz, req);

		//Se obtiene la diagonal de la matriz Q
		for(int i=0; i<req; i++) dq1[i] = Q[i][i];

		//Verificamos si Q es diagonal
		max =0;
		for(int i=0; i<req; i++){
			for(int j=i+1; j<req; j++){
				if(fabs(Q[i][j])>fabs(max)) max = Q[i][j];
			}
		}
		if(fabs(max)<TOL){
			printf("(01) ");
			break;
		} 

		//Aplicamos jacobi
		eigen_jacobi(Q, R, req, TOL, 3);
		for(int i=0; i<req; i++) dq2[i]=Q[i][i];

		//Verificamos la tolerancia
		res = rest_vec(dq2v, dq2, req);
		if(norma_tol(dq2, dq2v, req)<TOL){
			for(int i=0; i<req; i++) dq1[i]=dq2[i];
			printf("(02) ");
			break;
		}
		a1 = mult_matxmat(Phi, R, sz, req, req);
		for(int i=0; i<sz; i++){
			for(int j=0; j<req; j++) Phi[i][j] = a1[i][j];
		}
		free(tphi[0]);
		free(tphi);
		tphi = trans_mat(Phi, sz, req);
		for(int i=0; i<req; i++) dq2v[i]=dq2[i];
		for(int i=0; i<req; i++) dq1[i]=dq2[i];

		count++;
	}
	printf("Se encontro la solucion tras %d iteraciones.\n", count+1);
	for(int i=0; i<req; i++){
		sol[i].lambda = dq1[i];
		sol[i].vector = Phi[i];

	}


	return sol;
}

//Metodo de la potencia inversa
Eigenv *potencia_inv(double **matriz, double **x00, int *z, int sz, double TOL, int NMax){
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
    double lambda;
	double *temp = (double *)calloc(sz, sizeof(double));

	//Factorizamos la matriz
	double **LU = fact_LuCrout(matriz, sz);

	//Creamos un ciclo para obetener los n mayores eigenvalores
	for(int k=0; k<*z; k++){
		//Creamos una copia del vector inical
		for(int i=0; i<sz; i++) x0[i] = x00[k][i];
		while(n<NMax){
			/*Se le quita al vector las componentes que ya se han encontrado*/
			for(int y=0; y<k; y++){
				//Calculando el vector a restar
				alpha = mult_vecxvec(sol[y].vector, x0, sz);
				for(int c=0; c<sz; c++) temp[c] = alpha*sol[y].vector[c];
				x0 = rest_vec(x0, temp, sz);
			}
			//Resolvemos el problema de Ax_k+1=x_k
			w0 = solver_lu(LU, x0, sz);

			//Normalizamos el vector
			nw0 = mult_vecxvec(w0,w0, sz);
			nw0=sqrt(nw0);
			for(int i=0; i<sz; i++) w0[i]/=nw0;

			//Se obtiene el eigenvalor
			lambda = mult_vecxvec(w0, mult_matxvec(matriz, w0, sz), sz);

			//Verificamos la convergencia
			//SIn convergencia
			//printf("La solucion del %d eigenvalor se encontro tras %d iteraciones.\n",k+1,n);
			sol[k].lambda = lambda;
			for(int d=0; d<sz; d++) sol[k].vector[d] = w0[d];
			break;

			//Actualizamos los valores
			for(int p=0; p<sz; p++) x0[p]=w0[p];
			n++;
    	}
		// if(n==NMax){
		// 	printf("El algoritmo no convergio para el %d eigenvalor tras %d iteraciones.\n", k+1, NMax);
		// 	*z = k;
		// 	return sol;
		// }
	}
	free(temp);
	free(x0);
	free(w0);
    return sol;
}

//Metodo de Jacobi para eigenvalores
Eigenv *eigen_jacobi(double **matriz, double **rep, int sz, double TOL, int NMax){
	
	/*Definimos el espacio donde se va a guardar la solucion*/
	Eigenv *sol = (Eigenv *)malloc(sz * sizeof(Eigenv));
	/*Definimos el espacio para la matriz donde se tendran los eigenvectores*/
	//double **rep = (double **)malloc(sz * sizeof(double *));
	/*Se define el espacio para la matriz de rotacion*/
	double **rot = (double **)malloc(sz * sizeof(double *));

	for(int i=0; i<sz; i++){
		sol[i].vector = (double *)calloc(sz, sizeof(double));
		rep[i] = (double *)calloc(sz, sizeof(double));
		rot[i] = (double *)calloc(sz, sizeof(double));
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
		temp = mult_matxmat(rot, matriz, sz, sz, sz);

		//Se tiene la matriz de rotacion sin trasponer
		for(int i=0; i<sz; i++){
			for(int j=i+1; j<sz; j++){
				rot[i][j] = -rot[i][j];
				rot[j][i] = -rot[j][i];
			}
		}

		temp1 = mult_matxmat(temp, rot, sz, sz, sz);

		//Actualizamos el vector de respuesta
		temp2 = mult_matxmat(rep, rot, sz, sz, sz);

		//Liberamos la memoria que ha sido creada
			free(temp[0]); //mem conigua
			free(matriz[0]); //mem conigua
			free(rep[0]); //mem conigua
		for(int i=0; i<sz; i++){
			//Actualizando los valores
			matriz[i] = temp1[i];
			rep[i] = temp2[i];

		}
		n++;
	}

	//Si la convergencia se alcanza llenamos la solcion
	//printf("La convergencia se encontro tras %d iteraciones.\n", n);
	for(int i=0; i<sz; i++){
		sol[i].lambda = matriz[i][i];
		for(int j=0; j<sz; j++){
			sol[i].vector[j] = rep[j][i];
		}
	}
	//Liberando espacio
	//free(temp[0]);
	free(temp);
	//free(temp1[0]);
	free(temp1);
	//free(temp2[0]);
	free(temp2);
	//free_mat(rep, sz);
	free_mat(rot, sz);
	
	return sol;
}

double *solver_lu(double **matriz, double *vectorb, int sz){

	//factorizamos la matriz
	double **LU;
	LU=fact_LuCrout(matriz, sz);

	//Resolvemos Ly=b
	double *y = lSolve(LU, vectorb, sz);

	//Resolvemos Ux=y
	double *x = uSolve(LU, y, sz);

	//liberando memoria
	free(LU[0]); //Memoria contigua
	free(LU);
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
			if(fabs(LU[i][i])<0.00000000001){
				printf("Valor cercano a 0 (LU 1).\n");
				free(LU[0]); //Memoria contigua
				free(LU);
				return NULL;
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
	if(fabs(matriz[0][0])<0.00000000001){
		printf("Valor cercano a 0 (lSsolve 1).\n");
		free(X);
		return NULL;
	}
    X[0] = vec[0]/matriz[0][0];

    // Recorremos para los valores de cada renglon
    for (int i = 1; i < sz; i++) {
        temp = 0.0;
        // Obtenemos la parte a restar
        for (int j = 0; j < i; j++) {
            temp += matriz[i][j] * X[j];
        }
        // Asignamos el valor
		if(fabs(matriz[0][0])<0.00000000001){
			printf("Valor cercano a 0 (lSolve 2).\n");
			free(X);
			return NULL;
		}
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

//Subrutina para calcular la norma propuesta
double norma_tol(double *x, double *x0, int sz){
	//Obtenemos la norma de la resta de vectores
	double *res = rest_vec(x, x0, sz);
	//Se obtiene la norma
	double norma = sqrt(mult_vecxvec(res, res, sz));
	//Se obtiene la norma del vector actual
	norma /= sqrt(mult_vecxvec(x, x, sz));
	//Liberando la memoria
	free(res);
	return norma;
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

//Subrutina para liberar la estructura de Factor
void free_factor(Factor *sol){
	free(sol->Left[0]); //Memoria contigua
	free(sol->Left);
	free(sol->Right[0]); //Memoria contigua
	free(sol->Right);
	free(sol);
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
