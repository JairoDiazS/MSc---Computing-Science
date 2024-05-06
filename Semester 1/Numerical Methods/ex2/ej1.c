/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Examen 2 Ejercicio 1********/
/***********Metodos Numericos**********/
/**************04/12/2023**************/
/**************************************/
/**************************************/

#include "integrales.c"

double fun(double x){
    return 1.0/x;
}

int main(int argc, char **argv){
    double a = 1.0;
    double b = 2.0;
    double nco0 = NCO0(fun, a, b);
    double nco3 = NCO3(fun, a, b);
    double ncc4 = NCC4(fun, a, b);
    double gc5 = GC5(fun, a, b);
    printf("Metodo\ta\t\tb\t\tint\t\teabs\n");
    printf("%s\t%lf\t%lf\t%lf\t%lf\n", "NCO0", a, b, nco0, fabs(nco0-log(2)));
    printf("%s\t%lf\t%lf\t%lf\t%lf\n", "NCO3", a, b, nco3, fabs(nco3-log(2)));
    printf("%s\t%lf\t%lf\t%lf\t%lf\n", "NCC4", a, b, ncc4, fabs(ncc4-log(2)));
    printf("%s\t%lf\t%lf\t%lf\t%lf\n", "GC5", a, b, gc5, fabs(gc5-log(2)));

    return 0;
}