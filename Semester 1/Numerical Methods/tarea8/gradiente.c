/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/****Tarea 8 - Gradiente conjugado*****/
/***********Metodos Numericos**********/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "tarea8.c"

#define TOL 1e-6

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
    //Se obtiene el vector de entrada
    double **vectortemp = leerMatriz(argv[2], &sz);
    //Se reorganiza el vector
    double *vector = vectortemp[0]; //Memoria contigua
    //liberando temp
    free(vectortemp);

    //Se imprimen las entradas
    printf("La matriz de entrada es:\n");
    imprimirMatriz(Matriz, sz, sz);
    printf("El vector de entrada es:\n");
    for(int i=0; i<10; i++) printf("%lf\t", vector[i]);
    printf("\n");

    //Se obtiene la solucion
    double *sol = gradienteConjugado(Matriz, vector, sz, TOL);

    //Se imprime la solucion
    printf("La solucion es:\n");
    for(int i=0; i<sz; i++) printf("%lf\t", sol[i]);
    printf("\n");

    //Liberando la memoria
    free(Matriz[0]); //Memoria contigua
    free(Matriz);
    free(vector);
    free(sol);

    return 0;
}