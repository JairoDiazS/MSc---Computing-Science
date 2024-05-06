/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 6/EJ2-Cabecera********/
/*******Programacion y algoritmos******/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "EJ2.h"

//Subrutina para crear una tabla hash dado un vector de entrada
hNode **crea_Thash(int *keys, int sz, int mod){
    //Creamos la lista de la tabla hash
    //Reservamos el espacio
    hNode **tHash = (hNode **)malloc(mod * sizeof(hNode *));
    if(tHash == NULL){
        printf("Error de asignacion de memoria.\n");
        return NULL;
    }
    //Se rellena la tabla
    for(int i=0; i<mod; i++) tHash[i] = crea_Hnodo();

    //Empezamos a realizar el llenado conforme a la funcion de la tabla hash
    int temp;
    for(int i=0; i<sz; i++){
        //Buscamos a que nodo pertenece
        temp = keys[i]%mod;
        //Ingresamos al valor de la tabla de hash
        tHash[temp]->root = crea_Tnodo(keys[i], tHash[temp]->root);
        //Incrementamos el valor del numero de elementos en este nodo
        tHash[temp]->value++;
    }

    //Tras finalizar el proceso retornamos la tabla hash
    return tHash;
}

//Subrutina para hallar el arbol mas alto de la tabla hash
void max_height(hNode **tHash, int sz){

    int current, max, imax = -1, ii;
    //Calculamos la altura de los arboles
    for(int i=0; i<sz; i++){
        current = max = 0;
        tree_height(tHash[i]->root, &current, &max);
        //Se lleva un conteo de cual es el mayor
        if(max  > imax){
            imax = max;
            ii = i;
        }
    }
    //Se imprime el valor maximo
    printf("El arbol con mayor altura se encuentra en el indice %d de la tabla hash\n", ii);
    printf("El arbol es: ");
    print_inOrder_tree(tHash[ii]->root);
    printf("\n");
}

//Subrutina para calcular la altura del arbol
int tree_height(Root *root, int *current, int *max){
    if(root == NULL){
        return *current;
    }
    (*current)++;
    *current = tree_height(root->left, current, max);
    if(*current > *max) *max = *current;
    *current = tree_height(root->right, current, max);
    if(*current > *max) *max = *current;
    (*current)--;
    return *current;
}

//Subrutina para crear un nodo de la tabla Hash
hNode *crea_Hnodo(){
    //Se crea el espacio para el hNodo
    hNode *nodo = (hNode *)malloc(sizeof(hNode));
    if(nodo == NULL){
        printf("Error de asignacion de memoria.\n");
        return NULL;
    }

    //Se inicializa
    nodo->value =0;
    nodo->root = NULL;

    return nodo;
}

//Subrutina para crear un nodo del arbol binario
Root *crea_Tnodo(int val, Root *root){
    //Creamos espacio para el nodo
    Root *node = (Root *)malloc(sizeof(Root));
    //Le asignamos el valor
    node->value = val;
    //Verificamos si existe raiz
    if(root ==NULL){
        //De no existir, entonces esta sera la raiz
        return node;
    }
    //Si ya existe una raiz insertamos el nodo
    root = inserta_nodo(root, node);
    //Se retorna la raiz
    return root;
}

//Subrutina para insertar un nodo en un arbol binario
Root *inserta_nodo(Root *root, Root *nodo){
    if(root == NULL) return nodo;
    if(root->value > nodo->value){
        root->left = inserta_nodo(root->left, nodo);
    } else {
        root->right = inserta_nodo(root->right, nodo);
    }
    return root;
}

//Subrutina para crear valores aleatorios
int *genPop(int sz){
    //Se crea espacio para lista
    int *lista = (int *)calloc(sz, sizeof(int));
    if(lista == NULL){
        printf("Error al asignar la memoria.\n");
        return NULL;
    }
    //Se rellena la lista con valores aleatorios
    for(int i=0; i<sz; i++) lista[i] = (rand() % 101); //(0 - 100)

    //Se regresa la lista
    return lista;
}

//Subrutina para imprimir la tabla
void print_Thash(hNode **Node, int sz){
    //Imprimimos cada nodo
    for(int i=0; i<sz; i++){
        printf("En el nodo %d hay %d valores los cuales son:\n", i+1, Node[i]->value);
        print_inOrder_tree(Node[i]->root);
        printf("\n");
    }
}

//Subrutina para imprimir un arbol en orden
void print_inOrder_tree(Root *root){
    if(root == NULL) return;
    print_inOrder_tree(root->left);
    printf("%d\t",root->value);
    print_inOrder_tree(root->right);
}

//Subrutina para liberar la tabla hash
void liberar_hash(hNode **nodo, int sz){
    for(int i=0; i<sz; i++){
        liberar_arbol(nodo[i]->root);
        free(nodo[i]);
    }
    free(nodo);
}

//Subrutina para liberar un arbol
void liberar_arbol(Root *root){
    if (root == NULL) {
        return;
    }

    liberar_arbol(root->left);
    liberar_arbol(root->right);

    free(root); // Liberar el nodo actual
}
