/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**********Tarea 6/EJ1-Cabecera********/
/*******Programacion y algoritmos******/
/**************08/10/2023**************/
/**************************************/
/**************************************/

#ifndef EJ1_H
#define EJ1_H

#define MAXLENGTH 255
#define MAXVALUE  255

unsigned char **transImg(unsigned char **, int, int, double);
double logMap(double);
unsigned char **pgmRead(char *, int *, int *);
int pgmWrite(char*, int, int, unsigned char **, char *);
unsigned char **crea_img(int, int);
void freePgm(unsigned char **);

#endif