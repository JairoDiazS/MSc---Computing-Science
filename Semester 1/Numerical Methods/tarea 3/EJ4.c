/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ4*************/
/***********Metodos Numericos**********/
/**************10/09/2023**************/
/**************************************/
/**************************************/

//Este programa resuelve una matriz por el metodo gaussiano con el pivoteo
// parcial. Se creo la rutina llamada gauss_parc la cual recibe como argumento
//una matriz cuadrada, un vector y el tamanio de la matriz. Regresa un arreglo
//el cual es la solucion a dicho sistema

#include <stdio.h>
#include <stdlib.h>
#include "tarea3.h"

int main() {
    // Definimos el tamanio de la matriz
    int sz = 5;

//    // Definimos la matriz como un puntero doble y asignamos memoria din�mica a cada fila
//    double **matriz;
//    matriz = (double **)malloc(sz * sizeof(double *));
//    for (int i = 0; i < sz; i++) {
//        matriz[i] = (double *)malloc(sz * sizeof(double));
//    }

    // Definimos la matriz como un puntero doble y asignamos memoria dinamica a cada fila
    double **matrizA;
    matrizA = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizA[i] = (double *)malloc(sz * sizeof(double));
    }

    // Definimos la matriz como un puntero doble y asignamos memoria dinamica a cada fila
    double **matrizB;
    matrizB = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizB[i] = (double *)malloc(sz * sizeof(double));
    }

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
//    matriz[0][0] = 2.0;
//    matriz[0][1] = 1.0;
//    matriz[0][2] = -1.0;
//    matriz[1][0] = 3.0;
//    matriz[1][1] = 2.0;
//    matriz[1][2] = 2.0;
//    matriz[2][0] = 4.0;
//    matriz[2][1] = 3.0;
//    matriz[2][2] = 3.0;

//    // Definimos el vector de ejemplo
//    double vec[3] = {8.0, 14.0, 18.0};

    // Definimos el vector de ejemplo
    double vecA[5] = {51.0, 133.0, 90.0, 49.0, 99.0};

    // Definimos el vector de ejemplo
    double vecB[5] = {532.0, 360.0, 204.0, 396.0, 172.0};

    // Imprimimos la solucion
    printf("La matriz inicial es:\n");
    imprimirMatrizC(matrizB, sz, sz);
    printf("\nEl vector es:\n");
    for (int i = 0; i < sz; i++) printf("%g\t", vecB[i]);
    // Creamos un apuntador para tener la memoria de la solucion
    double *X = gauss_parc(matrizB, vecB, sz);

    printf("\nLa solucion encontrada es:\n");
    for (int i = 0; i < sz; i++) printf("%g\t", X[i]);

    // Liberamos la memoria asignada dinamicamente
    for (int i = 0; i < sz; i++) {
//        free(matriz[i]);
        free(matrizA[i]);
        free(matrizB[i]);
    }
//    free(matriz);
    free(matrizA);
    free(matrizB);
    free(X);

    return 0;
}
