/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 5/EJ2-Cabecera********/
/*******Programacion y algoritmos******/
/**************27/09/2023**************/
/**************************************/
/**************************************/

#ifndef EJ2_H
#define EJ2_H

struct escuela {
    char grupo; //A, B, C, D, E
    char *turno; //Vespertino, Matutino
};

struct estudiante {
    char *nombre;
    char *promedio; //Formato USA (A+,A,A-,B+,B,B-,...,F-)
    int edad;
    struct escuela *info;
};

enum calificaciones {
    F_MINUS, F, F_PLUS, E_MINUS, E, E_PLUS,
    D_MINUS, D, D_PLUS, C_MINUS, C, C_PLUS,
    B_MINUS, B, B_PLUS, A_MINUS, A, A_PLUS
};

void imp_file(char *, struct estudiante *, int);
void impr_menu();
struct estudiante *ordena_nombre(struct estudiante *, int);
int compara_str(char *, char *);
int lngString(char *);
enum calificaciones calif2int(const char *);
int *cont_grupo(struct estudiante *, int);
int *cont_turno(struct estudiante *, int);
struct estudiante *ordena_prom(struct estudiante *, int);
struct estudiante *ordena_edad(struct estudiante *, int);
struct estudiante *ordena_nombre(struct estudiante *, int);
struct estudiante *leer_file(char *, int *);
struct estudiante *alta_estudiante(struct estudiante *, int *);
struct estudiante *baja_estudiante(struct estudiante *, int *);
void imp_cons(struct estudiante *, int);
void free_lista(struct estudiante *, int);

#endif
