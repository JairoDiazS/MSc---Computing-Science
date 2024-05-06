/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ1B************/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ1.c"
#include <stdio.h>
#include <stdlib.h>

int main(){

	char fnImg[] = "fractal_tree.ascii.pgm"; //Nombre de la imagen a leer

	//Apuntadores para conocer el tamanio de la imagen
	int *rows, *cols;
	rows = (int *)malloc(sizeof(int));
	cols = (int *)malloc(sizeof(int));

	//Leer la imagen
	unsigned char **image = pgmRead(fnImg, rows, cols);

	//Obtenemos el gradiente de la imagen
	gradient_image(image, *rows, *cols, "imgGrad.pgm");

	//Liberando memoria
	freePgm(image);
	free(rows);
	free(cols);

	return 0;
}
