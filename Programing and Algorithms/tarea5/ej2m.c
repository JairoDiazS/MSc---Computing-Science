/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 5/EJ2*************/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#include "ej2.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){
    // Verifica si se proporcionaron argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    //Inicializamos el valor, se actualizara para el tamanio de lista
    int *sz =(int *)calloc(1,sizeof(int));
    /*Creamos un apuntador a la estructura de datos estudiante para generar un 
    vector (lista) de estudiantes y manejar con esto los ordenamientos e 
    impresion al archivo, etc.
    Creamos la lista, inicialmente sera para lamacenar un estudiante, sin 
    embargo, se ira actualizando el tamanio segun el numero de estudiantes
    que se tengan.*/
    struct estudiante *list_std;
    list_std = leer_file(argv[1],sz);
    
    //Creamos una variable para la lectura de la opcion
    int opt;
    char grp;
    char *turno;
    int *cnts;
    while(opt!=9){
        //Imprimimos el menu
        impr_menu();
        //Leemos la opcion
        scanf("%d",&opt);
        switch(opt){
            case 1:
                printf("Imprimendo archivo...\n");
                imp_cons(list_std,sz[0]);
                printf("...Archivo impreso.\n");
                break;
            case 2:
                printf("Ordenando los alumnos por nombre...\n");
                list_std = ordena_nombre(list_std, *sz);
                printf("...se han ordenado.\n");
                break;
            case 3:
                printf("Ordenando los alumnos por edad...\n");
                list_std = ordena_edad(list_std, *sz);
                printf("...se han ordenado.\n");
                break;
            case 4:
                printf("Ordenando los alumnos por promedio...\n");
                list_std = ordena_prom(list_std, *sz);
                printf("...se han ordenado.\n");
                break;
            case 5:
                printf("Contando por grupos...\n");
                cnts = cont_grupo(list_std, *sz);
                printf("En el grupo A hay %d alumnos.\n",cnts[0]);
                printf("En el grupo B hay %d alumnos.\n",cnts[1]);
                printf("En el grupo C hay %d alumnos.\n",cnts[2]);
                printf("En el grupo D hay %d alumnos.\n",cnts[3]);
                printf("En el grupo E hay %d alumnos.\n",cnts[4]);
                printf("...fin del conteo.\n");
                break;
            case 6:
                printf("Contando por turnos...\n");
                cnts = cont_turno(list_std, *sz);
                printf("En el turno Matutino hay %d alumnos.\n",cnts[0]);
                printf("En el turno Matutino hay %d alumnos.\n",cnts[1]);
                printf("...fin del conteo.\n");
                break;
            case 7:
                printf("Dando de baja un estudiante...\n");
                list_std = baja_estudiante(list_std, sz);
                printf("...baja finalizada.\n");
                break;
            case 8:
                printf("Dando de alta un estudiante...\n");
                list_std = alta_estudiante(list_std, sz);
                printf("...alta finalizada.\n");
                break;
            case 9:
                printf("Impresion final de la lista...\n");
                imp_file("out.txt", list_std, *sz);
                printf("...finalizando el programa.\n");
                break;
            default :
                printf("Opcion invalida, intente otra opcion.\n");
        }
    }
    free(sz);
    free(cnts);
    free_lista(list_std, *sz);
    return 0;
}