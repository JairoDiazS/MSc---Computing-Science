/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 6/EJ2-Cabecera********/
/*******Programacion y algoritmos******/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#ifndef EJ2_H
#define EJ2_H

typedef struct treeNode {
    struct treeNode *left;
    struct treeNode *right;
    int value;
} Root;

typedef struct hashNode {
    Root *root;
    int value;
} hNode;

hNode **crea_Thash(int *, int, int);
void max_height(hNode **, int);
int tree_height(Root *, int *, int *);
hNode *crea_Hnodo();
Root *crea_Tnodo(int, Root *);
Root *inserta_nodo(Root *, Root *);
int *genPop(int);
void print_Thash(hNode **, int);
void print_inOrder_tree(Root *);
void liberar_arbol(Root *root);
void liberar_hash(hNode **, int);

#endif