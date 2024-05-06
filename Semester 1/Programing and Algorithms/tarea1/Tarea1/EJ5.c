/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ5*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

void base(int, int);


int main(){
	int a, b;
	printf("Este programa toma dos numeros, el primero un numero en decimal, ");
	printf("El segundo la base a la que se quiere transformar y devuelve la ");
	printf("transformacion de forma inversa. Ingrese los numeros separados por ");
	printf("espacio: ");
	scanf("%d %d",&a,&b);
	printf("\nLa transformacion es: ");
	base(a,b);
	return 0;
}

void base(int a, int base){
    char b;
    int c,d;
    if(a==0) printf("0");
    while(a>0){
		d=a % base;
		if(d<9) c=48;
		else c=87;
        b = d + c;
        printf("%c", b);
        a /= base;
    }
}
