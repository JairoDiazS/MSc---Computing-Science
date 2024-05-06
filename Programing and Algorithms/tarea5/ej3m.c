/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 5/EJ3*************/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#include "ej3.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Creamos un nodo para cada letra
    NODE *hojas = init_leaf();

    //Leemos el archivo del quijote y onbtenemos las frecuencias para cada letra
    hojas = leer_archivo(argv[1], hojas);

    //Creamos el arbol del codigo huffman
    NODE *root; 
    printf("control11");
    root = arbol_huffman(hojas);
    //Se imprime el arbol.
    print_arbol(root);

    return 0;
}