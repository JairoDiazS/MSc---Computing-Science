/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 11 Cabecera*********/
/***********Metodos Numericos**********/
/**************05/11/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA11_H
#define TAREA11_H

typedef struct descomposicion{
    double **Left;
    double **Right;
} Factor;

double *least_sqr(double *x, double *y, double lambda, int sz, int k, int n, double (*function)(double, int));
double eval_exp(double *coef, double *x, double x0, int sz);
double eval_serie(double *coef, double x0, int sz, double (*function)(double, int));
double polinomial(double x, int n);
double trigonometrica(double x, int n);
double exponencial(double r, int n);
double *solver_lu(double **matriz, double *vectorb, int sz, int o);
double **fact_Cholesky(double **matriz, int sz);
double **fact_LuCrout(double **matriz, int sz);
Factor *QR(double **matriz, int sz);
double **GramS(double **matriz, int sz);
double *lSolve(double **matriz, double *vec, int sz);
double *uSolve(double **matriz, double *vec, int sz);
double **mult_matxmat(double **m1, double **m2, int nRows, int nEqs, int nCols);
double *mult_matxvec(double **matriz, double *vector, int nRows, int nCols);
double mult_vecxvec(double *v1, double *v2, int sz);
double **trans_mat(double **matriz, int nRows, int nCols);
double **genMatriz(int nRows, int nCols);
double *r_points(const char *fn, int *sz);
void print_mat(double **matriz, char *name, int nRows, int nCols);
void free_mat(double **matriz, int sz);
void free_factor(Factor *sol);

#endif

