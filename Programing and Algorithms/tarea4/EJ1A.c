/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ1A************/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ1.c"
#include <stdio.h>
#include <stdlib.h>

int main(){

	char fnImg[] = "len_out.pgm"; //Nombre de la imagen a leer
	int wsz=11;

	//Apuntadores para conocer el tamanio de la imagen
	int *rows, *cols;
	rows = (int *)malloc(sizeof(int));
	cols = (int *)malloc(sizeof(int));

	//Leer la imagen
	unsigned char **image = pgmRead(fnImg, rows, cols);

	//Promediamos la imagen
	mean_image(image, *rows, *cols, wsz, "imgout.pgm");

	//Liberando memoria
	freePgm(image);
	free(rows);
	free(cols);

	return 0;
}
