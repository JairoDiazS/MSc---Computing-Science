/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***Tarea 10 - Interpolacion Hermite***/
/***********Metodos Numericos**********/
/**************29/10/2023**************/
/**************************************/
/**************************************/

#include "tarea10.c"

int main(){
    //Se definen los valores
    int sz = 4;
    double *x = (double *)calloc(sz, sizeof(double));
    double *y = (double *)calloc(sz, sizeof(double));
    double *evals = (double *)calloc(sz, sizeof(double));
    x[0] = 0.3;
    x[1] = 0.32;
    x[2] = 0.33;
    x[3] = 0.35;

    for(int i=0; i<sz; i++){
        y[i] = sin(x[i]);
        evals[i] = cos(x[i]);
    }

    printf("Los datos de entrada son:\n");
    printf("x\t\tsin(x)\t\tD_x cos(x)\n");
    for(int i=0; i<sz; i++) printf("%lf\t%lf\t%lf\n", x[i], y[i], evals[i]);

    //Se obtiene la solucion
    double x0 = 0.34;
    solInterpol *sol = hermiteDD(x, y, evals, x0, sz);

    //Se imprime la solucion
    printf("La evaluacion de la interpolacion de hermite para el seno de %lf es %lf\
 con un error absoluto de %lf\n", x0, sol->sol, fabs(sol->sol-sin(x0)));

    //Liberando la memoria
    free(x);
    free(y);
    free(evals);
    free(sol->matriz[0]); //memoria contigua
    free(sol->matriz);
    free(sol);
    
    return 0;
}