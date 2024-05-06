/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 13 Cabecera*********/
/***********Metodos Numericos**********/
/**************19/11/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA13_H
#define TAREA13_H

double **edos_ivp(double *(*f)(double *, int), double *(*m)(double *(*)(double *, int),\
                    double *, double, int), double a, double b, int N, double *alpha, int sz);
double *euler(double *(*f)(double *, int), double *x, double h, int sz);
double *heun(double *(*f)(double *, int), double *x, double h, int sz);
double *taylor_2(double *(*f)(double *, int), double *x, double h, int sz);
double *rk_4(double *(*f)(double *, int), double *x, double h, int sz);
double GC3(double (*function)(double), double a, double b);
double **gradiente1(double *(*f)(double *, int), double *x, double h, int sz);
double **genMatriz(int nRows, int nCols);
void print_mat(double **matriz, char *name, int nRows, int nCols);

#endif
