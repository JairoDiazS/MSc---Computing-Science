/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4/Header***********/
/*******Programacion y Algoritmos******/
/**************19/09/2023**************/
/**************************************/
/**************************************/

#ifndef EJ1_H
#define EJ1_H

//Declaraciones
unsigned char **pgmRead(char *,int *,int *);
int pgmWrite(char *, int, int, unsigned char **, char *);
void freePgm(unsigned char **);
void imprimirMatriz(unsigned char **, int, int);
unsigned char **crea_img(int, int);
unsigned char mat_mean(unsigned char **, int, int);
void mean_image(unsigned char **, int, int, int, char *);
double mat_grad(unsigned char **);
void gradient_image(unsigned char **, int, int, char *);

#endif
