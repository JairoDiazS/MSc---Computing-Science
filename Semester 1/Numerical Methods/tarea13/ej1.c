/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/*Tarea 13 - Metodos Clasicos para EDO*/
/**********Metodos Numericos***********/
/**************19/11/2023**************/
/**************************************/
/**************************************/

#include "tarea13.c"

double *yp(double *x, int sz){
    double *sol = (double *)calloc(1, sizeof(double));
    *sol = x[1];
    return sol;
}

double y(double x){
    return exp(x);
}

int main(){
    double a, b, alpha;
    int N = 40;
    a = 0.0;
    b = 4.0;
    alpha = 1.0;
    double **sol1 = edos_ivp(yp, euler, a, b, N, &alpha, 1);
    double **sol2 = edos_ivp(yp, heun, a, b, N, &alpha, 1);
    double **sol3 = edos_ivp(yp, taylor_2, a, b, N, &alpha, 1);
    double **sol4 = edos_ivp(yp, rk_4, a, b, N, &alpha, 1);
    print_mat(sol1, "sol1.txt", N+1, 2);
    print_mat(sol2, "sol2.txt", N+1, 2);
    print_mat(sol3, "sol3.txt", N+1, 2);
    print_mat(sol4, "sol4.txt", N+1, 2);

    double **sol = genMatriz(N+1, 2);
    double h = (b-a)/N;
    for(int i=0; i<N+1; i++){
        sol[i][0] = a + (i*h);
        sol[i][1] = y(sol[i][0]);
    }

    print_mat(sol, "sol.txt", N+1, 2);


    free(sol[0]); //Memoria contigua
    free(sol);
    free(sol1[0]); //Memoria contigua
    free(sol1);
    free(sol2[0]); //Memoria contigua
    free(sol2);
    free(sol3[0]); //Memoria contigua
    free(sol3);
    free(sol4[0]); //Memoria contigua
    free(sol4);

    return 0;
}