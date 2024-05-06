/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1A************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngString(char *);
void fStr(char *,int);

int main(){
	char str[100]={'\0'};
	//Descomentar este bloque de lineas si decides ingresar el maximo a mano
//	int max;
//	printf("Ingresa un numero entero, el cual sera le maximo, debe ser menor a 100, por lo que se genera una cadena de longitud aleatoria entre 1 y el max. \n Su numero: ");
//	scanf("%d", &max);
	int max=10; //Comentar esta linea s[i decide ingresar el maximo a mano
	fStr(str, max); //Genera la cadena
	printf("\n Su cadena generada es: **%s**",str);
	printf("\n Tu cadena tiene %d caracteres",lngString(str));
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

//Subrutina para generar una cadena de tamanio aleatorio
//desde tamanio 1 hasta max
void fStr(char *str,int max){
	srand(time(0));
	int r = (rand() % max) + 1;
	char c;
 	for(int i=0;i<r;i++){
		c = (i % 26) + 97;
		str[i]=c;
 	}
}
