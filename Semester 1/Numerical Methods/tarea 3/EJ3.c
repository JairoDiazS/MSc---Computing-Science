/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ3*************/
/***********Metodos Numericos**********/
/**************10/09/2023**************/
/**************************************/
/**************************************/

//Este programa resuelve una matriz por el metodo gaussiano
//Se creo la subrutina llamada gauss la cual recibe como argumento
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
    double **matrizA;
    matrizA = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizA[i] = (double *)malloc(sz * sizeof(double));
    }

    // Definimos la matriz como un puntero doble y asignamos memoria dinámica a cada fila
    double **matrizB;
    matrizB = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizB[i] = (double *)malloc(sz * sizeof(double));
    }

//    // Definimos la matriz como un puntero doble y asignamos memoria dinámica a cada fila
//    double **matrizC;
//    matrizC = (double **)malloc(sz * sizeof(double *));
//    for (int i = 0; i < sz; i++) {
//        matrizC[i] = (double *)malloc(sz * sizeof(double));
//    }
//
//    // Definimos la matriz como un puntero doble y asignamos memoria dinámica a cada fila
//    double **matrizD;
//    matrizD = (double **)malloc(sz * sizeof(double *));
//    for (int i = 0; i < sz; i++) {
//        matrizD[i] = (double *)malloc(sz * sizeof(double));
//    }

//    // Asignamos valores a la matriz de ejemplo
//    matriz[0][0] = 2.0;
//    matriz[0][1] = 1.0;
//    matriz[0][2] = -1.0;
//    matriz[1][0] = 3.0;
//    matriz[1][1] = 2.0;
//    matriz[1][2] = 2.0;
//    matriz[2][0] = 4.0;
//    matriz[2][1] = 3.0;
//    matriz[2][2] = 3.0;

    // Asignamos valores a la matriz A
    matrizA[0][0] = 9.0;
    matrizA[0][1] = 7.0;
    matrizA[0][2] = 2.0;
    matrizA[0][3] = 3.0;
    matrizA[0][4] = 2.0;
    matrizA[1][0] = 1.0;
    matrizA[1][1] = 10.0;
    matrizA[1][2] = 9.0;
    matrizA[1][3] = 10.0;
    matrizA[1][4] = 9.0;
    matrizA[2][0] = 3.0;
    matrizA[2][1] = 8.0;
    matrizA[2][2] = 9.0;
    matrizA[2][3] = 1.0;
    matrizA[2][4] = 8.0;
    matrizA[3][0] = 3.0;
    matrizA[3][1] = 4.0;
    matrizA[3][2] = 2.0;
    matrizA[3][3] = 1.0;
    matrizA[3][4] = 4.0;
    matrizA[4][0] = 8.0;
    matrizA[4][1] = 8.0;
    matrizA[4][2] = 1.0;
    matrizA[4][3] = 8.0;
    matrizA[4][4] = 8.0;

    // Asignamos valores a la matriz de ejemplo
    matrizB[0][0] = 2.0;
    matrizB[0][1] = 20.0;
    matrizB[0][2] = 18.0;
    matrizB[0][3] = 20.0;
    matrizB[0][4] = 18.0;
    matrizB[1][0] = 6.0;
    matrizB[1][1] = 16.0;
    matrizB[1][2] = 18.0;
    matrizB[1][3] = 2.0;
    matrizB[1][4] = 16.0;
    matrizB[2][0] = 18.0;
    matrizB[2][1] = 14.0;
    matrizB[2][2] = 4.0;
    matrizB[2][3] = 6.0;
    matrizB[2][4] = 4.0;
    matrizB[3][0] = 16.0;
    matrizB[3][1] = 16.0;
    matrizB[3][2] = 2.0;
    matrizB[3][3] = 16.0;
    matrizB[3][4] = 16.0;
    matrizB[4][0] = 6.0;
    matrizB[4][1] = 10.0;
    matrizB[4][2] = 4.0;
    matrizB[4][3] = 2.0;
    matrizB[4][4] = 8.0;

