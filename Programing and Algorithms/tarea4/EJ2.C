/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Tarea 4/EJ2-Header*********/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#include "EJ2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Declaraciones
struct Nodo *crear_nodo(){
	struct Nodo *pnode;
	int val;
	printf("\nIngrese el valor del nuevo nodo: ");
	if(!scanf("%d",&val)){
		while ((c = getchar()) != '\n' && c != EOF); // Limpiar el bufer de entrada
		return NULL;
	}
	pnode = (struct Nodo *)malloc(sizeof(struct Nodo));
	if(pnode == NULL) return NULL;
	pnode->val = val;
	pnode->sig= NULL;

	return pnode;
};

struct Nodo *crear_nodo_in(int val){
	struct Nodo *pnode;
	pnode = (struct Nodo *)malloc(sizeof(struct Nodo));
	if(pnode == NULL) return NULL;
	pnode->val = val;
	pnode->sig= NULL;

	return pnode;
};

struct Nodo *crear_lista(){
	struct Nodo *Head, *pnode, *temp;

	printf("\nCreando lista...\n");
	Head=crear_nodo();
	if(Head==NULL) return NULL;
	pnode = Head;
	while(pnode!=NULL){
		printf("HH");
		temp=crear_nodo();
		pnode->sig=temp;
		pnode=temp;
	}
	return Head;
};

struct Nodo *crear_lista_ran(int sz){
	struct Nodo *Head, *pnode, *temp;

	printf("\nCreando lista...\n");
	Head=crear_nodo_in(rand());
	if(Head==NULL) return NULL;
	pnode = Head;
	int i=0;
	while(i<sz && pnode!=NULL){
		printf("HH");
		temp=crear_nodo_in(rand());
		pnode->sig=temp;
		pnode=temp;
		i++;
	}
	return Head;
};

struct Nodo *inserta_nodo(struct Nodo *Head, int pos){
	//Creamos el nuevo nodo
	struct Nodo *nuevoNodo = crear_nodo();
	//Verificamos si quiere agregarlo en la cabeza
	if(pos==0){
		nuevoNodo->sig=Head;
		return nuevoNodo;
	}
	//Declaramos apuntadores auxiliares
	struct Nodo *current=Head;
	struct Nodo *next=Head->sig;
	int count=0;
	//Verificamos que no hallamos llegado a la posicion que se desea
	//o bien, que no hallamos llegado al final de la lista. Si fuere el
	//caso de querer agregar en una posicion mas larga que la lista
	//este simplemente se agrega al final.
	while(count <pos && current!=NULL){
		current=current->sig;
		next=current->sig;
		count++;
	}
	current->sig=nuevoNodo;
	nuevoNodo->sig=next;

	return Head;
}

struct Nodo *elimina_nodo(struct Nodo *Head, int pos){
	//Verificamos que no se quiera eliminar la cabeza, en dado caso
	if(pos==0){
		return Head->sig;
	}
	//Apuntadores auxiliares
	struct Nodo *prev=Head;
	struct Nodo *current=Head->sig;
	int count=1;
	while(count < pos && current!=NULL){
		prev=current;
		current=prev->sig;
	}
	prev->sig=current->sig;
	//liberamos la memoria
	free(current);
	return Head;
}

int numero_nodos(struct Nodo *Head){
	//Apuntadores auxiliares
	struct Nodo *temp=Head;
	int count=0;
	while(temp!=NULL){
		count++;
		temp=temp->sig;
	}
	return count;
}

struct Nodo *buscar_valor(struct Nodo *Head, int val){
	//apuntadores auxiliares
	struct Nodo *temp=Head;
	while(temp->val!=val && temp!=NULL) temp=temp->sig;
	return temp;
};

// Funcion para invertir la lista
struct Nodo* invertir_lista(struct Nodo* Head) {
    struct Nodo* prev = NULL;
    struct Nodo* current = Head;
    struct Nodo* next = NULL;

    while (current != NULL) {
        next = current->sig;
        current->sig = prev;
        prev = current;
        current = next;
    }

    return prev; // El nuevo inicio de la lista es el �ltimo nodo original
}

