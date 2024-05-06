/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 12 Cabecera*********/
/***********Metodos Numericos**********/
/**************12/11/2023**************/
/**************************************/
/**************************************/

#include "tarea12.h"

//Rutina para derivada hacia atras
double fw_diff(double (*f)(double), double x0, double h){
    return (f(x0+h)-f(x0))/h;
}

//Rutina para derivada hacia atras
double bw_diff(double (*f)(double), double x0, double h){
    return (f(x0)-f(x0-h))/h;
}

//Rutina para derivada centrada
double ct_diff(double (*f)(double), double x0, double h){
    return (f(x0+h)-f(x0-h))/(2.0*h)
}

//Rutina para derivada de 3 puntos hacia adelante
double three_endp_diff(double (*f)(double), double x0, double h){
    return (1.0/(2*h)) * ((-3.0 * f(x0)) + (4.0*f(x0+h)) - f(x0+(2.0*h))); 
}

//Rutina para derivada de 3 puntos centrada
double three_midp_diff(double (*f)(double), double x0, double h){
    return (1.0/(2.0*h)) * (f(x0+h) - f(x0-h)); 
}

//Rutina para derivada de 5 puntos centrada
double five_midp_diff(double (*f)(double), double x0, double h){
    return (1.0/(12.0*h)) * (f(x0-(2.0*h)) - (8.0 * f(x0-h)) + (8.0*f(x0+h)) - f(x0+(2.0*h))); 
}

//Rutina para derivada de 5 puntos hacia adelante
double five_endp_diff(double (*f)(double), double x0, double h){
    return (1.0/(12.0*h)) * ((-25.0 * f(x0)) + (48.0 * f(x0+h)) + \
    (-36.0*f(x0+(2.0*h))) + (16.0*f(x0+(3.0*h))) + (-3.0*f(x0+(4.0*h)))); 
}

//Segunda derivada por punto fijo
double midp_secdiff(double (*f)(double), double x0, double h){
    return (1.0/(h*h)) * (f(x0-h) + (-2*f(x0)) + f(x0+h));
}

//Rutina para sistemas de ecuaciones no lineales por punto fijo
double *fixedPoint_nonLinear(double (*f)(double *), double *x0, double tol){

}
