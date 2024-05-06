/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*******Tarea 8 - Factorizacion QR*****/
/***********Metodos Numericos**********/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "tarea8.c"

int main(int argc, char** argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    int sz;
    //Obtenemos la matriz desde el archivo
    double **Matriz = leerMatriz(argv[1], &sz);

    //Imprimiendo la matriz
    printf("La matriz de entrada es :\n");
    imprimirMatriz(Matriz, sz, sz);

    //Se obtiene la factorizacion
    Factor *sol = QR(Matriz, sz);

    //Se imprimen las soluciones
    printf("La matriz Q es la siguiente:\n");
    imprimirMatriz(sol->Left, sz, sz);
    printf("La matriz R es la siguiente:\n");
    imprimirMatriz(sol->Right, sz, sz);

    //Se libera la matriz
    free(Matriz[0]); //Memoria contigua
    free(Matriz);
    free_factor(sol);

    return 0;
}