struct Nodo *ordena_lista(struct Nodo *Head){
	//Apuntadores auxiliares
	struct Nodo *current=Head;
	//Se obtiene el tamanio de la lista
	int sz = numero_nodos(Head);
	//Creamos un arreglo con los valores de los nodos
	int *arr=(int *)malloc(sz*sizeof(int));
	//Guardamos los valores en el arreglo
	for(int i=0; i<sz; i++){
		arr[i]=current->val;
		current=current->sig;
	}
	//Ordenamos la lista
	bubbleSort(arr, sz);
	//Regresamos los valores en orden
	current=Head;
	for(int i=0; i<sz; i++){
		current->val=arr[i];
		current=current->sig;
	}
	free(arr);
	return Head;
};

void imprimir_lista(struct Nodo *Head){
    // Apuntadores auxiliares
    struct Nodo *current = Head;
    int count = 0;
    if (current == NULL) {
        printf("La lista est� vac�a.\n");
        return;
    }
    while (current != NULL) {
        printf("\nEl nodo %d tiene un valor de %d\n", count, current->val);
        current = current->sig;
        count++;
    }
}

void liberar_lista(struct Nodo *Head){
	//Apuntadores auxiliares
	struct Nodo *current=Head;
	struct Nodo *next;
	while(current!=NULL){
		next=current->sig;
		free(current);
		current=next;
	}
}

struct Nodo **gen_arr_lnkLst(int arrSz){
	//
	int sz;
	//Reservamos el espacio para la lista
	struct Nodo **arr_lnkLst=(struct Nodo **)malloc(arrSz * sizeof(struct Nodo*));
	for(int i=0; i<arrSz; i++){
		sz = (rand()%16)+15;
		arr_lnkLst[i]=crear_lista_ran(sz);
	}
	return arr_lnkLst;
};

struct Nodo *ordena_arr_lnkLst(struct Nodo **arr_lst, int sz){
	//Creamos una lista ligada donde colocaremos cada una las listas del arreglo
	struct Nodo *current, *prev;
	//Unimos las listas ligadas
	for(int i=0; i<sz-1; i++){
		prev=arr_lst[i];
		current=prev->sig;
			while(current!=NULL){
				prev=current;
				current=prev->sig;
			}
		prev->sig=arr_lst[i+1];
	}
	//Ordenamos la lista
	arr_lst[0]=ordena_lista(arr_lst[0]);
	return arr_lst[0];
};

struct Nodo **tHash(int *keys, int arrSz, int mod){
	//Apartamos espacio para nuestra tabla hash
	struct Nodo **table = (struct Nodo **)malloc(mod * sizeof(struct Nodo*));
	//Inicializamos la tabla con Heads nulos
	for(int i=0; i<mod; i++){
		table[i]=NULL;
	}
	//Comenzamos a guardar las llaves
	int hKey;
	struct Nodo *temp, *current, *prev;
	for(int i=0; i<arrSz; i++){
		//Buscamos el valor en donde debe de ir en la tabla hash
		hKey=keys[i]%mod;
		//Verificamos si ya exitse el nodo cabeza de ese punto
		if(table[hKey]==NULL) table[hKey]=crear_nodo_in(0);
		//Accedemos al nodo cabecera y aumentamos su valor
		table[hKey]->val++;
		//Creamos un nodo y le damos el valor de la key
		temp=crear_nodo_in(keys[i]);
		//Recorremos la lista ligada y lo almacenamos al final
		prev=table[hKey];
		current=prev->sig;
		while(current!=NULL){
			prev=current;
			current=prev->sig;
		}
		//Asignamos el nuevo valor al final de la lista
		prev->sig=temp;
	}
	return table;
};

struct Nodo *busqueda_hash(struct Nodo **tHash, int val, int mod){
	//Hacemos el valor transformado
	int hKey = val%mod;
	//Buscamos el Head que pertenece a este valor
	struct Nodo *Head = tHash[hKey];
	//Obtenemos la direccion del nodo que pertenece
	struct Nodo *cnodo = buscar_valor(Head->sig, val);
	//Regresamos el nodo correspondiente
	return cnodo;
};

void bubbleSort(int *arr, int n){
    int swapped;
    int temp;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                swapped = 1;
            }
        }
        // Si no se hizo ning�n intercambio en esta pasada, el arreglo ya est� ordenado
        if (swapped == 0) {
            break;
        }
    }
}
