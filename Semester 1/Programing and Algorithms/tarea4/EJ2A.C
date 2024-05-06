/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 4/EJ2*************/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ2.c"
#include <stdio.h>
#include <stdlib.h>


int main(){
	printf("A continuacion se despliega un menu para manejar listas ligadas, ingrese ");
	printf("la opcion que quiera, aunque el programa comienza creando una lista, despues ");
	printf("puede manejar la lista.");
	struct Nodo *Head=crear_lista();

	int opt;
	while(1){
	while ((c = getchar()) != '\n' && c != EOF); // Limpiar el búfer de entrada

		printf("\n1.- Insertar nodo.");
		printf("\n2.- Elimina nodo.");
		printf("\n3.- Numero de nodos.");
		printf("\n4.- Buscar valor.");
		printf("\n5.- Invertir lista.");
		printf("\n6.- Ordenar lista.");
		printf("\n7.- Imprimir lista.");
		printf("\n0.- Finalizar programa.");
		printf("\nIngrese su opcion: ");
		scanf("%d",&opt);
		while ((c = getchar()) != '\n' && c != EOF); // Limpiar el búfer de entrada
		switch(opt){
			int n;
			case 1:
				printf("\nIngrese la posicion donde desea agregar el nodo: ");
				scanf("%d",&n);
				while ((c = getchar()) != '\n' && c != EOF); // Limpiar el búfer de entrada
				Head = inserta_nodo(Head, n);
				break;
			case 2:
				printf("\nIngrese la posicion donde del nodo que desea  eliminar: ");
				scanf("%d",&n);
				while ((c = getchar()) != '\n' && c != EOF); // Limpiar el búfer de entrada
				Head = elimina_nodo(Head, n);
				break;
			case 3:
				printf("\nEl numero de nodos es: %d", numero_nodos(Head));
				break;
			case 4:
				printf("\nIngrese el valor que desee buscar: ");
				scanf("%d", &n);
				while ((c = getchar()) != '\n' && c != EOF); // Limpiar el búfer de entrada
				printf("\nEl valor se encuentra en el nodo con direccion en %p", buscar_valor(Head, n));
				break;
			case 5:
				Head=invertir_orden(Head);
				printf("\nLa lista ha sido invertida.");
				break;
			case 6:
				Head = ordena_lista(Head);
				printf("\nLa lista ha sido ordenada.");
				break;
			case 7:
				printf("\nLa lista es la siguiente:\n");
				imprimir_lista(Head);
				break;
			default:
				printf("\nEl programa ha finalizado.");
				break;
		}
		if(opt>=8) break;
	}
	//Liberamos la lista
	liberar_lista(Head);
	return 0;
}
