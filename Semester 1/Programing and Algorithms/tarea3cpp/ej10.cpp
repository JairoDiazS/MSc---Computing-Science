/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ10***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor por defecto
    Complex() : real(0.0), imag(0.0) {}

    // Constructor con parámetros
    Complex(double r, double i) : real(r), imag(i) {}

    // Sobrecarga del operador de suma
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Sobrecarga del operador de resta
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Sobrecarga del operador de multiplicación
    Complex operator*(const Complex& other) const {
        return Complex((real * other.real) - (imag * other.imag),
                       (real * other.imag) + (imag * other.real));
    }

    // Sobrecarga del operador de división
    Complex operator/(const Complex& other) const {
        double denominator = (other.real * other.real) + (other.imag * other.imag);
        return Complex(((real * other.real) + (imag * other.imag)) / denominator,
                       ((imag * other.real) - (real * other.imag)) / denominator);
    }

    friend ostream& operator<<(ostream& os, const Complex& c);
};

// Función amiga para mostrar el número complejo en la forma a + bi
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real << " + " << c.imag << "i";
    return os;
}

int main() {
    // Crear números complejos
    Complex a(2.0, 3.0);
    Complex b(1.0, 4.0);

    // Mostrar los números complejos
    cout << "Número complejo a: " << a << endl;
    cout << "Número complejo b: " << b << endl;

    // Realizar operaciones
    Complex sum = a + b;
    Complex diff = a - b;
    Complex prod = a * b;
    Complex div = a / b;

    // Mostrar resultados
    cout << "Suma: " << sum << endl;
    cout << "Resta: " << diff << endl;
    cout << "Multiplicación: " << prod << endl;
    cout << "División: " << div << endl;

    return 0;
}
