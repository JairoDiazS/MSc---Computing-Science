/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Examen 2 Ejercicio 2********/
/***********Metodos Numericos**********/
/**************04/12/2023**************/
/**************************************/
/**************************************/

#include "tarea12.c"

#define TOL 1e-8
#define nMax 1000

double g1(double *x){
    return cos(x[0]) - sin(x[0] + x[1]);
}

double g2(double *x){
    return cos(x[1]) - sin(x[0] + x[1]);
}

int main(int argc, char **argv){
    double h = 1e-3;
    double (*g[])(double *) = {g1, g2};
    double inf = (4.0/3.0) * M_PI;
    double sup = (7.0/4.0) * M_PI;
    double x0[] = {inf, inf};   
    double *res = broyden_sys(g, x0, h, 2, TOL, nMax);

    printf("Solucion sistema 1\n");
    printf("x1\t\tx2\t\tMetodo\n");

    for(int i=0; i<2; i++) printf("%lf\t",res[i]);
    printf("Broyden\n");

    free(res);

    return 0;
}