/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1B************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngString(char *);
void fStr(char *,int);
char *strCpy(char *, char *);
int supStr(char *, char *);


int main(){
	srand(time(0));
	char src[100]={'\0'};
	char dst[100]={'\0'};

	//Obteniendo una longitud aleatoria
	int r = (rand() % 99) + 1;

	//Inicializando las cadenas
	fStr(src,r);
	fStr(dst,r);

	//Imprimiendo las cadenas iniciales
	printf("La cadena fuente es: **%s** \t Longitud: %d\n",src,lngString(src));
	printf("La cadena destino es: **%s**\t Longitud: %d\n",dst,lngString(dst));

	//Imprimiendo la cadena copiada
	printf("El resultado de la copia es: **%s**",strCpy(dst,src));
//	printf("El resultado de la copia es: %s",strCpy(dst,dst));

	return 0;
}

//subrutina para copiar de una cadena a otra;
char *strCpy(char *dst, char *src){
	char *temp=src;
	if(supStr(dst, src)) return '\0';
	int i=0;
	while(dst[i]!='\0'){
		if(src[i]=='\0'){
			dst[i]=src[i];
			return dst;
		}
		dst[i]=src[i];
		i++;
	}
	return dst;
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
	int r = (rand() % max) + 1;
	char c;
 	for(int i=0;i<r;i++){
		c = ((i + rand()) % 26) + 97;
		str[i]=c;
 	}
}

//Subrutina para comprobar que la cadena no se suporpone
int supStr(char *dst, char *src){

	char *temp;
	if(lngString(dst)>lngString(src)){
		temp = dst;
	} else {
		temp = src;
		src = dst;
	}

	for(int j=0;j<lngString(dst);j++){
		if(src==temp){
			printf("Error, parece que las cadenas se superponen.\n");
			return 1;
		}
		temp++;
	}
	return 0;
}
