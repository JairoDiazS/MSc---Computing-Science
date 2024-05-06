/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/***************Solvers****************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de Solvers con programacion dinamica*/

#include "solvers.h"
#include "tools.h"
#include "algebra.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void evalFForma(double *FForma, double *x0, int NDim, int NNode){
    if(NDim == 1){
        if(NNode == 2){
            FForma[0] = (1.0 - x0[0]) / 2.0;
            FForma[1] = (1.0 + x0[0]) / 2.0;
        }
        else if (NNode == 3){
            FForma[0] = ((x0[0]*x0[0]) - x0[0] ) / 2.0;
            FForma[1] = 1.0 - (x0[0]*x0[0]);
            FForma[2] = ((x0[0]*x0[0]) + x0[0] ) / 2.0;
        }
    }
    else if(NDim == 2){
        if(NNode == 3){
            FForma[0] = 1 - x0[0] - x0[1];
            FForma[1] = x0[0];
            FForma[2] = x0[1];
        }
        else if(NNode == 4){
            FForma[0] = (1-x0[0])*(1-x0[1])/4.0;
            FForma[1] = (1+x0[0])*(1-x0[1])/4.0;
            FForma[2] = (1+x0[0])*(1+x0[1])/4.0;
            FForma[3] = (1-x0[0])*(1+x0[1])/4.0;
        }
        else if(NNode == 6){
            double Li = 1.0 - x0[0] - x0[1];
            double Lj = x0[0];
            double Lk = x0[1];

            FForma[0] = Li - (2.0*Li*Lj) - (2.0*Li*Lk);
            FForma[2] = Lj - (2.0*Li*Lj) - (2.0*Lj*Lk);
            FForma[4] = Lk - (2.0*Li*Lk) - (2.0*Lj*Lk);
            FForma[1] = 4*Li*Lj;
            FForma[3] = 4*Lj*Lk;
            FForma[5] = 4*Lk*Li;
        }
		else if(NNode == 8){
			double Li1 = 1.0 - x0[0];
			double Lj1 = 1.0 + x0[0];
			double Lk1 = 1.0 - x0[1];
			double Ll1 = 1.0 + x0[1];
			double Li2 = 1.0 - (x0[0]*x0[0]);
			double Lk2 = 1.0 - (x0[1]*x0[1]);
			FForma[1] = Lk2*Li1/2.0;
			FForma[3] = Li2*Ll1/2.0;
			FForma[5] = Lk2*Lj1/2.0;
			FForma[7] = Li2*Lk1/2.0;
			FForma[0] = (Li1*Lk1/4.0) - ((FForma[7]+FForma[1])/2.0);
			FForma[2] = (Li1*Ll1/4.0) - ((FForma[1]+FForma[3])/2.0);
			FForma[4] = (Lj1*Ll1/4.0) - ((FForma[3]+FForma[5])/2.0);
			FForma[6] = (Lj1*Lk1/4.0) - ((FForma[5]+FForma[7])/2.0);
		}
		else if(NNode == 9){
			double rho[] = {-1.0, 0.0, 1.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0};
			double eta[] = {-1.0, -1.0, -1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0};

			for(int i=0; i<9; i++){
				switch(i){
					case 0:
					case 2:
					case 4:
					case 6:
						FForma[i] = ((x0[0]*x0[0]) + (x0[0]*rho[i]))*((x0[1]*x0[1]) + (x0[1]*eta[i]))/4.0;
						break;
					case 1:
					case 3:
					case 5:
					case 7:
						FForma[i] = (rho[i]*rho[i]*((x0[0]*x0[0]) - (x0[0]*rho[i]))*(1.0-(x0[1]*x0[1]))/2.0) + (eta[i]*eta[i]*((x0[1]*x0[1]) - (x0[1]*rho[i]))*(1.0-(x0[0]*x0[0]))/2.0);
						break;
					case 8:
						FForma[i] = (1.0 - (x0[0]*x0[0]))*(1.0 - (x0[1]*x0[1]));
						break;
				}
			}
		}
    }
	else if(NDim == 3){
		if(NNode == 4){
			FForma[0] = 1.0 - x0[0] - x0[1] - x0[2];
			FForma[1] = x0[0];
			FForma[2] = x0[1];
			FForma[3] = x0[2];
		}
	}
}

