/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ2*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <math.h>

int gcd(int, int);

int main(){
    int a,b,c;
    printf("Ingrese una fraccion a/b y se reducira a su minima expresion (ingrese los dos numeros separados por un espacio, primero numerador, luego denominador): ");
    scanf("%d %d",&a,&b);
    c=gcd(a,b);
    printf("Su fraccion reducida es: %d / %d \n %d", a/c, b/c, c);

    return 0;
}

int gcd(int a, int b) {
    while (b != 0) {
        int res = b;
        b = a % b;
        a = res;
    }
    return a;
}
