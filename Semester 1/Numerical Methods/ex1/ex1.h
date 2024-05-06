/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Examen 1 Cabecera**********/
/***********Metodos Numericos**********/
/**************16/10/2023**************/
/**************************************/
/**************************************/

#ifndef EX1_H
#define EX1_H

typedef struct eigen{
    double lambda;
    double *vector;
} Eigenv;

Eigenv *potencia_inv(double **, double *, int *, int, double, int);
Eigenv *potencia(double **, double *, int *, int, double, int);
double *gradienteJacobi(double **, double *, int, double);
double *mult_matxvec(double **, double *, int);
double mult_vecxvec(double *, double *, int);
double **gen_matProblema();
double *gen_vec();
double **genMatriz(int, int);
double *uSolve(double **, double *, int, int);
double *lSolve(double **, double *, int);
double **fact_Cholesky(double **, int);
double *solve_cholesky(double **, double *, int);
double **fact_LuCrout(double **, int);
double *solver_lu(double **, double *, int, int);
void print_mat(double **, char *, int);
void print_vec(double *, char *, int);
void free_mat(double **, int);
double *rest_vec(double *, double *, int);
void free_eigen(Eigenv *, int);
void print_eigenv_file(Eigenv *, char *, int, int);
double *solver_lured(double **, double *, int, int);

#endif