void evalDerive(double **Derive, double *x0, int NDim, int NNode){
    if(NDim == 1){
        if(NNode == 2){
            Derive[0][0] = -1.0 / 2.0;
            Derive[1][0] = 1.0 / 2.0;
        }
        else if (NNode == 3){
            Derive[0][0] = x0[0] - (1.0 / 2.0);
            Derive[1][0] = -2.0*x0[0];
            Derive[2][0] = x0[0] + (1.0 / 2.0);
        }
    }
    else if(NDim==2){
        if(NNode == 3){
            // Derivadas psi
            Derive[0][0] = -1.0;
            Derive[1][0] = 1.0;
            Derive[2][0] = 0.0;
            // Derrivadas eta
            Derive[0][1] = -1.0;
            Derive[1][1] = 0.0;
            Derive[2][1] = 1.0;
        }
        else if(NNode == 4){
            // Derivadas de psi
            Derive[0][0] = -(1-x0[1])/4.0;
            Derive[1][0] = (1-x0[1])/4.0;
            Derive[2][0] = (1+x0[1])/4.0;
            Derive[3][0] = -(1+x0[1])/4.0;
            // Derivadas eta
            Derive[0][1] = -(1-x0[0])/4.0;
            Derive[1][1] = -(1+x0[0])/4.0;
            Derive[2][1] = (1+x0[0])/4.0;
            Derive[3][1] = (1-x0[0])/4.0;
        }
        else if(NNode == 6){
            double Li = 1.0 - x0[0] - x0[1];
            double Lj = x0[0];
            double Lk = x0[1];

            //Derivadas de psi
			Derive[1][0] = 4*(Li - Lj);
			Derive[3][0] = 4*Lk;
			Derive[5][0] = -4*Lk;

            Derive[0][0] = -1.0 - ((Derive[1][0] + Derive[5][0])/2.0);
            Derive[2][0] = 1.0 - ((Derive[1][0] + Derive[3][0])/2.0);
            Derive[4][0] = 0.0;

            //Derivadas de eta
			Derive[1][1] = -4*Lj;
			Derive[3][1] = 4*Lj;
			Derive[5][1] = 4*(Li - Lk);
            
			Derive[0][1] = -1.0 - ((Derive[1][1] + Derive[5][1])/2.0);
			Derive[2][1] = 0.0;
			Derive[4][1] = 1.0 - ((Derive[3][1] + Derive[5][1])/2.0);
        }
		else if(NNode == 8){
			double Li1 = 1.0 - x0[0];
			double Lj1 = 1.0 + x0[0];
			double Lk1 = 1.0 - x0[1];
			double Ll1 = 1.0 + x0[1];
			double Li2 = 1.0 - (x0[0]*x0[0]);
			double Lk2 = 1.0 - (x0[1]*x0[1]);

			//Derivadas pares
			Derive[1][0] = -Lk2/2.0;
			Derive[1][1] = -x0[1] * Li1;
			Derive[3][0] = -x0[0] * Ll1;
			Derive[3][1] = -Li2/2.0;
			Derive[5][0] = Lk2/2.0;
			Derive[5][1] = -x0[1] * Lj1;
			Derive[7][0] = -x0[0] * Lk1;
			Derive[7][1] = Li2/2.0;

			//Derivadas impares
			Derive[0][0] = (-Lk1/4.0) - ((Derive[1][0] + Derive[7][0])/2.0);
			Derive[0][1] = (-Li1/4.0) - ((Derive[1][1] + Derive[7][1])/2.0);
			Derive[2][0] = (-Ll1/4.0) - ((Derive[1][0] + Derive[3][0])/2.0);
			Derive[2][1] = (Li1/4.0) -  ((Derive[1][1] + Derive[3][1])/2.0);
			Derive[4][0] = (Ll1/4.0) -  ((Derive[3][0] + Derive[5][0])/2.0);
			Derive[4][1] = (Lj1/4.0) -  ((Derive[3][1] + Derive[5][1])/2.0);
			Derive[5][0] = (Lk1/4.0) -  ((Derive[5][0] + Derive[7][0])/2.0);
			Derive[5][1] = (-Lj1/4.0) - ((Derive[5][1] + Derive[7][1])/2.0);
		}
		else if(NNode == 9){
			double rho[] = {-1.0, 0.0, 1.0, 1.0, 1.0, 0.0, -1.0, -1.0, 0.0};
			double eta[] = {-1.0, -1.0, -1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0};

			for(int i=0; i<9; i++){
				switch(i){
					case 0:
					case 2:
					case 4:
					case 6:
						Derive[i][0] = ((2.0*x0[0]) + rho[i])*((x0[1]*x0[1]) + (x0[1]*eta[i]))/4.0;
						Derive[i][1] = ((x0[0]*x0[0]) + (x0[0]*rho[i]))*((2.0*x0[1]) + (x0[1]*eta[i]))/4.0;
						break;
					case 1:
					case 3:
					case 5:
					case 7:
						Derive[i][0] = ((-x0[0]*eta[i]*eta[i])*((x0[1]*x0[1])-(x0[1]*eta[i]))) + (x0[0]*(1-(x0[1]*x0[1]))*((2*x0[0]*x0[0])-(x0[0]*rho[i])));
						Derive[i][1] = ((-x0[1]*rho[i]*rho[i])*((x0[0]*x0[0])-(x0[0]*rho[i]))) + (x0[1]*(1-(x0[0]*x0[0]))*((2*x0[1]*x0[1])-(x0[1]*eta[i])));
						break;
					case 8:
						Derive[i][0] = -2*x0[0]*(1.0 - (x0[1]*x0[1]));
						Derive[i][1] = -2*x0[1]*(1.0 - (x0[0]*x0[0]));
						break;
				}
			}
		}
    } 
	else if(NDim == 3){
		if(NNode == 4){
			Derive[0][0] = -1.0;
			Derive[0][1] = -1.0;
			Derive[0][2] = -1.0;
			Derive[1][0] = 1.0;
			Derive[1][1] = 0.0;
			Derive[1][2] = 0.0;
			Derive[2][0] = 0.0;
			Derive[2][1] = 1.0;
			Derive[2][2] = 0.0;
			Derive[3][0] = 0.0;
			Derive[3][1] = 0.0;
			Derive[3][2] = 1.0;
		}
	}
}

