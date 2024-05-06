/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ3*************/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ2.c"
#include <stdio.h>
#include <stdlib.h>

int main(){
	srand(time(0));
	//Generamos un tamanio aleatorio que determina el numero de listas dentro
	//del arreglo (numero entre 15 y 30
	int arrSz = (rand()%16)+15;
	//Generamos un arreglo de listas ligadas
	struct Nodo **arr_lnkLst=gen_arr_lnkLst(arrSz);
	//Imprimimos las listas
	for(int i=0; i<arrSz; i++){
		printf("La lista ligada %d, contiene los siguientes nodos:\n",i);
		imprimir_lista(arr_lnkLst[i]);
	}
	//Ordenamos la lista
	struct Nodo *bigHead = ordena_arr_lnkLst(arr_lnkLst, arrSz);
	//Imprimimos la lista ordena
	printf("La lista ordenada completa es:\n");
	imprimir_lista(bigHead);

	//Liberamos la memoria
	liberar_lista(bigHead);

	return 0;
}
