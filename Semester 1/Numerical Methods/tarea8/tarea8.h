/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 8 Cabecera**********/
/***********Metodos Numericos**********/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA8_H
#define TAREA8_H

typedef struct eigen{
    double lambda;
    double *vector;
} Eigenv;

typedef struct descomposicion{
    double **Left;
    double **Right;
} Factor;

Factor *QR(double **, int);
double **GramS(double **, int);
double *gradienteConjugado(double **, double *, int, double);
double *gradienteJacobi(double **, double *, int, double);
Eigenv *rayleigh(double **, int, double, int);
Eigenv *subspace(double **, int, int, double, int);
Eigenv *potencia_inv(double **, double **, int *, int, double, int);
Eigenv *eigen_jacobi(double **, double **, int, double, int);
double *solver_lu(double **, double *, int);
double **fact_LuCrout(double **, int);
double *lSolve(double **, double *, int);
double *uSolve(double **, double *, int);
double **trans_mat(double **, int, int);
double norma_tol(double *, double *, int);
double **mult_matxmat(double **, double **, int, int, int);
double *mult_matxvec(double **, double *, int);
double mult_vecxvec(double *, double *, int);
double *rest_vec(double *, double *, int);
double **leerMatriz(char *, int *);
void imprimirMatriz(double **, int, int);
void free_mat(double **, int);
void free_eigen(Eigenv *, int);
void free_factor(Factor *);
void print_eigenv_file(Eigenv *, char *, int, int);
double **genMatriz(int, int);

#endif