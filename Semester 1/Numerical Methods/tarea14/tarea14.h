/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/**********Tarea 14 Cabecera***********/
/**********Metodos Numericos***********/
/**************01/12/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA14_H
#define TAREA14_H

double **theta_method(double u0(double), double theta, double T, double a, double b, double alpha, int n, int m);
double *solver_lu(double **matriz, double *vectorb, int sz, int o);
double **fact_Cholesky(double **matriz, int sz);
double **fact_LuCrout(double **matriz, int sz);
double *lSolve(double **matriz, double *vec, int sz);
double *uSolve(double **matriz, double *vec, int sz);
double *mult_matxvec(double **matriz, double *vector, int nRows, int nCols);
double **genMatriz(int nRows, int nCols);
double **genMatriz3d(int sz);
void print_mat(double **matriz, char *name, int nRows, int nCols);
void free_mat(double **matriz, int sz);

#endif