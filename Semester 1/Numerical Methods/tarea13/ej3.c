/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/*****Tarea 13 - Depredador/Presa******/
/**********Metodos Numericos***********/
/**************19/11/2023**************/
/**************************************/
/**************************************/

#include "tarea13.c"

double *yh(double *x, int sz){
    //Se crea el espacio
    double *sol = (double *)calloc(sz, sizeof(double));
    sol[0] = (0.4*x[1]) - (0.018*x[1]*x[2]);
    sol[1] = (-0.8*x[2]) + (0.023*x[1]*x[2]);
    return sol;
}

double *burden(double *x, int sz){
    //Se crea el espacio
    double *sol = (double *)calloc(sz, sizeof(double));
    sol[0] = (-4.0*x[1]) + (3.*x[2]) + 6;
    sol[1] = (0.6*sol[0]) - (0.2*x[2]);
    return sol;
}

int main(int argc, char **argv){
    double *alpha = (double *)calloc(2, sizeof(double));
    alpha[0] = 30.0;
    alpha[1] = 4.0;
    double t0 = 0.0;
    double tn = 25.0;
    double N = 100;
    double **sol1 = edos_ivp(yh, euler, t0, tn, N, alpha, 2);
    double **sol2 = edos_ivp(yh, heun, t0, tn, N, alpha, 2);
    double **sol3 = edos_ivp(yh, taylor_2, t0, tn, N, alpha, 2);
    double **sol4 = edos_ivp(yh, rk_4, t0, tn, N, alpha, 2);

    print_mat(sol1, "sols1.txt", N+1, 3);
    print_mat(sol2, "sols2.txt", N+1, 3);
    print_mat(sol3, "sols3.txt", N+1, 3);
    print_mat(sol4, "sols4.txt", N+1, 3);

    free(sol1[0]); //Memoria contigua
    free(sol1);
    free(sol2[0]); //Memoria contigua
    free(sol2);
    free(sol3[0]); //Memoria contigua
    free(sol3);
    free(sol4[0]); //Memoria contigua
    free(sol4);
    free(alpha);

    return 0;
}