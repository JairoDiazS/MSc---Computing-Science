/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ5*************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lngSp(char *str, char c);
int lngString(char *str);
char **tokenizar(char *str, char c);
char *gen_str_imprim();

int main(){
	//Opcional srand, sino puedes generar la misma cadena para tokenizar
	//por diferentes separadores
//	srand(time(0));
	char *str;
	char **tokens;
	//Separador
	char c = 'a';
	str = gen_str_imprim();
	printf("La cadena sin tokenizar es: %s\n",str);
	printf("\nLos tokens de la cadena son:\n");
	tokens = tokenizar(str,c);
	// Liberar la memoria de tokens
	int g=0;
    while(tokens[g]!='\0') {
        free(tokens[g]);
        g++;
    }
    free(tokens);

    // Liberar la memoria de str
    free(str);
	return 0;
}

char **tokenizar(char *str, char c){

	int n=lngString(str);
	int i=0;
	int j=0;
	int k=0;
	int r=0;
	int s=0;
	char **tokens;
	//contamos las veces que aparece el separador
	for(int w=0;w<n;w++){
		if(str[w]==c) r++;
	}
	//si no se ecnuentra regresamos null
	if(r==0) return;
	tokens = (char **)malloc((r+2)*sizeof(char *));
	//Creamos los espacios para cada token
	r=0;
	for(int w=0;w<n;w++){
		if(str[w]==c || w==n-1){
			tokens[r]=(char *)malloc((w+1)*sizeof(char));
			r++;
			s=0;
		}
		s++;
	}
	//Colocamos los tokens
	for(i=0;i<n;i++){
		if(str[i]==c || i==n-1){
			if(i==n-1){
				tokens[k][j] = str[i];
				j++;
			}
			tokens[k][j] = '\0';
			i++;
			j=0;
			k++;
		}
		tokens[k][j]=str[i];
		j++;
	}
	for(int t=0;t<r;t++){
		printf("%s\n",tokens[t]);
	}
	tokens[r]='\0';
	return tokens;
}

//Subrutina para determinar la longitud de la cadena.
int lngString(char *str){
	int i=0;
	while(str[i]!='\0'){
		i++;
	}
	return i;
}

//Subrutina para determinar la longitud de la cadena dado un caracter
int lngSp(char *str, char c){
	int i=0;
	while(str[i]!=c){
		i++;
	}
	return i;
}
//Subrutina que genera una cadena de caracteres imprimibles
char *gen_str_imprim(){
	//generamos tamanios aleatorios entre 30 y 100;
	int ap=(rand()%101)+30;

	//generamos espacio en memoria para almacenar el string;
	char *str=(char *)malloc((ap+1)*sizeof(char));

	//generamos el nonbre de forma aleatoria
	int i;
	char c;
	for(i=0;i<ap;i++){
		str[i] = (char) ((i + rand()) % 95) + 32;
	}
	//a;adimos el caracter nulo al final
	str[i]='\0';

	//regresamos la direccion de memoria del arreglo
	return str;
}
