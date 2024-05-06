/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/***********Tarea 4/EJ2-Header*********/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#ifndef EJ2_H
#define EJ2_H

struct Nodo {
	int val;
	struct Nodo *sig;
};

int c;

//Declaraciones
struct Nodo *crear_nodo();
struct Nodo *crear_nodo_in(int);
struct Nodo *crear_lista();
struct Nodo *crear_lista_ran(int);
struct Nodo *inserta_nodo(struct Nodo *, int);
struct Nodo *elimina_nodo(struct Nodo *, int);
int numero_nodos(struct Nodo *);
struct Nodo *buscar_valor(struct Nodo *, int);
struct Nodo *invertir_orden(struct Nodo *);
struct Nodo *ordena_lista(struct Nodo *);
void imprimir_lista(struct Nodo *);
void bubbleSort(int *, int);
struct Nodo **gen_arr_lnkLst(int);
struct Nodo *ordena_arr_lnkLst(struct Nodo **, int);
struct Nodo **tHash(int *, int, int);
struct Nodo *busqueda_hash(struct Nodo **, int, int);

#endif
