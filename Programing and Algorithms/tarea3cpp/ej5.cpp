/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ5************/
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
};

// Definición de la función amiga
double calculateVolume(const Box& box) {
    return box.length * box.width * box.height;
}

int main() {
    // Crear un objeto Box
    Box myBox(3.0, 4.0, 5.0);

    // Imprimir las dimensiones de la caja
    cout << "Dimensiones de la caja:\n";
    cout << "Largo: " << myBox.getLength() << endl;
    cout << "Ancho: " << myBox.getWidth() << endl;
    cout << "Alto: " << myBox.getHeight() << endl;

    // Utilizar la función amiga para calcular el volumen
    double volume = calculateVolume(myBox);

    // Imprimir el volumen
    cout << "Volumen de la caja: " << volume << endl;

    return 0;
}
