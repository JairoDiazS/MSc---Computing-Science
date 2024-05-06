/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 3/EJ2*************/
/*******Programacion y Algoritmos******/
/**************10/09/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void caminata();

int main(){
	srand(time(0));
	caminata();
	return 0;
}

void caminata(){
	int matriz[10][10]={0};

	//El recorrido se va a iniciar en la casilla (0,0)
	int i=0;
	int j=0;
	int k=0;
	int w=1;
	while(k<10){
		matriz[i][j]=w;
		switch(rand()%4){
			case 0:
				if(j+1<10 && matriz[i][j+1]==0){
					j++;
					k=0;
					w++;
					break;
				}

			case 1:
				if(i+1<10 && matriz[i+1][j]==0){
					i++;
					k=0;
					w++;
					break;
				}

			case 2:
				if(j-1>-1 && matriz[i][j-1]==0){
					j--;
					k=0;
					w++;
					break;
				}

			case 3:
				if(i-1>-1 && matriz[i-1][j]==0){
					i--;
					k=0;
					w++;
					break;
				}
		}
		k++;
	}
	printf("\n");
	for (int fil = 0; fil < 10; fil++) {
        for (int col = 0; col < 10; col++) {
            printf("%d\t", matriz[fil][col]);
        }
        printf("\n");
    }

}
