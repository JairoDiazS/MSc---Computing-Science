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
    if (argc < 4) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }
    //Se leen los valores desde la terminal
    int sz1;
    double **ps1 = r_pairs(argv[1], &sz1);
    int sz2;
    double **ps2 = r_pairs(argv[2], &sz2);
    int sz3;
    double **ps3 = r_pairs(argv[3], &sz3);

    for(int i=0; i<sz1; i++) printf("%lf\t%lf\n",ps1[0][i], ps1[1][i]);

    //Se genera una matriz para almacenar algunas soluciones
    double **sols = genMatriz(2900, 2);
    //Se rellena el espacio de las x's
    for(int i=0; i<2900; i++) sols[i][0] = 1 + (0.01*i);

    //Se obtiene la solucion para cada punto
    for(int i=0; i<1599; i++){
        sols[i][1] = interpolCubicaFix(ps1[0], ps1[1], 1.0, -0.67, sols[i][0], sz1);
    }
    printf("s1");
    for(int i=1599; i<2669; i++){
        sols[i][1] = interpolCubicaFix(ps2[0], ps2[1], 3.0, -4.0, sols[i][0], sz2);
    }
    printf("s1");
    for(int i=2669; i<2899; i++){
        sols[i][1] = interpolCubicaFix(ps3[0], ps3[1], 0.33, -1.5, sols[i][0], sz3);
    }

    //Se imprimen los puntos en un archivo
    print_mat(sols, "out1.txt", 2899, 2);

    //Liberando la memoria
    free(sols[0]); //memoria contigua
    free(sols);
    free(ps1[0]); //memoria contigua
    free(ps1);
    free(ps2[0]); //memoria contigua
    free(ps2);
    free(ps3[0]); //memoria contigua
    free(ps3);

    return 0;
}