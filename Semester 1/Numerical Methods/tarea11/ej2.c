/********************************************/
/********************************************/
/*************Jairo Saul Diaz Soto***********/
/************Tarea 11 - Integracion**********/
/**************Metodos Numericos*************/
/*****************05/11/2023*****************/
/********************************************/
/********************************************/

#include "integrales.c"

int main(){
    //Creamos un arreglo de las funciones
    double (*functions[3])(double) = {f1, f2, f3};

    double a[3] = {0.0, 1.0, 0.0};
    double b[3] = {M_PI_4, 1.5, 1.0};
    double vals[13];
    double (*ints[13])(double (*)(double), double, double) = {NCO0, NCO1, NCO2,\
    NCO3, NCC1, NCC2, NCC3, NCC4, GC1, GC2, GC3, GC4, GC5};
    char *strgs[] = {"NCO0", "NCO1", "NCO2",\
    "NCO3", "NCC1", "NCC2", "NCC3", "NCC4", "GC1", "GC2", "GC3", "GC4", "GC5"};

    //Recorremos las funciones y las evaluamos con los distintos metodos
    for(int i=0; i<3; i++){
        if(i==0) printf("f(x) = sen(x)\n");
        if(i==1) printf("f(x) = x**2 ln(x)\n");
        if(i==2) printf("f(x) = x**2 exp(-x)\n");
        printf("Metodo\ta\t\tb\t\tint\n");
        //Calculando las integrales
        for(int j=0; j<13; j++){
            vals[j] = ints[j](functions[i], a[i], b[i]);
            printf("%s\t%lf\t%lf\t%lf\n",strgs[j], a[i], b[i], vals[j]);
        } 
    }

    return 0;
}