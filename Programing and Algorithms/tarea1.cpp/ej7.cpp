/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 1 - EJ7/EJ8*********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    //Se crea un apuntador a la clase padre
    figuraGeometrica *figura;
    //Se crea un circulo
    circulo c1 = circulo(1);

    //Asignamos el puntero
    figura = &c1;

    //Obtenemos el area del circulo
    figura->setArea();

    //Se imprime
    cout << "Se tiene un circulo de radio 1 con area " << figura->area << endl;

    return 0;

}