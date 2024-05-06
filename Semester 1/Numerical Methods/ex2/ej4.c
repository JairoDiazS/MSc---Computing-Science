/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Examen 2 Ejercicio 4********/
/***********Metodos Numericos**********/
/**************04/12/2023**************/
/**************************************/
/**************************************/

#include "tarea13.c"

double *yh(double *x, int sz){
    //Se crea el espacio
    double *sol = (double *)calloc(sz, sizeof(double));
    sol[0] = (2*x[1]) - x[2] + sin(x[0]);
    sol[1] = x[1];
    return sol;
}

double yreal(double x){
    return (-(3.0*exp(x)/2.0) + (5.0*x*exp(x)/2.0) + (cos(x)/2.0));
}

int main(int argc, char** argv){
    double *alpha = (double *)calloc(2, sizeof(double));
    alpha[0] = 1.0;
    alpha[1] = -1.0;
    double t0 = 0.0;
    double tn = 2.0;
    double N = 200;
    double **sol4 = edos_ivp(yh, rk_4, t0, tn, N, alpha, 2);
    print_mat(sol4, "sols4.txt", N+1, 3);

    //Creamos la matriz para guardar el intervalo
    double **ppts1 = genMatriz(N, 2);

    for(int i=0; i<N; i++){
        ppts1[i][0] = t0 + (i / 100.0);
        ppts1[i][1] = yreal(ppts1[i][0]);
    }
    print_mat(ppts1, "ppts1.txt", N, 2);

    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    fprintf(gnuplotPipe, "plot 'sols4.txt' using 1:3 w p title 'RK-4'\n");
    fprintf(gnuplotPipe, "replot 'ppts1.txt' using 1:2 w l title 'Funcion Real'\n");
    fclose(gnuplotPipe);

    free(sol4[0]); //Memoria contigua
    free(sol4);
    free(alpha);

    return 0;
}