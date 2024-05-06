/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ5***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    //Vamos a crear un vector de enteros
    vector<int> vec = {1, 2, 3, 4, 5, 6};

    cout << "La capacidad inicial del vector es: " << vec.capacity() << endl;
    for(int i=0; i<6; i++) cout << vec[i] << endl;

    //obtenemos un valor aleatorio entre 1 y 100 y rellenamos con esos numeros
    int temp = (rand() % 100) + 1;
    dangling_function(vec, temp);
    cout << "La capacidad del vector tras la funcion es: " << vec.capacity() << endl;
    for(int i=0; i<6; i++) cout << vec[i] << endl;

    //volvemos a rellenarlo
    temp = (rand() % 100) + 1;
    dangling_function(vec, temp);
    cout << "La capacidad del vector tras la funcion es: " << vec.capacity() << endl;
    for(int i=0; i<6; i++) cout << vec[i] << endl;

    /*La funcion implementada, al pasar el valor del vector como referencia y
    manipularlo dentro de si, podria ocasionar que se llame a un realloc y se mueva
    la memoria hacia otro lugar, dejandola inaccesible desde el main, pues la
    referencia que se tiene en el main de esta no ha sido modificada*/
    return 0;
}