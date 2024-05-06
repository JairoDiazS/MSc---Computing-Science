/*****************************************/
/*****************************************/
/***********Jairo Saul Diaz Soto**********/
/*Tarea 10 - Interpolacion Cubica Natural*/
/************Metodos Numericos************/
/***************29/10/2023****************/
/*****************************************/
/*****************************************/

#include "tarea10.c"

int main(int argc, char **argv){
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }
    //Se leen los valores desde la terminal
    int sz1;
    double **ps1 = r_pairs(argv[1], &sz1);

    //Se genera una matriz para almacenar algunas soluciones
    double **sols = genMatriz(120, 2);
    //Se rellena el espacio de las x's
    for(int i=0; i<120; i++) sols[i][0] = 1 + (0.1*i);

    //Se obtiene la solucion para cada punto
    for(int i=0; i<120; i++){
        sols[i][1] = interpolCubicaNat(ps1[0], ps1[1], sols[i][0], sz1);
    }

    //Se imprimen los puntos en un archivo
    print_mat(sols, "out.txt", 120, 2);

    //Liberando la memoria
    free(sols[0]); //memoria contigua
    free(sols);
    free(ps1[0]); //memoria contigua
    free(ps1);

    return 0;
}