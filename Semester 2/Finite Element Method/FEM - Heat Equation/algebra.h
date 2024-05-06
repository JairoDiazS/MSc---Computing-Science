/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/***************Algrebra***************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de algebra con programacion dinamica*/

#ifndef ALGEBRA_H
#define ALGEBRA_H

double **inverseMatrix(double ** inversa, double **matriz, int sz);
double **mult_matxmat(double **sol, double **m1, double **m2, int nRows, int nEqs, int nCols);
double **mult_matinvxmat(double **sol, double **m1, double **m2, int nRows, int nEqs, int nCols);
double detMatrix(double **Mat, int sz);
double mult_vecxvec(double *v1, double *v2, int sz);
double *mult_matxvec(double *x, double **matriz, double *vector, int nRows, int nCols);
double ** mult_vecfxvecc(double **sol, double *v1, double *v2, int nRows, int nCols);
double *rest_vec(double *v1, double *v2, int sz);

double norma_tol(double *x, double *x0, int sz);


#endif