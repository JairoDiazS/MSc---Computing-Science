/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ4*************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *gen_nombres();
char **crea_arreglo(int);
char **ordena(char **arreglo, int n);
int compara_str(char *, char *);
int lngString(char *);

int main(){
	srand(time(0));
	char **arreglo;
	int n=5;
	arreglo=crea_arreglo(n);
	printf("El arreglo sin ordenar es: \n\n");
	for(int i=0;i<n;i++){
		printf("%s\n",arreglo[i]);
	}
	ordena(arreglo,5);
	printf("\nEl arreglo ordenado es: \n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", arreglo[i]);
        free(arreglo[i]); // Liberamos la memoria de cada nombre
    }
    free(arreglo); // Liberamos la memoria del arreglo de nombres
	return 0;
}

char **ordena(char **arreglo, int n){
	int k=0;
	char *temp;
	for(int i=0; i<n-1;i++){
		for(int j=0;j<n-1-i;j++){
			k = compara_str(arreglo[j],arreglo[j+1]);
			if(k>0){
				temp=arreglo[j];
				arreglo[j]=arreglo[j+1];
				arreglo[j+1]=temp;
			}
		}
	}
	return arreglo;
}

char **crea_arreglo(int n){
	char **lista;
	lista=(char **)malloc(n*sizeof(char *));
	for(int i=0;i<n;i++){
		lista[i]=gen_nombres();
	}
	return lista;
}

char *gen_nombres(){
	//generamos tres tamanios aleatorios entre 5 y 14;
	int ap=(rand()%10)+5;
	int am=(rand()%10)+5;
	int nm=(rand()%10)+5;

	//generamos espacio en memoria para almacenar el string;
	char *str=(char *)malloc((ap+am+nm+3)*sizeof(char));

	//generamos el nonbre de forma aleatoria
	int i;
	char c;
	for(i=0;i<ap+am+nm+2;i++){
		if(i==ap || i==ap+am+1){
			str[i] = ' ';
			i++;
		}
		str[i] = (char) ((i + rand()) % 26) + 97;
	}
	//a;adimos el caracter nulo al final
	str[i]='\0';

	//regresamos la direccion de memoria del arreglo
	return str;
}

//Subrutina para comparar 2 strings
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
