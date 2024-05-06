/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ6************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>

using namespace std;

class Box {
private:
    double length;
    double width;
    double height;

public:
    // Constructor
    Box(double l, double w, double h) : length(l), width(w), height(h) {}

    // Funciones para obtener dimensiones
    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    // Declaración de la función amiga
    friend double calculateVolume(const Box& box);

    // Sobrecarga del operador +
    Box operator+(const Box& other) const {
        // Sumar las dimensiones correspondientes
        return Box(length + other.length, width + other.width, height + other.height);
    }
};

// Definición de la función amiga
double calculateVolume(const Box& box) {
    return box.getLength() * box.getWidth() * box.getHeight();
}

int main() {
    // Crear dos objetos Box
    Box box1(3.0, 4.0, 5.0);
    Box box2(1.0, 2.0, 3.0);

    // Imprimir las dimensiones de la primera caja
    cout << "Dimensiones de la primera caja:\n";
    cout << "Largo: " << box1.getLength() << endl;
    cout << "Ancho: " << box1.getWidth() << endl;
    cout << "Alto: " << box1.getHeight() << endl;

    // Imprimir las dimensiones de la segunda caja
    cout << "\nDimensiones de la segunda caja:\n";
    cout << "Largo: " << box2.getLength() << endl;
    cout << "Ancho: " << box2.getWidth() << endl;
    cout << "Alto: " << box2.getHeight() << endl;

    // Sumar las dimensiones de las cajas usando la sobrecarga del operador +
    Box sumBox = box1 + box2;

    // Imprimir las dimensiones de la caja resultante
    cout << "\nDimensiones de la caja resultante:\n";
    cout << "Largo: " << sumBox.getLength() << endl;
    cout << "Ancho: " << sumBox.getWidth() << endl;
    cout << "Alto: " << sumBox.getHeight() << endl;

    // Utilizar la función amiga para calcular el volumen de la caja resultante
    double volume = calculateVolume(sumBox);

    // Imprimir el volumen de la caja resultante
    cout << "\nVolumen de la caja resultante: " << volume << endl;

    return 0;
}
