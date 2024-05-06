/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ2*************/
/***********Metodos Numericos**********/
/**************10/09/2023**************/
/**************************************/
/**************************************/

//Este programa resuelve una matriz triangular superior
//Se creo la subrutina llamada uSolve la cual recibe como argumento
//una matriz cuadrada, un vector y el tamanio de la matriz. Regresa un arreglo
//el cual es la solucion a dicho sistema

#include <stdio.h>
#include <stdlib.h>
#include "tarea3.h"

int main() {
    // Definimos el tamaño de la matriz
    int sz = 5;

//    // Definimos la matriz como un puntero doble y asignamos memoria dinámica a cada fila
//    double **matriz;
//    matriz = (double **)malloc(sz * sizeof(double *));
//    for (int i = 0; i < sz; i++) {
//        matriz[i] = (double *)malloc(sz * sizeof(double));
//    }

    // Definimos la matriz como un puntero doble y asignamos memoria dinámica a cada fila
    double **matrizD;
    matrizD = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizD[i] = (double *)malloc(sz * sizeof(double));
    }

//    // Asignamos valores a la matriz de ejemplo
//    matriz[0][0] = 1.0;
//    matriz[0][1] = 2.0;
//    matriz[0][2] = 1.0;
//    matriz[1][0] = 0;
//    matriz[1][1] = 2.0;
//    matriz[1][2] = 1.0;
//    matriz[2][0] = 0;
//    matriz[2][1] = 0;
//    matriz[2][2] = 1.0;

    // Asignamos valores a la matriz de ejemplo
    matrizD[0][0] = 9.0;
    matrizD[0][1] = 7.0;
    matrizD[0][2] = 2.0;
    matrizD[0][3] = 3.0;
    matrizD[0][4] = 2.0;
    matrizD[1][0] = 0.0;
    matrizD[1][1] = 9.22222;
    matrizD[1][2] = 8.77778;
    matrizD[1][3] = 9.66667;
    matrizD[1][4] = 8.77778;
    matrizD[2][0] = 0.0;
    matrizD[2][1] = 0.0;
    matrizD[2][2] = 2.93976;
    matrizD[2][3] = -5.93976;
    matrizD[2][4] = 1.93976;
    matrizD[3][0] = 0.0;
    matrizD[3][1] = 0.0;
    matrizD[3][2] = 0.0;
    matrizD[3][3] = -5.22951;
    matrizD[3][4] = 1.59016;
    matrizD[4][0] = 0.0;
    matrizD[4][1] = 0.0;
    matrizD[4][2] = 0.0;
    matrizD[4][3] = 0.0;
    matrizD[4][4] = 5.69749;

//    // Definimos el vector de ejemplo
//    double vector[3] = {8.0, 5.0, 1.0};

    // Definimos el vector de ejemplo
    double vecD[5] = {51.0, 127.3333, -5.241, -12.9672, 28.4875};

    // Imprimimos la solución
    printf("La matriz inicial es:\n");
    imprimirMatrizC(matrizD,sz,sz);
    printf("\nEl vector es: \n");
    for(int i=0;i<sz;i++) printf("%g\t",vecD[i]);
    printf("\nLa solcuon ecnontrada es el vector es: \n");
    // Creamos un apuntador para tener la memoria de la solución
    double *X = uSolve(matrizD, vecD, sz);
    for(int i=0;i<sz;i++) printf("%g\t",X[i]);


    // Liberamos la memoria asignada dinámicamente
    for (int i = 0; i < sz; i++) {
        free(matrizD[i]);
    }
    free(matrizD);
    free(X);

    return 0;
}


