/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 11 Cabecera*********/
/***********Metodos Numericos**********/
/**************05/11/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integrales.h"

//Subrutina para Newton-Cotes abierto
double NCO0(double (*function)(double), double a, double b){
    double h = (b-a)/2;
    double x0 = a + h;
    return 2 * h * function(x0);
}

double NCO1(double (*function)(double), double a, double b){
    double h = (b-a) / 3;
    double x0 = a + h;
    double x1 = x0 + h;
    return (3*h/2) * (function(x0) + function(x1));
}

double NCO2(double (*function)(double), double a, double b){
    double h = (b-a) / 4;
    double x0 = a + h;
    double x1 = x0 + h;
    double x2 = x1 + h;

    return (4*h/3) * ((2*function(x0))-function(x1)+(2*function(x2)));
}

double NCO3(double (*function)(double), double a, double b){
    double h = (b-a) / 5;
    double x0 = a + h;
    double x1 = x0 + h;
    double x2 = x1 + h;
    double x3 = x2 + h;

    return (5*h/24) * ((11*function(x0))+function(x1)+function(x2)+(11*function(x3)));
}

//Subrutina para Newton-Cotes Cerrado
double NCC1(double (*function)(double), double a, double b){
    double h = (b-a)/1;
    double x0 = a;
    double x1 = x0 + h;
    return (h/2) * (function(x0)+function(x1));
}

double NCC2(double (*function)(double), double a, double b){
    double h = (b-a)/2;
    double x0 = a;
    double x1 = x0 + h;
    double x2 = x1 + h;
    return (h/3) * (function(x0)+(4*function(x1))+function(x2));
}

double NCC3(double (*function)(double), double a, double b){
    double h = (b-a)/3;
    double x0 = a;
    double x1 = x0 + h;
    double x2 = x1 + h;
    double x3 = x2 + h;
    return (3*h/8) * (function(x0)+(3*function(x1))+(3*function(x2))+function(x3));
}

double NCC4(double (*function)(double), double a, double b){
    double h = (b-a)/4;
    double x0 = a;
    double x1 = x0 + h;
    double x2 = x1 + h;
    double x3 = x2 + h;
    double x4 = x3 + h;
    return (2*h/45) * ((7*function(x0))+(32*function(x1))+(12*function(x2))+(32*function(x3))+(7*function(x4)));
}

double GC1(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x = 1 / sqrt(3);
    double t1 = (((b-a)*(x))+a+b)/2;
    double t2 = (((b-a)*(-x))+a+b)/2;

    return ((b-a)/2) * (function(t1)+function(t2));
}

double GC2(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x = sqrt(15.0) / 5.0;
    double t1 = (((b-a)*(x))+a+b)/2.0;
    double t2 = (((b-a)*(-x))+a+b)/2.0;
    double t3 = (((b-a)*(0))+a+b)/2.0;

    double p1 = (5.0/9.0) * (function(t1) + function(t2));
    double p2 = (8.0/9.0) * function(t3);

    return ((b-a)/2.0) * (p1+p2);
}

double GC3(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x1 = (1.0/35.0) * sqrt(525.0 - (70.0 * sqrt(30.0)));
    double x2 = (1.0/35.0) * sqrt(525.0 + (70.0 * sqrt(30.0)));
    double t1 = (((b-a)*(x1))+a+b)/2.0;
    double t2 = (((b-a)*(-x1))+a+b)/2.0;
    double t3 = (((b-a)*(x2))+a+b)/2.0;
    double t4 = (((b-a)*(-x2))+a+b)/2.0;

    double p1 = (1.0/36.0) * (18.0 + sqrt(30.0)) * (function(t1)+function(t2));
    double p2 = (1.0/36.0) * (18.0 - sqrt(30.0)) * (function(t3)+function(t4));

    return ((b-a)/2.0) * (p1 + p2);
}

double GC4(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x1 = (1.0/21.0) * sqrt(245.0 - (14.0 * sqrt(70.0)));
    double x2 = (1.0/21.0) * sqrt(245.0 + (14.0 * sqrt(70.0)));
    double t1 = (((b-a)*(0))+a+b)/2.0;
    double t2 = (((b-a)*(x1))+a+b)/2.0;
    double t3 = (((b-a)*(-x1))+a+b)/2.0;
    double t4 = (((b-a)*(x2))+a+b)/2.0;
    double t5 = (((b-a)*(-x2))+a+b)/2.0;

    double p1 = (128.0/225.0) * function(t1);
    double p2 = (1.0/900.0) * (322.0 + (13.0*sqrt(70.0))) * (function(t2)+function(t3));
    double p3 = (1.0/900.0) * (322.0 - (13.0*sqrt(70.0))) * (function(t4)+function(t5));

    return ((b-a)/2.0) * (p1 + p2 + p3);
}

double GC5(double (*function)(double), double a, double b){
    //Se obtiene el cambio de variable
    double x1 = 0.932469514203152;
    double x2 = 0.661209386466265;
    double x3 = 0.238619186083197;
    double t1 = (((b-a)*(x1))+a+b)/2;
    double t2 = (((b-a)*(-x1))+a+b)/2;
    double t3 = (((b-a)*(x2))+a+b)/2;
    double t4 = (((b-a)*(-x2))+a+b)/2;
    double t5 = (((b-a)*(x3))+a+b)/2;
    double t6 = (((b-a)*(-x3))+a+b)/2;

    double c1 = 0.171324492379170;
    double c2 = 0.360761573048193;
    double c3 = 0.467913934572691;

    double p1 = c1 * (function(t1)+function(t2));
    double p2 = c2 * (function(t3)+function(t4));
    double p3 = c3 * (function(t5)+function(t6));

    return ((b-a)/2.0) * (p1 + p2 + p3);
}

double f1(double x){
    return sin(x);
}

double f2(double x){
    return (x*x * log(x));
}

double f3(double x){
    return (x*x * exp(-x));
}
