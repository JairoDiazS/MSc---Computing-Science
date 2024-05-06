/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/*************Herramientas*************/
/**************23/01/2024**************/
/**************************************/
/**************************************/

/*Libreria de herramientas con programacion dinamica*/

#ifndef TOOLS_H
#define TOOLS_H

//Solicitar memoria dinamica
double *genVector(int size);    //Generar arreglos dinamicos
int *genVector_int(int size);   //Generar arreglos dinamicos
double **genMatrix(int nRows, int nCols);   //Generar matrices dinamicas contiguas
int **genMatrix_int(int nRows, int nCols);  //Generar matrices dinamicas contiguas

//Lectura de archivos
void leerMatriz_int(int **Mat, char *name, int *nRows, int *nCols); //Leer una matriz desde un archivo de texto
void leerMatriz_double(double **Mat, char *name, int *NElem, int *NNode);   //Leer una matriz desde un archivo de texto
double **r_mat(const char *fn, int *nRows, int *nCols);     //Lee una matriz desde un txt
int **r_mat_int(const char *fn, int *nRows, int *nCols);    //Lee una matriz desde un txt

//Escritura de Archivos
void print_mat(double **matriz, char *name, int nRows, int nCols);  //Imprimir matriz a un archivo de texto
void print_mat_int(int **matriz, char *name, int nRows, int nCols);
void print_vec(double *vec, char *name, int sz);    //Imprime un vector a un txt
void print_vec_int(int *vec, char *name, int sz);
void print_postproc(char *fn, double *phi, double **q_pg, double **q_n, int NPoints, int NElem, int NDim);

//Liberacion de memoria dinamica
void freeMat_int(int **mat);    //Liberar matriz contigua
void freeMat_double(double **mat); //Liberar matriz contigua

#endif