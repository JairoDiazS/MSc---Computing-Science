/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 6/Jacobi***********/
/***********Metodos Numericos**********/
/**************17/09/2023**************/
/**************************************/
/**************************************/

#include "tarea6.c"
#include <stdio.h>

#define TOL 0.0000000001
#define NMax 50


int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 3) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Obtenemos el vector y la matriz
    double **matrizA = leerMatriz(argv[1]);
    double **vectorBx = leerMatriz(argv[2]);

	//Obtencion del tamanio del sistema
	FILE * mat_file;
	mat_file = fopen(argv[1], "r");
	if(mat_file==NULL) printf("Error al abrir archivo\n");
	int sz; //Solo se lee un valor, ya que el vector, tiene este tamanio y la matriz es cuadrada
	if(fscanf(mat_file, "%d %d", &sz, &sz)<1) printf("Error de lectura\n");
	fclose(mat_file);

    //Reorganizamos el vector
    double *vectorB = (double *)malloc(sz * sizeof(double));
    for(int i=0; i<sz; i++) vectorB[i]=vectorBx[i][0];
    free_mat(vectorBx, sz);

    //Mostramos la entrada
    printf("La matriz de entrada es:\n");
    imprimirMatriz(matrizA, sz, sz);
    printf("El vector de entrada es:\n");
    int sz1=sz;
    if(sz>10) sz1=10;
    for(int i=0; i<sz1; i++) printf("%g\n",vectorB[i]); 

    //Se aplica el metodo de Jacobi
    //Se declara un vector inicial
    double *x0 = (double *)calloc(sz, sizeof(double)); //Vector inicializado en 0
    double *xsol = jacobi(matrizA, vectorB, x0, sz, TOL, NMax);

    //Se imprime el resultado
    printf("EL resultado solucion es\n");
    for(int i=0; i<sz1; i++) printf("%g\n",xsol[i]);

    //Se realiza Ax-b
    double *aprox = rest_vec(mult_matxvec(matrizA, xsol, sz),vectorB, sz);
    printf("La aproximacion es:\n");
    for(int i=0; i<sz1; i++) printf("%g\n",aprox[i]);

    //Se libera la memoria.
    free_mat(matrizA, sz);
    free(vectorB);
    free(x0);
    free(xsol);
    free(aprox);

    return 0;
}