void evalJacobian(double **Jacobian, double **CoordEl, double **Derive, int NDim, int NNode){
    int i,j,k;
    for(i=0; i<NDim; i++){
        for(j=0; j<NDim; j++){
            double temp = 0.0;
            for(k=0; k<NNode; k++){
                temp += Derive[k][i] * CoordEl[k][j];
            }
            Jacobian[i][j] = temp;
        }
    }
}

void evalDeriveCart(double **BMat, double **invJacobian, double **Deriv, int NDim, int NNode){
    int i,j,k;
	double temp;
    for(i=0; i<NDim; i++){
        for(j=0; j<NNode; j++){
			temp = 0;
			for(k=0; k<NDim; k++){
				temp += Deriv[j][k] * invJacobian[i][k];
			}
            BMat[i][j] =  temp;
        }
    }
}

void get_NPointG(int NDim, int NNode, int *NPointG){
    if(NDim == 1){
        if(NNode == 2) *NPointG = 1;
        if(NNode == 3) *NPointG = 2;
    }
    else if(NDim == 2){
        if(NNode == 3) *NPointG = 1;
        if(NNode == 4) *NPointG = 4;
		if(NNode == 6) *NPointG = 7;
		if(NNode == 8) *NPointG = 8;
		if(NNode == 9) *NPointG = 9;
    }
	else if(NDim == 3){
		if(NNode == 4) *NPointG = 1;
	}
}

