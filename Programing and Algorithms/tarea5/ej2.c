/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 5/EJ2-Cabecera********/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#include "ej2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Subrutina para desplegar en terminal
void imp_cons(struct estudiante *lista, int sz){
    //Se imprime la cabecera
    printf("No.\t\tNombre\t\t\t\tEdad\tPromedio\tGrupo\tTurno\n");
    //Imprimimos cada estudiante de la lista
    for(int i=0; i<sz; i++){
        printf("%d\t%30s\t\t%d\t%s\t\t%c\t%s\n",
        i+1, lista[i].nombre, lista[i].edad, lista[i].promedio,
        lista[i].info->grupo, lista[i].info->turno);
    }
}

//Subrutina para imprimir los datos a un archivo
void imp_file(char *fn, struct estudiante *lista, int sz){
    FILE *nfEstr = fopen(fn, "w");
    if (nfEstr == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    
    //Imprimimos cada estudiante de la lista
    for(int i=0; i<sz; i++){
        fprintf(nfEstr, "%d\t%30s\t%d\t%s\t%c\t%s\n",
        i+1, lista[i].nombre, lista[i].edad, lista[i].promedio,
        lista[i].info->grupo, lista[i].info->turno);
    }
    fclose(nfEstr);
}

// Función para leer estudiantes desde un archivo
struct estudiante *leer_file(char *fn, int *sz){
    FILE *archivo = fopen(fn, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    // Contar el número de lineas en el archivo para determinar el tamanio de la lista
    *sz = 0;
    char c;
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') {
            (*sz)++;
        }
    }

    // Volver al principio del archivo
    fseek(archivo, 0, SEEK_SET);

    // Crear una lista de estudiantes con el tamaño determinado
    struct estudiante *lista;
    struct escuela *temp;
    lista = (struct estudiante *)malloc(*sz * sizeof(struct estudiante));
    for(int i=0; i<*sz; i++){
        temp=(struct escuela *)malloc(sizeof(struct escuela));
        lista[i].info = temp;
    }

    // Leer los datos de los estudiantes desde el archivo
    for (int i = 0; i < *sz; i++) {
        int edad;
        char nombre[100];
        char promedio[10];
        char grupo;
        char turno[20];

        fscanf(archivo, "%d %s %d %s %c %s", &i, nombre, &edad, promedio, &grupo, turno);

        lista[i].nombre = strdup(nombre);
        lista[i].edad = edad;
        lista[i].promedio = strdup(promedio);
        lista[i].info->grupo = grupo;
        lista[i].info->turno = strdup(turno);
    }

    // Cerrar el archivo
    fclose(archivo);

    return lista;
}

//Ordenar por nombre
struct estudiante *ordena_nombre(struct estudiante *lista, int sz){
	int k=0;
	struct estudiante temp;
	for(int i=0; i<sz-1;i++){
		for(int j=0;j<sz-1-i;j++){
			k = compara_str(lista[j].nombre,lista[j+1].nombre);
			if(k>0){
				temp=lista[j];
				lista[j]=lista[j+1];
				lista[j+1]=temp;
			}
		}
	}
	return lista;
}

