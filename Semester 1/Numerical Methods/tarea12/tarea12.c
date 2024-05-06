/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 12 Cabecera*********/
/***********Metodos Numericos**********/
/**************12/11/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tarea12.h"

//Rutina para derivada hacia delante
double fw_diff(double fx, double fh, double h){
    return (fh-fx)/h;
}

//Rutina para derivada hacia atras
double bw_diff(double fh, double fx, double h){
    return (fx-fh)/h;
}

//Rutina para derivada centrada
double ct_diff(double fd, double fu, double h){
    return (fu-fd)/(2.0*h);
}

//Rutina para derivada de 3 puntos hacia adelante
double three_endp_diff(double fx, double fh1, double fh2, double h){
    return (1.0/(2*h)) * ((-3.0 * fx) + (4.0*fh1) - fh2); 
}

//Rutina para derivada de 3 puntos centrada
double three_midp_diff(double fd, double fu, double h){
    return (fu-fd)/(2.0*h);
}

//Rutina para derivada de 5 puntos centrada
double five_midp_diff(double fd2, double fd1, double fu1, double fu2, double h){
    return (1.0/(12.0*h)) * (fd2 - (8.0 * fd1) + (8.0*fu1) - fu2); 
}

//Rutina para derivada de 5 puntos hacia adelante
double five_endp_diff(double fx, double fh1, double fh2, double fh3, double fh4, double h){
    return (1.0/(12.0*h)) * ((-25.0 * fx) + (48.0 * fh1) + \
    (-36.0*fh2) + (16.0*fh3) + (-3.0*fh4)); 
}

//Segunda derivada por punto fijo
double midp_secdiff(double fd, double fx, double fu, double h){
    return (1.0/(h*h)) * (fd + (-2*fx) + fu);
}

//Rutina para calcular el jacobiano de una funcion
double **jacobian_matrix(double (**f)(double *), double *x, double h, int sz){
    //Comenzamos por generar el espacio donde se guardara la matriz
    double **sol = genMatriz(sz, sz);
    double fd, fu, temp;
    //Comenzamos el bucle para rellenear la matriz
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++){
            //Se toma la iesima funcion, se evaluan los puntos y se calcula su derivada
            x[j]-=h;
            fd = f[i](x);
            x[j]+=(2*h);
            fu = f[i](x);
            x[j]-=h;
            //Se obtiene la derivada
            temp = ct_diff(fd, fu, h);
            //Se escribe en la matriz
            sol[i][j] = temp;
        }
    }
    return sol;
}

//Rutina para calcular el jacobiano de una funcion
double **hessian_matrix(double (**f)(double *), double *x, double h, int sz){
    //Comenzamos por generar el espacio donde se guardara la matriz
    double **sol = genMatriz(sz, sz);
    double fdi, fdj, fui, fuj;
    //Comenzamos el bucle para rellenear la matriz
    for(int i=0; i<sz; i++){
        for(int j=0; j<sz; j++){
            //Se toma la iesima funcion, se evaluan los puntos y se calcula su derivada
            fdj = f[i](x);

            x[j]+=h;
            fuj = f[i](x);
            x[j]-=h;

            x[i]+=h;
            fui = f[i](x);
            x[i]-=h;

            x[j]+=h;
            x[i]+=h;
            fdi = f[i](x);
            x[j]-=h;
            x[i]-=h;

            sol[i][j] = (1.0/(h*h)) * (fdi+fdj-fui-fuj);
        }
    }
    return sol;
}

//Rutina para sistemas de ecuaciones no lineales por punto fijo
double *fixedPoint_nonLinear(double *(*f)(double *), double *x0, int sz, double TOL, int nMax){
    //Se comienza el bucle
    int i=0;
    double *x;
    while(i<nMax){
        //Evaluamos el punto en la funcion
        if(i>0) free(x);
        x = f(x0);
        //Se verifica la tolerancia
        if(inf_norm(x0, x, sz)<TOL) break;
        //Si no se cumple la rutina se reasigna x0
        for(int j=0; j<sz; j++) x0[j] = x[j];
        i++;
    }
    if(i>=nMax) printf("No se alcanzo la convergencia tras %d iteraciones\n", i);
    else printf("El programafinalizo tras %d iteraciones\n", i);

    return x;
}

double *newton_sys(double (**f)(double *), double *x0, double h, int sz, double TOL, int nMax){
    //Se genera espacio para el vector
    double *b = (double *)calloc(sz, sizeof(double));
    double **A, *x;
    Factor *qr;
    double **qt;
    double *b1;
    
    //Se genera el bucle
    int i=0;
    while(i<nMax){
        //Se rellena el vector
        for(int j=0; j<sz; j++) b[j] = -f[j](x0);

        //Se obtiene la matriz Jacobiana
        A = jacobian_matrix(f, x0, h, sz);

        //Se resuelve el sistema de ecuaciones
        qr = QR(A, sz);
        qt = trans_mat(qr->Left, sz, sz);
        b1 = mult_matxvec(qt, b, sz, sz);
        x = uSolve(qr->Right, b1, sz);

        //Se actualiza el punto
        for(int j=0; j<sz; j++) x0[j] += x[j];

        //Se verifica la tolerancia
        if(sqrt(mult_vecxvec(x, x, sz))<TOL) break;

        free(x);
        free(b1);
        free(A[0]); //Memoria contigua
        free(A);
        free(qt[0]); //Memoria contigua
        free(qt);
        free_factor(qr);

        i++;
    }
    if(i>=nMax) printf("No se alcanzo la convergencia tras %d iteraciones\n", i);
    else printf("El programafinalizo tras %d iteraciones\n", ++i);
    
    return x0;
}

double *broyden_sys(double (**f)(double *), double *x0, double h, int sz, double TOL, int nMax){
    double **A0 = jacobian_matrix(f, x0, h, sz);
    print_mat(A0, "jac.txt", sz, sz);
    double *v = (double *)calloc(sz, sizeof(double));
    double *s, *z, *u, p;
    double *xn = (double *)calloc(sz, sizeof(double));
    double *w = (double *)calloc(sz, sizeof(double));
    double *y= (double *)calloc(sz, sizeof(double));
    double *temp= (double *)calloc(sz, sizeof(double));

    //Se obtiene la inversa 
    double **A_inv = inverseMatrix(A0, sz);
    print_mat(A_inv, "inv.txt", sz, sz);

    for(int i=0; i<sz; i++) v[i] = f[i](x0);
    s = mult_matxvec(A_inv, v, sz, sz);
    for(int i=0; i<sz; i++){
        s[i] *= -1.0;
        xn[i] = x0[i] + s[i];
    }

    int k=1;
    while(k<nMax){
        for(int i=0; i<sz; i++){
            w[i] = v[i];
            v[i] = f[i](xn);
            y[i] = v[i] - w[i];
        }

        z = mult_matxvec(A_inv, y, sz, sz);
        for(int i=0; i<sz; i++) z[i] *=-1.0;
        p = -1.0*mult_vecxvec(s, z, sz);
        u = mult_vecxmat(A_inv, s, sz, sz);
        for(int i=0; i<sz; i++) temp[i] = s[i] + z[i];

        for(int i=0; i<sz; i++){
            for(int j=0; j<sz; j++){
                A_inv[i][j] += (1.0/p) * (temp[i] * u[j]);
            }
        }

        free(s);
        s = mult_matxvec(A_inv, v, sz, sz);
        for(int i=0; i<sz; i++){
            s[i] *= -1.0;
            xn[i] += s[i];
        }

        if(sqrt(mult_vecxvec(s, s, sz))<TOL) break;
        k++;
    }
    if(k>=nMax) printf("No se alcanzo la convergencia tras %d iteraciones\n", k);
    else printf("El programafinalizo tras %d iteraciones\n", ++k);
    
    return xn;
}

double *cg_Freeves(double (**f)(double *), double *x0, double dh, int sz, double TOL, int nMax){
    double *z, z0, **j, **jt, g0, gv0;
    double a[4], g[4], h[3], gv[4], gmin;
    double *temp = (double *)calloc(sz, sizeof(double));
    double *zv = (double *)calloc(sz, sizeof(double));
    int y;
    
    int k=0;
    while(k<nMax){
        j = jacobian_matrix(f, x0, dh, sz);
        jt = trans_mat(j, sz, sz);
        for(int i=0; i<sz; i++) temp[i] = 2*f[i](x0);
        z = mult_matxvec(jt, temp, sz, sz);
        if(k>0){
            g0 = mult_vecxvec(g, g, sz);
            gv0 = mult_vecxvec(gv, gv, sz);
            for(int i=0; i<sz; i++) z[i] += (g0/gv0) * zv[i];
        }
        g[1] = 0.0;
        for(int i=0; i<sz; i++) g[1] += f[i](x0)*f[i](x0);
        z0 = sqrt(mult_vecxvec(z,z, sz));
        if(fabs(z0)<1e-12){
            printf("Gradiente 0\n");
            break;
        }
        for(int i=0; i<sz; i++) z[i] /= z0;
        a[1] = 0.0;
        a[3] = 1.0;
        for(int i=0; i<sz; i++) temp[i] = x0[i] - (a[3]*z[i]);
        g[3] = 0.0;
        for(int i=0; i<sz; i++) g[3] += f[i](temp)*f[i](temp);
        while(g[3]>=g[1]){
            a[3] /= 2.0;
            for(int i=0; i<sz; i++) temp[i] = x0[i] - (a[3]*z[i]);
            g[3] = 0.0;
            for(int i=0; i<sz; i++) g[3] += f[i](temp)*f[i](temp);
        }

        if(a[3]<1e-12/2){
            printf("No hay mejora\n");
            break;
        }

        a[2] = a[3]/2.0;
        for(int i=0; i<sz; i++) temp[i] = x0[i] - (a[2]*z[i]);
        g[2] = 0.0;
        for(int i=0; i<sz; i++) g[2] += f[i](temp)*f[i](temp);
        h[0] = (g[2] - g[1])/a[2];
        h[1] = (g[3] - g[2])/(a[3] - a[2]);
        h[2] = (h[1] - h[0])/a[3];
        a[0] = 0.5 * (a[2] - (h[0]/h[2]));

        for(int i=0; i<sz; i++) temp[i] = x0[i] - (a[0]*z[i]);
        g[0] = 0.0;
        for(int i=0; i<sz; i++) g[0] += f[i](temp)*f[i](temp);

        y=0;
        gmin = g[0];
        for(int i=0; i<4; i++){
          if(g[i]<gmin){
            gmin=g[i];
            y = i;
          }
        }
        for(int i=0; i<sz; i++) x0[i] -= a[y]*z[i];
        if(fabs(gmin-g[1])<TOL) break;
        for(int i=0; i<4; i++){
            gv[i] = g[i];
            zv[i] = z[i];
        } 
        k++;
    }
    if(k>=nMax) printf("No se alcanzo la convergencia tras %d iteraciones\n", k);
    else printf("El programafinalizo tras %d iteraciones\n", ++k);

    free(j[0]); //Memoria contigua
    free(jt[0]); //Memoria contigua
    free(j);
    free(jt);
    free(z);
    free(temp);

    return x0;
}

double *gradiente(double (**f)(double *), double *x, double h, int sz){
    double *sol = (double *)calloc(sz, sizeof(double));
    double fd, fu;
    for(int i=0; i<sz; i++){
        x[i] -= h;
        fd = f[i](x);
        x[i] += 2.0*h;
        fu = f[i](x);
        x[i] -= h;
        sol[i] = ct_diff(fd, fu, h);
    }

    return sol;
}

//Subrutina para calcular la norma infinita
double inf_norm(double *r1, double *r2, int sz){
    //Se verifica cual es la diferencia mas grande y se retorna
    double res = 0.0;
    for(int i=0; i<sz; i++){
        if(fabs(r1[i]-r2[i])>res) res = fabs(r1[i]-r2[i]);
    }
    return res;
}

// Funcion para realizar pivoteo parcial y encontrar la inversa
double **gauss_parc_inversa(double **matriz, int sz){
    // Definimos el espacio donde se guarda la solución (inversa)
    double **inversa = genMatriz(sz, sz);

    // Inicializamos la matriz inversa como la matriz identidad
    for(int i=0; i<sz; i++) inversa[i][i] = 1.0;

    // Definimos el multiplicador
    double m = 0.0;

    // Comenzamos con el proceso de eliminacion
    for (int i = 0; i < sz; i++) {
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
        if (filaPivote != i) {
            temp = matriz[i];
            matriz[i] = matriz[filaPivote];
            matriz[filaPivote] = temp;

            temp = inversa[i];
            inversa[i] = inversa[filaPivote];
            inversa[filaPivote] = temp;
        }

        // Escalar la fila para tener un pivote de 1
        double pivotValue = matriz[i][i];
        for (int j = i; j < sz; j++) {
            matriz[i][j] /= pivotValue;
            inversa[i][j] /= pivotValue;
        }

        // Eliminacion hacia abajo
        for (int j = i + 1; j < sz; j++) {
            m = matriz[j][i];
            for (int k = i; k < sz; k++) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }

    // Eliminacion hacia arriba
    for (int i = sz - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            m = matriz[j][i];
            for (int k = i; k >= 0; k--) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }

    return inversa;
}

// Función para calcular la inversa de una matriz
double **inverseMatrix(double **matriz, int sz){
    // Crear la matriz identidad
    // Definimos el espacio donde se guarda la solucion (inversa)
    double **inversa = genMatriz(sz, sz);

    // Inicializamos la matriz inversa como la matriz identidad
    for(int i=0; i<sz; i++) inversa[i][i] = 1.0;

    // Comenzar con el proceso de eliminacion
    for (int i = 0; i < sz; i++) {
        // Encontrar el pivote parcial
        double maxPivote = fabs(matriz[i][i]);
        int filaPivote = i;

        for (int k = i + 1; k < sz; k++) {
            if (fabs(matriz[k][i]) > maxPivote) {
                maxPivote = fabs(matriz[k][i]);
                filaPivote = k;
            }
        }

        // Intercambiar filas si es necesario (pivoteo parcial)
        if (filaPivote != i) {
            double *temp = matriz[i];
            matriz[i] = matriz[filaPivote];
            matriz[filaPivote] = temp;

            temp = inversa[i];
            inversa[i] = inversa[filaPivote];
            inversa[filaPivote] = temp;
        }

        // Escalar la fila para tener un pivote de 1
        double pivotValue = matriz[i][i];
        for (int j = 0; j < sz; j++) {
            matriz[i][j] /= pivotValue;
            inversa[i][j] /= pivotValue;
        }

        // Eliminacion hacia abajo
        for (int j = i + 1; j < sz; j++) {
            double m = matriz[j][i];
            for (int k = 0; k < sz; k++) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }

    // Eliminacion hacia arriba
    for (int i = sz - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double m = matriz[j][i];
            for (int k = 0; k < sz; k++) {
                matriz[j][k] -= m * matriz[i][k];
                inversa[j][k] -= m * inversa[i][k];
            }
        }
    }

    return inversa;
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

//Subrutina para multiplicar una matriz por un vector
double *mult_vecxmat(double **matriz, double *vector, int nRows, int nCols){
	//Reservamos espacio
	double *x=(double *)calloc(nRows, sizeof(double));

	double temp=0;
	for(int i=0; i<nRows; i++){
		temp=0;
		for(int j=0; j<nCols; j++){
			temp+=matriz[j][i]*vector[i];
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
    fclose(file);
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