void Gauss(double **pGauss, double *wGauss, int NDim, int NNodes){
    if(NDim==1){
        if(NNodes==2){
            pGauss[0][0] = 0.0;
            wGauss[0] = 2.0;
        }
        else if (NNodes==3){
            pGauss[0][0] = sqrt(1.0/3.0);
            pGauss[1][0] = -sqrt(1.0/3.0);
            wGauss[0] = 1.0;
            wGauss[1] = 1.0;
        }
    }
    else if(NDim==2){
        if(NNodes==3){
            pGauss[0][0] = 1.0/3.0;
            pGauss[0][1] = 1.0/3.0;
            wGauss[0] = 1.0;
        }
        else if(NNodes==4){
            pGauss[0][0] = sqrt(1.0/3.0);
            pGauss[0][1] = sqrt(1.0/3.0);

            pGauss[1][0] = -sqrt(1.0/3.0);
            pGauss[1][1] = sqrt(1.0/3.0);

            pGauss[2][0] = -sqrt(1.0/3.0);
            pGauss[2][1] = -sqrt(1.0/3.0);

            pGauss[3][0] = sqrt(1.0/3.0);
            pGauss[3][1] = -sqrt(1.0/3.0);

            wGauss[0] = 1.0;
            wGauss[1] = 1.0;
            wGauss[2] = 1.0;
            wGauss[3] = 1.0;
        }
		else if(NNodes == 6){
			pGauss[0][0] = 0.5;
			pGauss[0][1] = 0.0;

			pGauss[1][0] = 0.0;
			pGauss[1][1] = 0.5;

			pGauss[2][0] = 0.5;
			pGauss[2][1] = 0.5;

			pGauss[3][0] = 1.0/6.0;
			pGauss[3][1] = 1.0/6.0;

			pGauss[4][0] = 2.0/3.0;
			pGauss[4][1] = 1.0/6.0;

			pGauss[5][0] = 1.0/6.0;
			pGauss[5][1] = 2.0/3.0;

			wGauss[0] = 1.0/6.0;
			wGauss[1] = 1.0/6.0;
			wGauss[2] = 1.0/6.0;
			wGauss[3] = 1.0/6.0;
			wGauss[4] = 1.0/6.0;
			wGauss[5] = 1.0/6.0;
		}
		else if(NNodes == 8){
			pGauss[3][0] = -sqrt(3.0/5.0);
			pGauss[3][1] = sqrt(3.0/5.0);

			pGauss[4][0] = 0.0;
			pGauss[4][1] = -sqrt(3.0/5.0);

			pGauss[5][0] = sqrt(3.0/5.0);
			pGauss[5][1] = 0.0;

			pGauss[6][0] = 0.0;
			pGauss[6][1] = sqrt(3.0/5.0);

			pGauss[7][0] = -sqrt(3.0/5.0);
			pGauss[7][1] = 0.0;

			wGauss[0] = 25.0/81.0;
			wGauss[1] = 25.0/81.0;
			wGauss[2] = 25.0/81.0;
			wGauss[3] = 25.0/81.0;
			wGauss[4] = 40.0/81.0;
			wGauss[5] = 40.0/81.0;
			wGauss[6] = 40.0/81.0;
			wGauss[7] = 40.0/81.0;
		}
		else if(NNodes == 9){
			pGauss[0][0] = -sqrt(3.0/5.0);
			pGauss[0][1] = -sqrt(3.0/5.0);

			pGauss[1][0] = sqrt(3.0/5.0);
			pGauss[1][1] = -sqrt(3.0/5.0);

			pGauss[2][0] = sqrt(3.0/5.0);
			pGauss[2][1] = sqrt(3.0/5.0);

			pGauss[3][0] = -sqrt(3.0/5.0);
			pGauss[3][1] = sqrt(3.0/5.0);

			pGauss[4][0] = 0.0;
			pGauss[4][1] = -sqrt(3.0/5.0);

			pGauss[5][0] = sqrt(3.0/5.0);
			pGauss[5][1] = 0.0;

			pGauss[6][0] = 0.0;
			pGauss[6][1] = sqrt(3.0/5.0);

			pGauss[7][0] = -sqrt(3.0/5.0);
			pGauss[7][1] = 0.0;

			pGauss[8][0] = 0.0;
			pGauss[8][1] = 0.0;

			wGauss[0] = 25.0/81.0;
			wGauss[1] = 25.0/81.0;
			wGauss[2] = 25.0/81.0;
			wGauss[3] = 25.0/81.0;
			wGauss[4] = 40.0/81.0;
			wGauss[5] = 40.0/81.0;
			wGauss[6] = 40.0/81.0;
			wGauss[7] = 40.0/81.0;
			wGauss[8] = 64.0/81.0;
		}
    }
	else if(NDim == 3){
		if(NNodes == 4){
			pGauss[0][0] = 0.25;
			pGauss[0][1] = 0.25;
			pGauss[0][2] = 0.25;

			wGauss[0] = 1.0/6.0;
		}
	}
}

