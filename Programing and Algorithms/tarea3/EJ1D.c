/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1D************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngString(char *);
void fStr(char *,int);
int concatena_str(char *, char *, char *);
int supStr(char *, char *);

int main(){
	srand(time(0));
	char str1[100]={'\0'};
	char str2[100]={'\0'};
	char str3[100]={'\0'};

	//Obteniendo una longitud aleatoria
	int r = (rand() % 99) + 1;
//	int r=10;

	//Inicializando las cadenas
	fStr(str1,r);
	fStr(str2,r);
	fStr(str3,r);

	//imprimiendo las cadenas iniciales
	printf("La primer cadena es: **%s** \t Longitud: %d\n",str1,lngString(str1));
	printf("La segunda cadena es: **%s**\t Longitud: %d\n",str2,lngString(str2));
	printf("La tercer cadena es: **%s** \t Longitud: %d\n",str3,lngString(str3));
	int l_st=concatena_str(str1,str2,str3);
	printf("La concatenacion de la cadena es **%s** \t de longitud: %d:%d",str1,l_st,lngString(str1));

	return 0;
}

//Subrutina para concatenar string;
int concatena_str(char *str1, char *str2, char *str3){

	//Declaracion de variables
	int n1=lngString(str1);
	int n2=lngString(str2);
	int n3=lngString(str3);
	int j =0;
	int i = n1;

	//Revisando la superposicion
	if(supStr(str1,str2) || supStr(str1,str3)) return 0;

	//Concatenanco la primer cadena
	for(i;i<n1+n2+1;i++){
		if(j==0) {
			str1[i]=' ';
			i++;
		}
		if(i>=99) return 99;
		str1[i]=str2[j];
		j++;
	}

	//Reiniciando el contador
	j=0;

	//Concatenando segunda cadena
	for(i;i<n1+n2+n3+2;i++){
		if(j==0) {
			str1[i]=' ';
			i++;
		}
		if(i>=99) return 99;
		str1[i]=str3[j];
		j++;
	}
	return i;
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
