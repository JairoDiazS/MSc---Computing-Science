/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ1***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"
#define sz 5

using namespace std;

int main(){
    //Se genera un arreglo
    double arr[sz];
    randArray(arr, sz);

    //Se imrpime el arreglo generado
    cout << "El arreglo generado es el siguiente: " << endl;
    int i;
    for(i=0; i<sz; i++) cout << arr[i] << endl;

    //Se obtiene la suma
    double sum = sumaArreglo(arr, sz);

    //Se muestra al usuario
    cout << "La suma del arreglo es: " << sum << endl;

    return 0;
}