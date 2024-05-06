/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 7 Cabecera**********/
/***********Metodos Numericos**********/
/**************01/10/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA7_H
#define TAREA7_H

typedef struct eigen{
    double lambda;
    double *vector;
} Eigenv;

Eigenv *potencia(double **, double *, int *, int, double, int);
Eigenv *potencia_inv(double **, double *, int *, int, double, int);
Eigenv *eigen_jacobi(double **, int, double, int);
double *solver_lu(double **, double *, int, int);
double **fact_LuCrout(double **, int);
double *lSolve(double **, double *, int);
double *uSolve(double **, double *, int, int);
double **mult_matxmat(double **, double **, int);
double *mult_matxvec(double **, double *, int);
double mult_vecxvec(double *, double *, int);
double *rest_vec(double *, double *, int);
double **leerMatriz(char *, int *);
void imprimirMatriz(double **, int, int);
void free_mat(double **, int);
void free_eigen(Eigenv *, int);
void print_eigenv_file(Eigenv *, char *, int, int);
double **genMatriz(int, int);

#endif