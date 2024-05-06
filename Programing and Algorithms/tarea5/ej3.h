/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 5/EJ3-Cabecera********/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#ifndef EJ3_H
#define EJ3_H

typedef struct Node {
    struct Node *left;
    char caracter;
    int freq;
    struct Node *right;
}NODE;

NODE *leer_archivo(char *, NODE *);
NODE *init_leaf();
NODE *arbol_huffman(NODE *);
void print_arbol(NODE *);

#endif