/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1G************/
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
int concatena2(char *, char *);
char **tokenizar(char *, char **);
char *sin_repetir(char *);
void **gen_mtx(int fils, int cols, int sz);
char *strCpy(char *dst, char *src);
char *gen_palabras(char *, int);

int main(){
	srand(time(0));

	char str[500]={'\0'};
	gen_palabras(str,10);
	printf("Las palabras a analizar son : %s\n",str);
	sin_repetir(str);

	void free (void* tokens);
	return 0;

}

char *sin_repetir(char *str){
	char *tokens[100]={'\0'};
	tokenizar(str,tokens);
	char dicc[100]={'\0'};
	fStr(dicc,26,1);
	int i=0;
	int j;
	int r;
	int s=0;
	printf("Las palabras sin letras repetidas son: ");
	while(tokens[i]!=NULL){
		j=0;
		while(dicc[j]!='\0'){
			r=encuentra_str(&dicc[j],tokens[i]);
			if(r>1) s++;
			j++;
		}
		if(s==0) printf("\n%s\n",tokens[i]);
		s=0;
		i++;
	}
	return tokens[0];
}

char **tokenizar(char *str,char **tokens){

	int n=lngString(str);
	int i=0;
	int j=0;
	int k=0;
	char *temp = (char *)malloc(1000);
	for(i=0;i<n;i++){
		if(str[i]==' ' || i==n-1){
			if(i==n-1){
				temp[j]=str[i];
				j++;
			}
			temp[j]='\0';
			i++;
			j=0;
			tokens[k]=temp;
			k++;
			temp = (char *) malloc(100);
		}
		temp[j]=str[i];
		j++;
	}
	return tokens;
}

int concatena2(char *str1, char *str2){

	//Declaracion de variables
	int n1=lngString(str1);
	int n2=lngString(str2);
	int j =0;
	int i;

	//Revisando la superposicion
//	if(supStr(str1,str2)) return 0;

	//Concatenando la primer cadena
	for(i=n1;i<n1+n2+1;i++){
		if(j==0) {
			str1[i]=' ';
			i++;
		}
		if(i>=99) return 99;
		str1[i]=str2[j];
		j++;
	}

	str1[i]='\0';

	return i;
}

//Subrutina para encontrar una cadena1 en cadena2
int encuentra_str(char *str1, char *str2){
	int r=0;
	int j = 0;
//	int n1 = lngString(str1);
	int n1=1;//Modificaciooooon
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
	char c;
	int i=0;
 	for(i=0;i<max;i++){
		switch(d){
		case 1:
			//Caracter en orden alfabetico
			c =(char) (i%26)+97;
			break;
		case 2:
			//Caracter aleatorio del alfabeto
			c =(char) ((i + rand()) % 26) + 97;
			break;
		default:
			//Caracter aleatorio de {a,b}
			c =(char) ((i + rand()) % 2) + 97;
			break;
		}
		str[i]=c;
 	}
 	str[i]='\0';
}

//subrutina para copiar de una cadena a otra;
char *strCpy(char *dst, char *src){
//	if(supStr(dst, src)) return '\0';
	int i=0;
	while(i<99){
		if(src[i]=='\0'){
			dst[i]=src[i];
			return dst;
		}
		dst[i]=src[i];
		i++;
	}
	return dst;
}

char *gen_palabras(char *str, int n){
	char temp[100];
	for(int i=0;i<n;i++){
		fStr(temp,5,2);
		concatena2(str,temp);
	}
	return str;
}