//Subrutina para ensamblar la matriz de Rigidez
void ensamblarMatriz(double **K, double **ke, int i, int NNode, int** LNodes){
	//Se obtiene el vector de los nodos
	int *nodes = LNodes[i];
	//Obtenemos el tamanio de la ventana
	for(int i=0; i<NNode; i++){
		for(int j=0; j<NNode; j++){
			K[nodes[i]][nodes[j]] += ke[i][j];
		}
	}
}

//Ensamblar P
void ensamblarP(double **P, double **p_e, int i, int NDim, int** LNodes, int NNode){
	//Se obtiene el vector de los nodos
	int *nodes = LNodes[i];
	//
	for(int i=0; i<NNode; i++){
		for(int j=0; j<NDim; j++){
			P[nodes[i]][j] += p_e[i][j];
		}
	}
}

//Subrutina para ensamblar el vector de fuerza
void ensamblarVector(double *F, double *F_e, int i, int NNode, int** LNodes){
	//Se obtiene el vector de los nodos
	int *nodes = LNodes[i];
	//Obtenemos el tamanio de la ventana
	for(int i=0; i<NNode; i++){
			F[nodes[i]] += F_e[i];
	}
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
	freeMat_double(LU);
	free(y);

	return x;
}

//Factorizacion Cholesky
double **fact_Cholesky(double **matriz, int sz){

	//Reservamos el espacio para la solucion
	double **LLt=genMatrix(sz,sz);

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

//Subrutina para solcuion de ecuaciones lineales a traves del metodo de gradiente conjuagdo
double *gradienteConjugado(double **matriz, double *vector, int sz, double TOL){
	int iter = 5*sz; 
	//Se define el vector inicial
	double *x0 = (double *)calloc(sz, sizeof(double));
	//Se define el residuo inicial
	double *r0 = (double *)calloc(sz, sizeof(double));
	//Se define P
	double *p0 = (double *)calloc(sz, sizeof(double));

	double *w0 = (double *)calloc(sz, sizeof(double));
	//Auxiliares
	double norma_p2, alpha, beta;
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
		mult_matxvec(w0, matriz, p0, sz, sz);
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
double *gradienteJacobi(double **matriz, double *vector, int sz, double TOL, int NMax){
	//Se define el maximo de iteraciones
	int iter = NMax;
	//Se define el vector inicial
	double *x0 = (double *)calloc(sz, sizeof(double));
	//Se define el residuo inicial
	double *r0 = (double *)calloc(sz, sizeof(double));
	//Se define P
	double *p0 = (double *)calloc(sz, sizeof(double));
	double *w0 = (double *)calloc(sz, sizeof(double));
	//Auxiliares
	double alpha, beta;
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
			break;
		}
		M[i] = 1/matriz[i][i];
		y0[i] = M[i]*vector[i];
		p0[i] = -y0[i];
	}

	//Iniciamos el bucle
	while(count < iter){
		//Se calcula el producto matriz vector
		mult_matxvec(w0, matriz, p0, sz, sz);

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

void solver_flux_sys(double **sol, double **M, double **P, int NPoints, int NDim){
	//Se va a resolver un sistema de ecuaciones

	//Creamos un vector que almacena las columnas de P
	double *vcol = genVector(NPoints);
	double *solc;
	//Creamos un ciclo sobre el numero de dimensiones
	for(int i =0; i<NDim; i++){
		//Asignamos el vector por cada columna de P
		for(int j=0; j<NPoints; j++) vcol[j] = P[j][i];
		//Resolvemos el sistema de ecuaciones
		solc = gradienteJacobi(M, vcol, NPoints, 1E-8, 1E6);
		//Asignamos la solucion
		for(int j=0; j<NPoints; j++) sol[j][i] = solc[j];
		//Liberamos la memoria
		free(solc);
	}
	free(vcol);
}
