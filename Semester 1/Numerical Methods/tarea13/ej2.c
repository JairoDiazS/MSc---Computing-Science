/**************************************/
/**************************************/
/*********Jairo Saul Diaz Soto*********/
/*****Tarea 13 - Integral eliptica*****/
/**********Metodos Numericos***********/
/**************19/11/2023**************/
/**************************************/
/**************************************/

#include "tarea13.c"

double f(double x0){
    return sqrt( 1 + (x0*x0*x0) );
}

double *yp(double *x, int sz){
    double *sol = (double *)calloc(1, sizeof(double));
    *sol = sqrt( 1 + (x[0]*x[0]*x[0]));
    return sol;
}

int main(){

    //Aproximacion
    double a = 0.0;
    double b = 2.0;
    double apx = GC3(f, a, b);
    printf("El valor de la arpoximacion de y(2)=%lf\n", apx);

    //Metodo de edos
    double N = 10;
    double alpha = 0;
    double **sol1 = edos_ivp(yp, euler, a, b, N, &alpha, 1);
    double **sol2 = edos_ivp(yp, heun, a, b, N, &alpha, 1);
    double **sol3 = edos_ivp(yp, taylor_2, a, b, N, &alpha, 1);
    double **sol4 = edos_ivp(yp, rk_4, a, b, N, &alpha, 1);

    printf("Tabla de aproximaciones por metodo\n");
    printf("xi\t\tyi Euler\tyi Heun\t\tyi T2\t\tyi RK4\n");
    for(int i=0; i<N+1; i++){
        printf("%lf\t%lf\t%lf\t%lf\t%lf\n", sol1[i][0], sol1[i][1], sol2[i][1], sol3[i][1], sol4[i][1]);
    }

    print_mat(sol1, "sol1b.txt", N+1, 2);
    print_mat(sol2, "sol2b.txt", N+1, 2);
    print_mat(sol3, "sol3b.txt", N+1, 2);
    print_mat(sol4, "sol4b.txt", N+1, 2);

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