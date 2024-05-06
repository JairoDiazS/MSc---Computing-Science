/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/********Tarea 7/Potencia Inversa******/
/***********Metodos Numericos**********/
/**************01/10/2023**************/
/**************************************/
/**************************************/

#include "tarea7.c"
#include <stdio.h>

#define TOL 1e-6
#define NMax 10000

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 3) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    int sz;
    //Obtenemos la matriz desde el archivo
    double **Matriz = leerMatriz(argv[1], &sz);

    //Definimos el vector inicial
    double *x0 = (double *)calloc(sz, sizeof(double));
    for(int i=0; i<sz; i++) x0[i] = 1;

    //Imprimiendo la matriz
    printf("La matriz de entrada es :\n");
    //imprimirMatriz(Matriz, sz, sz);

    //Numero de eigenvalores solicitados
    int nl= atoi(argv[2]);

    //Obtenemos el eigenvalor y su eigenvector
    Eigenv *sol = potencia_inv(Matriz, x0, &nl, sz, TOL, NMax);

    //Se imprime el eigenvalor hallado y su eigenvector
    for(int i=0; i<nl; i++){
        printf("El eigenvalor %d es: %lf\n", i+1, sol[i].lambda);
    }
    print_eigenv_file(sol, "potinvout.txt", nl, sz);

    //Liebrando el espacio
    free_eigen(sol, nl);
    free_mat(Matriz, sz);
    free(x0);

    return 0;
}