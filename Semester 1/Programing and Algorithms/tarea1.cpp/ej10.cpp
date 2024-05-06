/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 1 - EJ10***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    cout << "Programa que implementa una division con manejo de error (segura)" << endl;
    double num, den;
    cout << "Ingrese el numerador: ";
    cin >> num;
    cout << "Ingrese el denominador: ";
    cin >> den;
    cout << "El resultado de la division es: " << safeDivision(num, den) << endl;

    return 0;
}