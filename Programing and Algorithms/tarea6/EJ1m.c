/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 6/EJ1*************/
/*******Programacion y algoritmos******/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "EJ1.c"

#define x_inicial 0.1

int main(int argc, char** argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 4) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Leemos la imagen de entrada
    int nRows, nCols;
    unsigned char **img = pgmRead(argv[2], &nRows, &nCols);
    unsigned char **tImg;

    //Verificamos si se quiere encriptar o desencriptar la imagen
    if(atoi(argv[1])==0){
        printf("Encriptando la imagen...\n");
        //Funcion de encriptacion
        tImg = transImg(img, nRows, nCols, x_inicial);
        pgmWrite(argv[3], nRows, nCols, tImg, NULL);
        printf("...Imagen encriptada.\n");
    } else{
        printf("Desencriptando la imagen...\n");
        //Funcion de encriptacion
        tImg = transImg(img, nRows, nCols, x_inicial);
        pgmWrite(argv[3], nRows, nCols, tImg, NULL);
        printf("...Imagen desencriptada.\n");
    }

    //Liberando la memoria
    freePgm(img);
    freePgm(tImg);

    return 0;
}