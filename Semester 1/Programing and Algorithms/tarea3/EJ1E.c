/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1E************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngString(char *);
void fStr(char *,int, int);
int encuentra_str(char *, char *);

int main(){
	srand(time(0));
	char str1[100]={'\0'};
	char str2[100]={'\0'};

	//Obteniendo una longitud aleatoria
//	int r = (rand() % 99) + 1;

	//longitud fija
	int r=10;

	//Inicializando las cadenas
	//Longitud fija
	fStr(str1,r/2+1,1);
	fStr(str2,r*2,10);

	//Longitud variable
//	fStr(str1,r/2+1,0);
//	fStr(str2,r*2,0);


	//imprimiendo las cadenas iniciales
	printf("La subcadena cadena es: **%s** \t Longitud: %d\n",str1,lngString(str1));
	printf("La cadena es: **%s**\t Longitud: %d\n",str2,lngString(str2));

	printf("El numero de veces que se repite la cubcadena en la cadena es: %d", encuentra_str(str1, str2));

	return 0;
}

int encuentra_str(char *str1, char *str2){
	int r=0;
	int j = 0;
	int n1 = lngString(str1);
	int n2 = lngString(str2);

	for(int i=0; i<n2; i++){
		while(str1[j]==str2[j+i] && j+i<n2){
			if(j==n1-1){
				r++;
				break;
			}
			j++;
		}
		j=0;
	}
	return r;
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
void fStr(char *str,int max, int d){
	//Si se ingresa una d distinta de 0, la longitud ya no es variable sino fija
	int r = (rand() % max) + 1;
	if (d!=0) r=d;
	char c;
 	for(int i=0;i<r;i++){

		//Caracter en orden alfabetico
//		c = i+97;

		//Caracter aleatorio del alfabeto
//		c = ((i + rand()) % 26) + 97;

		//Caracter aleatorio de {a,b}
		c = ((i + rand()) % 2) + 97;
		str[i]=c;
 	}
}