//Ordenar por edad
struct estudiante *ordena_edad(struct estudiante *lista, int sz){
    struct estudiante temp;
    for(int i=0; i< sz-1; i++){
        for(int j=0; j<sz-1-i; j++){
            if(lista[j].edad > lista[j+1].edad){
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    return lista;
}

//Ordenar por promedio
struct estudiante *ordena_prom(struct estudiante *lista, int sz){
    struct estudiante temp;
    for(int i=0; i< sz-1; i++){
        for(int j=0; j<sz-1-i; j++){
            if(calif2int(lista[j].promedio) > calif2int(lista[j+1].promedio)){
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    return lista;
}

//Subrutina para contar alumnos por grupo
int *cont_grupo(struct estudiante *lista, int sz){
    //Se crea un arreglo para almacenar el numero de estudiantes por grupo
    int *grps = (int *)calloc(5, sizeof(int)); //Inicializa en 0's
    for(int i=0; i<sz; i++){
        switch(lista[i].info->grupo){
            case 'A':
                grps[0]++;
                break;
            case 'B':
                grps[1]++;
                break;
            case 'C':
                grps[2]++;
                break;
            case 'D':
                grps[3]++;
                break;
            case 'E':
                grps[4]++;
                break;
        }
    }
    return grps;
}

//Subrutina para contar alumnos por turno
int *cont_turno(struct estudiante *lista, int sz){
    //Se crea un arreglo para almacenar el numero de estudiantes por turno
    int *trns = (int *)calloc(2, sizeof(int)); //Inicializa en 0's
    for(int i=0; i<sz; i++){
        if(strcmp(lista[i].info->turno,"Matutino")==0) trns[0]++;
        else if(strcmp(lista[i].info->turno,"Vespertino")==0) trns[1]++;
    }
    return trns;
}

//Subrutina para dar de alta un alumno a la lista
struct estudiante *alta_estudiante(struct estudiante *lista, int *sz){
    //Redefinimos el espacio para el estudiante nuevo
    lista = (struct estudiante *)realloc(lista, ((*sz)+1)*(sizeof(struct estudiante)));

    //Definimos donde guardaremos el nuevo estudiante
    struct estudiante *temp = (struct estudiante *)malloc(sizeof(struct estudiante));
    struct escuela *stemp = (struct escuela * )malloc(sizeof(struct escuela));
    temp->info = stemp;

    //Solicitamos la informacion
    int edad;
    char nombre[100];
    char promedio[10];
    char grupo;
    char turno[20];

    printf("Ingrese el nombre del alumno, cambie espacios por puntos...\n");
    scanf("%s",nombre);

    printf("\nIngrese la edad: ");
    scanf("%d", &edad);

    printf("\nIngrese el promedio. Formato USA.\n");
    scanf("%s",promedio);

    printf("\nIngrese el grupo con mayuscula: ");
    scanf(" %c", &grupo);

    printf("\nIngrese el turno, la primer letra mayuscula: ");
    scanf("%s", turno);

    temp->nombre = strdup(nombre);
    temp->edad = edad;
    temp->promedio = strdup(promedio);
    temp->info->grupo = grupo;
    temp->info->turno = strdup(turno);

    lista[*sz] = *temp;
    (*sz)++;

    return lista;
}

//Subrutina para dar de baja un alumno
struct estudiante *baja_estudiante(struct estudiante *lista, int *sz){
    printf("Ingrese el nombre del alumno a dar de baja, sustituya espacios por puntos: ");
    char nombre[100];
    scanf("%s", nombre);
    for(int i=0; i<*sz; i++){
        if(strcmp(lista[i].nombre,nombre)==0){
            //Liberamos la memoria que hay en este lugar
            free(lista[i].nombre);
            free(lista[i].promedio);
            free(lista[i].info->turno);
            free(lista[i].info);
            //Reorganizamos
            if (i < (*sz) - 1) lista[i] = lista[(*sz) - 1];
            (*sz)--;
            lista = (struct estudiante *)realloc(lista, (*sz)*sizeof(struct estudiante));
            return lista;
        }
    }
    printf("No se encontro al alumno, sin cambios.\n");
    return lista;
}

//Subrutina para comparar 2 strings
int compara_str(char *str1, char *str2){
	int n1=lngString(str1);
	int n2=lngString(str2);
	int n = (n1 > n2) ? n2 : n1;
	for(int i=0;i<n;i++){
		if(str1[i]!=str2[i]){
			return (int) (str1[i]-str2[i]);
		}
	}
	return 0;
}

//Subrutina para determinar la longitud de la cadena.
int lngString(char *str){
	int i=0;
	while(str[i]!='\0'){
		i++;
	}
	return i;
}

// Subrutina para obtener la calificación
enum calificaciones calif2int(const char *str){
    if (strcmp(str, "A+") == 0) return A_PLUS;
    if (strcmp(str, "A") == 0) return A;
    if (strcmp(str, "A-") == 0) return A_MINUS;
    if (strcmp(str, "B+") == 0) return B_PLUS;
    if (strcmp(str, "B") == 0) return B;
    if (strcmp(str, "B-") == 0) return B_MINUS;
    if (strcmp(str, "C+") == 0) return C_PLUS;
    if (strcmp(str, "C") == 0) return C;
    if (strcmp(str, "C-") == 0) return C_MINUS;
    if (strcmp(str, "D+") == 0) return D_PLUS;
    if (strcmp(str, "D") == 0) return D;
    if (strcmp(str, "D-") == 0) return D_MINUS;
    if (strcmp(str, "E+") == 0) return E_PLUS;
    if (strcmp(str, "E") == 0) return E;
    if (strcmp(str, "E-") == 0) return E_MINUS;
    if (strcmp(str, "F+") == 0) return F_PLUS;
    if (strcmp(str, "F") == 0) return F;
    if (strcmp(str, "F-") == 0) return F_MINUS;
    
    // Devolver un valor que indique que la cadena no es valida
    return -1;
}

//Subrutina para imprimir el menu
void impr_menu(){
    printf("\nEste programa maneja una estructura de datos de estudiantes y la ");
    printf("imprime en un archivo, puede modificar, ordenar y obtener informa");
    printf("cion acerca de la matricula de estudiantes. Por favor ingrese su ");
    printf("opcion:\n");
    printf("1.- Imprimir en consola.\n");
    printf("2.- Ordenar por nombre.\n");
    printf("3.- Ordenar por edad.\n");
    printf("4.- Ordenar por promedio.\n");
    printf("5.- Numero de estudiantes por grupo.\n");
    printf("6.- Numero de estudiantes por turno.\n");
    printf("7.- Baja de estudiante.\n");
    printf("8.- Alta de estudiante.\n");
    printf("9.- Finalizar programa.\n");
}

//Subrutina para liberar lista
void free_lista(struct estudiante *lista, int sz){
    for (int i = 0; i < sz; i++) {
        free(lista[i].nombre);
        free(lista[i].promedio);
        free(lista[i].info->turno);
        free(lista[i].info);
    }
    free(lista);
}
