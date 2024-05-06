/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4/Header***********/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#ifndef TAREA4_H
#define TAREA4_H

//Declaraciones
unsigned char **pgmRead(char *,int *,int *);
int pgmWrite(char *, int, int, unsigned char **, char *);
void freePgm(unsigned char **);
void imprimirMatriz(unsigned char **, int, int);
unsigned char **crea_img(int, int);
double mat_mean(unsigned char **, int, int);
void mean_image(unsigned char **, int, int, int, char *);

#endif
