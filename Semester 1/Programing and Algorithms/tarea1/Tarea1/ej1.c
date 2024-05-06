/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1/EJ1*************/
/*******Programacion y Algoritmos******/
/**************27/08/2023**************/
/**************************************/
/**************************************/

#include <stdio.h>
#include <math.h>

int main(void){
    char fecha[200]="";
    int dia, mes, anio;
    int mil,cen,dec1,dec2,uni1,uni2,cont;
    mil = cen = dec1 = dec2 = uni1 = uni2 = 0;
    cont=0;

    printf("Ingrese una fecha con formato dd/mm/aaaa (sustituya las diagonales por espacios): ");
    scanf("%d %d %d",&dia,&mes, &anio);

    //Descomposicion en decenas y unidades para el dia
    while(dia>=10){
        dia-=10;
        cont++;
    }
    dec1=cont;
    uni1 = dia;


    //Descomposicion de millares, centenas, decenas y unidades para anio
    //millares
    cont=0;
    while(anio>=1000){
        anio-=1000;
        cont++;
    }
    mil=cont;

    //centenas
    cont=0;
    while(anio>=100){
        anio-=100;
        cont++;
    }
    cen=cont;

    //decenas
    cont=0;
    while(anio>=10){
        anio-=10;
        cont++;
    }
    dec2=cont;

    //unidades
    uni2=anio;
    printf("\nLa fecha es: ");

        switch(dec1){
        case 0:
            printf("");
            break;
        case 1:
            printf("diez");
            break;
        case 2:
            printf("veinte");
            break;
        case 3:
            printf("treinta");
            break;
        case 4:
            printf("cuarenta");
            break;
        case 5:
            printf("cincuenta");
            break;
        case 6:
            printf("sesenta");
            break;
        case 7:
            printf("setenta");
            break;
        case 8:
            printf("ochenta");
            break;
        case 9:
            printf("noventa");
            break;
    }

    if(dec1>0 && uni1>0) printf(" y ");

    switch(uni1){
        case 0:
            printf("");
            break;
        case 1:
            printf("uno");
            break;
        case 2:
            printf("dos");
            break;
        case 3:
            printf("tres");
            break;
        case 4:
            printf("cuatro");
            break;
        case 5:
            printf("cinco");
            break;
        case 6:
            printf("seis");
            break;
        case 7:
            printf("siete");
            break;
        case 8:
            printf("ocho");
            break;
        case 9:
            printf("nueve");
            break;

    }
    printf(" de ");
     switch(mes){
        case 1:
            printf("enero");
            break;
        case 2:
            printf("febrero");
            break;
        case 3:
            printf("marzo");
            break;
        case 4:
            printf("abril");
            break;
        case 5:
            printf("mayo");
            break;
        case 6:
            printf("junio");
            break;
        case 7:
            printf("julio");;
            break;
        case 8:
            printf("agosto");
            break;
        case 9:
            printf("septiembre");
            break;
        case 10:
            printf("octubre");
            break;
        case 11:
            printf("noviembre");
            break;
        case 12:
            printf("diciembre");
            break;
        default:
            printf("ERROR");
            break;
    }

    printf(" del ");

    switch(mil){
        case 0:
        case 1:
            printf("");
            break;
        case 2:
            printf("dos");
            break;
        case 3:
            printf("tres");
            break;
        case 4:
            printf("cuatro");
            break;
        case 5:
            printf("cinco");
            break;
        case 6:
            printf("seis");
            break;
        case 7:
            printf("siete");
            break;
        case 8:
            printf("ocho");
            break;
        case 9:
            printf("nueve");
            break;

    }

    if(mil>0) printf(" mil ");

        switch(cen){
        case 0:
            printf("");
            break;
        case 1:
            printf("cien ");
            break;
        case 2:
            printf("doscientos ");
            break;
        case 3:
            printf("trescientos ");
            break;
        case 4:
            printf("cuatrocientos ");
            break;
        case 5:
            printf("quinientos ");
            break;
        case 6:
            printf("seiscientos ");
            break;
        case 7:
            printf("setecientos ");
            break;
        case 8:
            printf("ochocientos ");
            break;
        case 9:
            printf("novecientos ");
            break;

    }

    switch(dec2){
        case 0:
            printf("");
            break;
        case 1:
            printf("diez");
            break;
        case 2:
            printf("veinte");
            break;
        case 3:
            printf("treinta");
            break;
        case 4:
            printf("cuarenta");
            break;
        case 5:
            printf("cincuenta");
            break;
        case 6:
            printf("sesenta");
            break;
        case 7:
            printf("setenta");
            break;
        case 8:
            printf("ochenta");
            break;
        case 9:
            printf("noventa");
            break;
    }

    if(dec2>0 && uni2>0) printf(" y ");

    switch(uni2){
        case 0:
            printf("");
            break;
        case 1:
            printf("uno");
            break;
        case 2:
            printf("dos");
            break;
        case 3:
            printf("tres");
            break;
        case 4:
            printf("cuatro");
            break;
        case 5:
            printf("cinco");
            break;
        case 6:
            printf("seis");
            break;
        case 7:
            printf("siete");
            break;
        case 8:
            printf("ocho");
            break;
        case 9:
            printf("nueve");
            break;

    }
    return 0;
}

