/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/***************Solvers****************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de Solvers con programacion dinamica para Metodo de elemento finito*/

#ifndef SOLVERS_H
#define SOLVERS_H

//Elemento finito
void evalFForma(double *FForma, double *x0, int NDim, int NNode);   //Evalua las funciones de forma
void evalDerive(double **Derive, double *x0, int NDim, int NNode);  //Evalua las derivadas de ls FF en el espacio normalizado
void evalJacobian(double **Jacobian, double **CoordEl, double **Derive, int NDim, int NNode);   //Obtiene el jacobiano de transformacion
void evalDeriveCart(double **BMat, double **invJacobian, double **Deriv, int NDim, int NNode);  //Obtiene las derivadas de las FF en el espacio Cartesiano
void get_NPointG(int NDim, int NNode, int *NPointG);    //Define el numero de puntos
void Gauss(double **pGauss, double *wGauss, int NDim, int NNodes);  //Obtiene los valores de los puntos y los pesos de gauss
void ensamblarMatriz(double **K, double **ke, int i, int NNode, int** LNodes);  //Ensamble de la matriz de Rigidez
void ensamblarVector(double *F, double *F_e, int i, int NNode, int** LNodes);   //Ensamble del vector de fuerzas
void ensamblarP(double **P, double **p_e, int i, int NDim, int** LNodes, int NNode);
void solver_flux_sys(double **sol, double **M, double **P, int NPoints, int NDim);

//Resolcuion de Sistemas de ecuaciones
double *solver_lu(double **matriz, double *vectorb, int sz, int o); //Solver de Descomposicion LU
double **fact_Cholesky(double **matriz, int sz);    //Factorizacion Chloesky de una matriz Cuadrada LLt
double **fact_LuCrout(double **matriz, int sz);     //Factorizacion LU Crout
double *lSolve(double **matriz, double *vec, int sz);   //Resolver sistema triangular inferior
double *uSolve(double **matriz, double *vec, int sz);   //Resolver sistema triangular superior
double *gradienteConjugado(double **matriz, double *vector, int sz, double TOL);    //Sistema de ecuaciones por gradiente conjugado.
double *gradienteJacobi(double **matriz, double *vector, int sz, double TOL, int NMax); //Sistema de ecuaciones por gradiente conjugado con precondicionador Jacobi

#endif