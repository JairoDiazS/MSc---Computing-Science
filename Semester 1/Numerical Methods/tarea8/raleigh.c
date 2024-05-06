/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Tarea 8 - Raleigh**********/
/***********Metodos Numericos**********/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "tarea8.c"

#define TOL 1e-6
#define NMax 10000

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Se obtiene la matriz de entrada
    int sz;
    //Obtenemos la matriz desde el archivo
    double **Matriz = leerMatriz(argv[1], &sz);

    //Se imprimen las entradas
    printf("La matriz de entrada es:\n");
    imprimirMatriz(Matriz, sz, sz);

    //Se obtiene la solucion
    double sol = rayleigh(Matriz, sz, TOL, NMax);

    //Se imprime la solucion
    printf("La solucion es: %lf\n", sol);

    //Liberando la memoria
    free(Matriz[0]); //Memoria contigua
    free(Matriz);

    return 0;
}