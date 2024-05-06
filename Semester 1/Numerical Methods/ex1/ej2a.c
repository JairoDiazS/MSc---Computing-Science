/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/********Examen 1 - Ejercicio 2a*******/
/***********Metodos Numericos**********/
/**************16/10/2023**************/
/**************************************/
/**************************************/

#include "ex1.c"

#define NMax 5000
#define TOL 1e-6

int main(){

    int sz = 2000;

    //Se obtiene la matriz
    double **matriz = gen_matProblema();

    //Se imrpime en un archivo
    //print_mat(matriz, "matriz.txt", sz);

    //Se genera el vector de entrada
    double *vectorB =  gen_vec();
    //print_vec(vectorB, "vin.txt", sz);

    //Se obtiene la solucion al sistema de ecuaciones
    //double *sol1 = solver_lu(matriz, vectorB, sz, 1); //Cholesky
    //double *sol2 = gradienteJacobi(matriz, vectorB, sz, TOL);

    //Se imprime la solcion
    //print_vec(sol1, "voutcholesky.txt", sz);
    //print_vec(sol2, "voutjacgrad.txt", sz);

    //Se obtienen los eigenvalores y vectores
    //Definimos el vector inicial
    double *x0 = (double *)calloc(sz, sizeof(double));
    for(int i=0; i<sz; i++) x0[i] = 1.0;

    int nl = 10;

    //Eigenv *sol11 = potencia(matriz, x0, &nl, sz, TOL, NMax);
    //print_eigenv_file(sol11, "potencia.txt", nl, sz);
    Eigenv *sol22 = potencia_inv(matriz, x0, &nl, sz, TOL, NMax);
    print_eigenv_file(sol22, "potenciainv.txt", nl, sz);

    //Liberando memoria
    //free_eigen(sol11, nl);
    free_eigen(sol22, nl);
    free(vectorB);
    //free(sol1);
    //free(sol2);
    free(matriz[0]); //Memoria contigua
    free(matriz);
    free(x0);

    return 0;
}