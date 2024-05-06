/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ6*************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *bSort(int, int *);
int *gen_sz_arr(int);
int *gen_arr_int(int n);
int **gen_n_arr(int,int *);
int *merge(int **, int, int *);

int main(){
	srand(time(0));
	//numero de arreglos
	int n=10;
	//tamanios de los arreglos
	int *sz_int=gen_sz_arr(n);
	int **arr = gen_n_arr(n,sz_int);
//	printf("Los arreglos sin ordenar son :/n");
//	imprimirArr(arr,n,sz_int);
	int *bigArr = merge(arr,n,sz_int);
// Liberar la memoria asignada
    free(sz_int);

    // Liberar la memoria de arr y sus subarreglos
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    // Liberar la memoria de bigArr
    free(bigArr);
	return 0;
}

int *merge(int **arr, int n, int *dim){
	//obtenemos la cantidad de espacio que se va a requerir
	int r=0;
	for(int i=0;i<n;i++) r+=dim[i];
	int *bigArr = (int *)malloc(r*sizeof(int));

	//Guardamos todos los valores de los arreglos en el gran arreglo
	int w=0;
	for(int i=0;i<n;i++){;
		for(int j=0;j<dim[i];j++){
			bigArr[w]=arr[i][j];
			w++;
		}
	}
	//regresamos el arreglo ordenado
	bigArr = bSort(w,bigArr);
	printf("El arreglo final es:\n");

	for(int i=0;i<w;i++){
		printf("%d\t",bigArr[i]);
	}
	return bigArr;
}

int **gen_n_arr(int n,int *sz_arr){
	int **arr = (int **)malloc(n*sizeof(int *));
	for(int i=0;i<n;i++){
		arr[i]=gen_arr_int(sz_arr[i]);
	}
	return arr;
}

int *gen_arr_int(int n){
	//generamos espacio para el arreglo
	int *arr = (int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++) arr[i] = rand();
	return bSort(n,arr);
}

int *gen_sz_arr(int n){
	//generamos espacio para el arreglo
	int *arr = (int *)malloc(n*sizeof(int));
	//tamanio entre 5 y 25
	for(int i=0;i<n;i++) arr[i] = (rand()%21)+5;
	return arr;
}

int *bSort(int n, int *arr){
	int temp;
	for(int i=0;i<n;i++){
		for(int j=0;j<n-i-1;j++){
			if(arr[j]>arr[j+1]){
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	return arr;
}

