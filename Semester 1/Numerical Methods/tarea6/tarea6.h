/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 6/Cabecera**********/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA6_H
#define TAREA6_H

double **leerMatriz(char *);
double *rest_vec(double *, double *, int);
void free_mat(double **, int);
void imprimirMatriz(double **, int, int);
double *jacobi(double **, double *, double *, int, double, int);
double norm_vec(double *, int);
double *mult_matxvec(double **, double *, int);
double *gauss_seidel(double **, double *, double *, int, double, int);

#endif
