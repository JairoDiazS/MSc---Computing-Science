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

#define TOL 1e-8
#define NMax 1000

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 3) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Se obtiene la matriz de entrada
    int sz;
    //Obtenemos la matriz desde el archivo
    double **Matriz = leerMatriz(argv[1], &sz);

    //Se imprimen las entradas
    //printf("La matriz de entrada es:\n");
    //imprimirMatriz(Matriz, sz, sz);

    //Se obtiene el numero de eigenvalores
    int req = atoi(argv[2]);
    //Se obtiene la solucion
    Eigenv *sol = subspace(Matriz, req, sz, TOL, NMax);

    //Se imprime la solucion
    printf("La solucion es:\n");
    for(int i=0; i<req; i++){
        printf("El eigenvalor %d es: %lf\n", i+1, sol[i].lambda);
    }

    //Liberando la memoria
    free(Matriz[0]); //Memoria contigua
    free(Matriz);
    free(sol->vector);
    free(sol);

    return 0;
}