//    // Asignamos valores a la matriz de ejemplo
//    matrizC[0][0] = 1.0;
//    matrizC[0][1] = 0.0;
//    matrizC[0][2] = 0.0;
//    matrizC[0][3] = 0.0;
//    matrizC[0][4] = 0.0;
//    matrizC[1][0] = 0.11111;
//    matrizC[1][1] = 1.0;
//    matrizC[1][2] = 0.0;
//    matrizC[1][3] = 0.0;
//    matrizC[1][4] = 0.0;
//    matrizC[2][0] = 0.33333;
//    matrizC[2][1] = 0.61446;
//    matrizC[2][2] = 1.0;
//    matrizC[2][3] = 0.0;
//    matrizC[2][4] = 0.0;
//    matrizC[3][0] = 0.33333;
//    matrizC[3][1] = 0.28916;
//    matrizC[3][2] = -0.40984;
//    matrizC[3][3] = 1.0;
//    matrizC[3][4] = 0.0;
//    matrizC[4][0] = 0.88889;
//    matrizC[4][1] = 0.19277;
//    matrizC[4][2] = -0.84016;
//    matrizC[4][3] = 0.29075;
//    matrizC[4][4] = 1.0;

//    // Asignamos valores a la matriz de ejemplo
//    matrizD[0][0] = 9.0;
//    matrizD[0][1] = 7.0;
//    matrizD[0][2] = 2.0;
//    matrizD[0][3] = 3.0;
//    matrizD[0][4] = 2.0;
//    matrizD[1][0] = 0.0;
//    matrizD[1][1] = 9.22222;
//    matrizD[1][2] = 8.77778;
//    matrizD[1][3] = 9.66667;
//    matrizD[1][4] = 8.77778;
//    matrizD[2][0] = 0.0;
//    matrizD[2][1] = 0.0;
//    matrizD[2][2] = 2.93976;
//    matrizD[2][3] = -5.93976;
//    matrizD[2][4] = 1.93976;
//    matrizD[3][0] = 0.0;
//    matrizD[3][1] = 0.0;
//    matrizD[3][2] = 0.0;
//    matrizD[3][3] = -5.22951;
//    matrizD[3][4] = 1.59016;
//    matrizD[4][0] = 0.0;
//    matrizD[4][1] = 0.0;
//    matrizD[4][2] = 0.0;
//    matrizD[4][3] = 0.0;
//    matrizD[4][4] = 5.69749;


//    // Definimos el vector de ejemplo
//    double vec[sz] = {8.0, 14.0, 18.0};

    // Definimos el vector de ejemplo
    double vecA[5] = {51.0, 133.0, 90.0, 49.0, 99.0};

    // Definimos el vector de ejemplo
    double vecB[5] = {532.0, 360.0, 204.0, 396.0, 172.0};

//    // Definimos el vector de ejemplo
//    double vecC[5] = {51.0, 133.0, 90.0, 43.0, 99.0 };
//
//    // Definimos el vector de ejemplo
//    double vecD[5] = {51.0, 127.3333, -5.241, -12.9672, 28.4875};

    // Imprimimos la solución
    printf("La matriz inicial es:\n");
    imprimirMatrizC(matrizB, sz, sz);
    printf("\nEl vector es:\n");
    for (int i = 0; i < sz; i++) printf("%g\t", vecB[i]);
    // Creamos un apuntador para tener la memoria de la solución
    double *X = gauss(matrizB, vecB, sz);

    printf("\nLa solución encontrada es:\n");
    for (int i = 0; i < sz; i++) printf("%g\t", X[i]);

    // Liberamos la memoria asignada dinámicamente
    for (int i = 0; i < sz; i++) {
//        free(matriz[i]);
        free(matrizA[i]);
        free(matrizB[i]);
//        free(matrizC[i]);
//        free(matrizD[i]);
    }
//    free(matriz);
    free(matrizA);
    free(matrizB);
//    free(matrizC);
//    free(matrizD);
    free(X);

    return 0;
}
