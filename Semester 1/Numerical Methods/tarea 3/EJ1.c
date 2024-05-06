/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1*************/
/***********Metodos Numericos**********/
/**************10/09/2023**************/
/**************************************/
/**************************************/

//Este programa resuelve una matriz triangular inferior
//Se creo la subrutina llamada lSolve la cual recibe como argumento
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
    double **matrizC;
    matrizC = (double **)malloc(sz * sizeof(double *));
    for (int i = 0; i < sz; i++) {
        matrizC[i] = (double *)malloc(sz * sizeof(double));
    }

//    // Asignamos valores a la matriz de ejemplo
//    matriz[0][0] = 1.0;
//    matriz[0][1] = 0;
//    matriz[0][2] = 0;
//    matriz[1][0] = 1.0;
//    matriz[1][1] = 2.0;
//    matriz[1][2] = 0;
//    matriz[2][0] = 1.0;
//    matriz[2][1] = 2.0;
//    matriz[2][2] = 1.0;

    // Asignamos valores a la matriz de ejemplo
    matrizC[0][0] = 1.0;
    matrizC[0][1] = 0.0;
    matrizC[0][2] = 0.0;
    matrizC[0][3] = 0.0;
    matrizC[0][4] = 0.0;
    matrizC[1][0] = 0.11111;
    matrizC[1][1] = 1.0;
    matrizC[1][2] = 0.0;
    matrizC[1][3] = 0.0;
    matrizC[1][4] = 0.0;
    matrizC[2][0] = 0.33333;
    matrizC[2][1] = 0.61446;
    matrizC[2][2] = 1.0;
    matrizC[2][3] = 0.0;
    matrizC[2][4] = 0.0;
    matrizC[3][0] = 0.33333;
    matrizC[3][1] = 0.28916;
    matrizC[3][2] = -0.40984;
    matrizC[3][3] = 1.0;
    matrizC[3][4] = 0.0;
    matrizC[4][0] = 0.88889;
    matrizC[4][1] = 0.19277;
    matrizC[4][2] = -0.84016;
    matrizC[4][3] = 0.29075;
    matrizC[4][4] = 1.0;

//    // Definimos el vector de ejemplo
//    double vector[3] = {1.0, 5.0, 8.0};

    // Definimos el vector de ejemplo
    double vecC[5] = {51.0, 133.0, 90.0, 43.0, 99.0 };

    // Imprimimos la solución
    printf("La matriz inicial es:\n");
    imprimirMatrizC(matrizC,sz,sz);
    printf("\nEl vector es: \n");
    for(int i=0;i<sz;i++) printf("%g\t",vecC[i]);
    printf("\nLa solcuon ecnontrada es el vector es: \n");

    // Creamos un apuntador para tener la memoria de la solución
    double *X = lSolve(matrizC, vecC, sz);
    for(int i=0;i<sz;i++) printf("%g\t",X[i]);


    // Liberamos la memoria asignada dinámicamente
    for (int i = 0; i < sz; i++) {
        free(matrizC[i]);
    }
    free(matrizC);
    free(X);

    return 0;
}
