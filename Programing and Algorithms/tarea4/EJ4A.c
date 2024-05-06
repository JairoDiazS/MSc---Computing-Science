/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ4*************/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ2.c"
#include <stdio.h>
#include <stdlib.h>

int main(){

	srand(time(0));
	//Vamos a generar un arreglo de enteros, el cual contendra las llaves que se
	//buscar en nuestra tabla  hash
	int arrSz=30;	//Eltamanio del arreglo
	//Definimoss el espacio para el arreglo
	int *keys = (int *)malloc(arrSz * sizeof(int));
	for(int i=0; i<arrSz; i++){
		keys[i] =(rand()%100); //Se almacena un valor entero entre 0 y 100
	}	
	//Creamos nuestra tabla hash con las keys que se obtieron
	int mod = 31; //Definimos el modulo del valor de trasnformacion
	struct Nodo **tablaHash = tHash(keys, arrSz, mod);

	//Buscamos una key aleatoria
	int sKey = rand()%arrSz;
	printf("El valor buscado es: %d\n", keys[sKey]);
	struct Nodo *cnodo = busqueda_hash(tablaHash, keys[sKey], mod);
	printf("El valor se encuentra en el nodo con la direccion de memoria %p", cnodo);
	printf("\nEl cual tiene un valor de %d",cnodo->val);

	//Liberamos la memoria
	for(int i=0; i<mod; i++) liberar_lista(tablaHash[i]);
	free(keys);
	return 0;
}
