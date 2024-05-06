/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1C************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngString(char *);
void fStr(char *,int);
int compara_str(char *, char *);

int main(){
	srand(time(0));

	char str1[100]={'\0'};
	char str2[100]={'\0'};

	//Obteniendo una longitud aleatoria
	int r = (rand() % 99) + 1;

	//Inicializando las cadenas
	fStr(str1,r);
	fStr(str2,r);

	//Imprimiendo las cadenas iniciales
	printf("La primer cadena es: **%s** \t Longitud: %d\n",str1,lngString(str1));
	printf("La segunda cadena es: **%s**\t Longitud: %d\n",str2,lngString(str2));
	printf("El resultado de la comparacion es: %d", compara_str(str1,str2));

	//Comparación de la misma cadena
//	printf("El resultado de la comparacion es: %d", compara_str(str1,str1));


	return 0;
}

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
