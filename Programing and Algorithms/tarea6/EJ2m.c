/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 6/EJ1*************/
/*******Programacion y algoritmos******/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include "EJ2.c"

#define key 17

int main(int argc, char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Semilla de aleatorios
    srand(time(0));

    //Se obtiene el valor que se ingreso
    int sz = atoi(argv[1]);

    //Se genera de manera aleatoria una poblacion de la cantidad que se solicito
    int *pop = genPop(sz);

    //Se genera la tabla hash con los valores de entrada
    hNode **tabla_hash = crea_Thash(pop, sz, key);

    //Bucle para el menu
    int val, opt=0, temp;
    while(opt != 4){
        printf("La tabla hash tiene %d elementos, a continuacion ", sz);
        printf("se presenta un menu para manejar la tabla:\n");
        printf("1.- Insertar valor.\n");
        printf("2.- Imprimir tabla en orden.\n");
        printf("3.- Desplegar el indice y arbol con mayor profundidad.\n");
        printf("4.- Finalizar programa.\n");
        printf("Su opcion: ");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                printf("Ingrese el valor que desea agregar: ");
                scanf("%d", &val);
                //Se obtiene a donde pertenece y se inserta
                temp = val % key;
                crea_Tnodo(val, tabla_hash[temp]->root);
                tabla_hash[temp]->value++;
                sz++;
                break;
            case 2:
                //Se imprime la tabla hash
                print_Thash(tabla_hash, key);
                break;
            case 3:
                //Se imrpime el arbol mas grande
                max_height(tabla_hash, key);
                break;
            case 4:
                printf("Finalizando programa...\n");
                break;
        }
    }

    //Se liebra la tabla hash
    liberar_hash(tabla_hash, key);

}