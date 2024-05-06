/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/********Examen 1 - Ejercicio 1a*******/
/***********Metodos Numericos**********/
/**************16/10/2023**************/
/**************************************/
/**************************************/

/*El siguiente programa realiza una aproximacion para la constante de euler, el
tamanio de n se debe ingresar en la ejecucion como bandera.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    //Declaracion de variables
    int k=20, i;
    double e, n=1.0, e_real = exp(1), e_abs, e_rel;
    FILE *file;

    //Abrimos un archivo para guardar los valores
    file = fopen("datos.txt", "w");
    if(file == NULL){
        printf("Error al abrir el archivo.\n");
        return 0;
    }
    //Se imprime una cabecera
    printf("Iter\te aprox \terror abs\terror rel\n");

    //Se inicia el ciclo
    for(i=0; i<k; i++){
        //Se define la n
        n*=10;

        //Se obtiene la arpoximacion
        e = pow((1.0+(1/n)), n);

        //Se obtienen los errores
        e_abs = fabs(e-e_real);
        e_rel = e_abs/e_real;

        //Se imprimen los valores
        fprintf(file, "%d\t%lf\n",i+1, e);
        printf("%d\t%.8lf\t%.8lf\t%.8lf\n",i+1, e, e_abs, e_rel);
    }

    fclose(file);
    return 0;
}