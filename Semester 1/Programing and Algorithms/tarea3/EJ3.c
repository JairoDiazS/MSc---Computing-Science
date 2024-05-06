/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ3*************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generar_mat(int **, int , int);
void max_fc(int , int);
int bytes0(int x);

int main(){
	srand(time(0));
	max_fc(rand()%10+1,rand()%10+1);
	return 0;
}

void max_fc(int fils, int cols){
	int matriz[fils][cols];
	int mxf[fils];
	int mxc[cols];
	int nbytes=0;

	printf("La matriz generada es: \n");
	for(int i=0; i<fils;i++){
		for(int j=0;j<cols;j++){
			matriz[i][j]=rand();
			printf("%d\t",matriz[i][j]);
			nbytes+=bytes0(matriz[i][j]);
		}
		printf("\n");
	}

	int maxf =0;
	int maxc =-1;
	int temp=0;
	printf("\nLos maximos por fila: \n");
	for(int i=0;i<fils;i++){
		for(int j=0;j<cols;j++){
				temp=matriz[i][j];
			maxc = (maxc>temp) ? maxc : temp;
		}
		mxc[i]=maxc;
		printf("%d\t",maxc);
		maxc=-1;
	}
	printf("\nLos maximos por columna son :\n");
	for(int i=0;i<cols;i++){
		for(int j=0;j<fils;j++){
				temp=matriz[j][i];
			maxc = (maxc>temp) ? maxc : temp;
		}
		mxf[i]=maxc;
		printf("%d\t",maxc);
		maxc=-1;
	}
	printf("\nEl numero de bytes en 0 que tiene esta matriz es %d",nbytes);
}

int bytes0(int x){
	int bins[32]={0};
	for(int i=31;i>=0;i--){
		bins[i]=x%2;
		x/=2;
	}
	int k=0;
	int r=0;
	for(int i=0;i<32;i++){
		if(i==8 || i==16 || i==24) k=0;
		if(bins[i]==0) k++;
		if(k==4) r++;
	}
	return r;
}
