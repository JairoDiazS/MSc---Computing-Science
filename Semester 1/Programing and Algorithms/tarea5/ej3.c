/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 5/EJ3-Cabecera********/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#include "ej3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Subrutina para obtener las frecuencias de cada letra
NODE *leer_archivo(char *nfile, NODE *hojas){
    //Abrimos el archivo
    FILE *archivo = fopen(nfile, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }
    //Caracter para recorrer
    char c;

    //Recorriendo el archivo
    while((c = fgetc(archivo)) != EOF){
        if(isalpha(c)){
            c= tolower(c);
            //Incrementamos el valor
            hojas[c-'a'].freq++;
        }
    }

    fclose(archivo);
    return hojas;
}

//Subrutina para crear un nodo para cada letra
NODE *init_leaf(){
    //Definimos el espacio para guardarlo en un arreglo cada hoja
    NODE *hojas = (NODE *)malloc(26*sizeof(NODE));
    for(int i=0; i<26; i++){
        hojas[i].left = hojas[i].right = NULL;
        hojas[i].caracter = 'a' + i;
        hojas[i].freq = 0; //Inicializando en 0 las frecuencias
    }
    return hojas;
}

NODE *arbol_huffman(NODE *hojas){
    printf("control0");
    //Buscamos la maxima frecuencia
    int max=0;
    for(int i=0; i< 26; i++){
        if(max<hojas[i].freq){
            max=hojas[i].freq;
        }
    }
    max++;
    int lwr1=max, lwr2=max;
    int m1=0, m2=0;
    int sz=26;
    int cont=0;
    int pos=0;
    NODE *temp;
    NODE *leaf_temp;
    while(sz>1){
        //Buscamos las dos menores frecuencias
        for(int i=0; i<26; i++){
            if(lwr1>hojas[i].freq){
                lwr2=lwr1;
                m2=m1;
                lwr1=hojas[i].freq;
                m1=i;
            } else if (lwr2>hojas[i].freq && m1 != i){
                lwr2 = hojas[i].freq;
                m2=i;
            }
        }
        /*Ahora que se ha localizado la posicion y las frecuencias minimas
        creamos un nodo que sera el padre de estas hojas*/
        temp = (NODE *)malloc(sizeof(NODE));
        //asignamos sus valores
        temp->right = &hojas[m1];
        temp->left = &hojas[m2];
        temp->freq = hojas[m1].freq + hojas[m2].freq;
        //Asignamos un caracter nulo
        temp->caracter = '\0';

        /*Reasignamos un nuevo arreglo de hojas, quitando las anteriores y 
        anadiendo la hoja padre*/
        sz--;
        leaf_temp = (NODE *)malloc(sz*sizeof(NODE));
        cont=0;
        pos=0;
        while(cont < sz){
            if(cont!= m1 && cont!= m2){
                leaf_temp[cont]=hojas[cont];
                pos++;
            }
            cont++;
        }
        printf("%d\n",pos);
        leaf_temp[sz-1]=*temp;
        //cambiamos el apuntador de hojas al nuevo
        hojas = leaf_temp;
    }
    return hojas;
}

void print_arbol(NODE *root){
    if(root=NULL) return;

    print_arbol(root->left);

    printf("%c\t%d\n",root->caracter, root->freq);

    print_arbol(root->right);
}
