/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ1F************/
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
int **frecuencia(char *);
void imprimirMatriz(int **matriz, int filas, int columnas);
int concatena_str(char *str1, char *str2, char *str3);

int main(){

	srand(time(0));
	//se genera una cadena
	int **matriz;
	char str[100]={'\0'};
	fStr(str,30,2);

	printf("La cadena es: %s\n",str);

	matriz = frecuencia(str);
	imprimirMatriz(matriz,26,2);

	void free (void* matriz);
	return 0;
}

int **frecuencia(char *str){
	//Generando la matriz
	int **matriz;
	int filas=26;
	int columnas=2;
    matriz = (int **)malloc(filas * sizeof(int *));

    if (matriz == NULL) {
        perror("Error al asignar memoria para las filas");
        exit(1);
    }

    for (int i = 0; i < filas; i++) {
        matriz[i] = (int *)malloc(columnas * sizeof(int));

        if (matriz[i] == NULL) {
            perror("Error al asignar memoria para las columnas");
            exit(1);
        }
    }

    // Inicializar la matriz (opcional)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0;
        }
    }

	//Se genera el diccionario el cual contiene todos los caracteres
	char dicc[100]={'\0'};
	fStr(dicc,26,1);
	char temp[100]={'\0'};
	int r=0;
	int j=0;

	//Ahora, contamos cuantas veces aparece una letra dada del arreglo en la cadena
	for(int i=0;i<26;i++){
		r = encuentra_str(&dicc[i],str);
		if(r>0){
			matriz[j][0]=(int) dicc[i];
			matriz[j][1]=r;
			j++;
		}
	}
	return matriz;
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
	//Si se ingresa una d distinta de 0, la longitud ya no es variable sino fija
	char c;
 	for(int i=0;i<max;i++){
		switch(d){
		case 1:
			//Caracter en orden alfabetico
			c = i+97;
			break;
		case 2:
			//Caracter aleatorio del alfabeto
			c = ((i + rand()) % 26) + 97;
			break;
		default:
			//Caracter aleatorio de {a,b}
			c = ((i + rand()) % 2) + 97;
			break;
		}
		str[i]=c;
 	}
}

void imprimirMatriz(int **matriz, int filas, int columnas) {
	char c;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == 0) {
                return; // Salir de la función si se encuentra un 0
            }
            if(j==0){ /////Cuidado
				c=(char) matriz[i][j];
				printf("%c\t",c);
            } else {
				printf("%d\t", matriz[i][j]);
            }
        }
        printf("\n");
    }
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
//	if(supStr(str1,str2) || supStr(str1,str3)) return 0;

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
