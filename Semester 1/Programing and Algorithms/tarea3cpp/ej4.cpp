/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ4************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <complex>

using namespace std;

class Calculator {
public:
    // Suma de dos enteros
    int sum(int a, int b) const {
        return a + b;
    }

    // Suma de dos números de punto flotante
    double sum(double a, double b) const {
        return a + b;
    }

    // Suma de dos números complejos
    complex<double> sum(const complex<double>& a, const complex<double>& b) const {
        return a + b;
    }
};

int main() {
    Calculator calculator;

    // Suma de enteros
    int aEntero = 5, bEntero = 3;
    int sumaEnteros = calculator.sum(aEntero, bEntero);
    cout << "Suma de enteros (" << aEntero << " + " << bEntero << "): " << sumaEnteros << endl;

    // Suma de doubles
    double aDouble = 4.2, bDouble = 3.7;
    double sumaDoubles = calculator.sum(aDouble, bDouble);
    cout << "Suma de doubles (" << aDouble << " + " << bDouble << "): " << sumaDoubles << endl;

    // Suma de números complejos
    complex<double> numComplejo1(1.0, 2.0);
    complex<double> numComplejo2(2.5, 3.5);
    complex<double> sumaComplejos = calculator.sum(numComplejo1, numComplejo2);

    cout << "Suma de complejos (" << numComplejo1 << " + " << numComplejo2 << "): " << sumaComplejos << endl;

    return 0;
}
