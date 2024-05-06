/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ3***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    int sz, i;
    cout << "Ingrese el tamanio del arreglo: ";
    cin >> sz;

    //Se genera un arreglo aleatorio del tamanio del usuario
    unique_ptr<int *[]> arr = make_unique<int *[]>(sz);
    for(i=0; i<sz; i++){
        arr[i] = new int(rand() % 101);
    }

    //Se imrpime el arreglo generado
    cout << "El arreglo generado es el siguiente: " << endl;
    for(i=0; i<sz; i++) cout << *arr[i] << endl;

    cout << "La memoria se libera de forma automatica" << endl;
    
    return 0;

}