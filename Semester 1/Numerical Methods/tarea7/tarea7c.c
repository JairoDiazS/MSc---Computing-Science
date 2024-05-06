/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*******Tarea 7/Jacobi eigenvalores****/
/***********Metodos Numericos**********/
/**************01/10/2023**************/
/**************************************/
/**************************************/

#include "tarea7.c"
#include <stdio.h>

#define TOL 1e-6
#define NMax 5

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    int sz;
    //Obtenemos la matriz desde el archivo
    double **Matriz = leerMatriz(argv[1], &sz);

    //Obtenemos el eigenvalor y su eigenvector
    Eigenv *sol = eigen_jacobi(Matriz, sz, TOL, NMax);

    //Se imprime el eigenvalor hallado y su eigenvector
    if(sol != NULL){
        for(int i=0; i<sz; i++){
            printf("El eigenvalor %d es: %lf\n", i+1, sol[i].lambda);
        }
        print_eigenv_file(sol, "jacobiout.txt", sz, sz);
        free_eigen(sol, sz);
    }
    

    //Liebrando el espacio
    free_mat(Matriz, sz);

    return 0;
}