/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 9 Cabecera**********/
/***********Metodos Numericos**********/
/**************22/10/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA9_H
#define TAREA9_H

typedef struct mInterpol{
    double **matriz;
    double sol;
} solInterpol;

solInterpol *eval_newtonDD(double *, double *, double, int);
solInterpol *eval_neville(double *, double *, double, int);
double eval_lagrange(double *, double *, double, int);
double eval_taylor(double *, double, double, int);
double **r_pairs(const char *, int *);
double *r_points(const char *, int *);
void sortPairs(double **, int);
void free_interpol(solInterpol *);
double **genMatriz(int, int);
void imprimirMatriz(double **, int, int);
void print_mat(double **, char *, int, int);

#endif