/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ6*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>

int main() {
    int n, mayor1, mayor2, mayor3, even, odd;
    mayor1 = mayor2 = mayor3 = -2147483647;  // Valor minimo para enteros en C
    even = odd = 0;

    printf("Ingrese el numero de elementos: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int r;
        printf("Ingrese el elemento %d: ", i + 1);
        scanf("%d", &r);

        if (r > mayor1) {
            mayor3 = mayor2;
            mayor2 = mayor1;
            mayor1 = r;
        } else if (r > mayor2) {
            mayor3 = mayor2;
            mayor2 = r;
        } else if (r > mayor3) {
            mayor3 = r;
        }

        if (r % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    printf("\nTercer mayor: %d\n", mayor3);
    printf("Numero de elementos even: %d\n", even);
    printf("Numero de elementos odd: %d\n", odd);

    return 0;
}
