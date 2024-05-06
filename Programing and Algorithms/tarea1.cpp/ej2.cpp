/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ2***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    int sz;
    cout << "Ingrese el tamanio del arreglo: ";
    cin >> sz;

    //Se genera un arreglo aleatorio del tamanio del usuario
    double *arr = (double *)calloc(sz, sizeof(double));
    randArray(arr, sz);

    //Se imrpime el arreglo generado
    cout << "El arreglo generado es el siguiente: " << endl;
    int i;
    for(i=0; i<sz; i++) cout << arr[i] << endl;

    cout << "Liberando arreglo..." << endl;
    free(arr);
    cout << "...arreglo liberado." << endl;
    
    return 0;
}