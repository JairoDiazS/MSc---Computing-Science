/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 10 Cabecera**********/
/***********Metodos Numericos**********/
/**************29/10/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA10_H
#define TAREA10_H

typedef struct mInterpol{
    double **matriz;
    double sol;
} solInterpol;

double interpolCubicaFix(double *x, double *y, double f0, double fn, double x0, int sz);
double interpolCubicaNat(double *x, double *y, double x0, int sz);
solInterpol *hermiteDD(double *x, double *y, double *evals, double x0, int sz);
double **r_pairs(const char *fn, int *sz);
double **genMatriz(int nRows, int nCols);
void print_mat(double **matriz, char *name, int nRows, int nCols);


#endif
