/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ7************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <string>

using namespace std;

// Clase base (padre)
class Vehicle {
protected:
    string brand;

public:
    // Constructor de Vehicle
    Vehicle(const string& brand) : brand(brand) {}

    // Función para obtener la marca del vehículo
    string getBrand() const {
        return brand;
    }

    // Función virtual pura para mostrar información específica del vehículo
    virtual void displayInfo() const = 0;
};

// Clase derivada (hija) Car
class Car : public Vehicle {
private:
    int numDoors;

public:
    // Constructor de Car
    Car(const string& brand, int numDoors) : Vehicle(brand), numDoors(numDoors) {}

    // Función para obtener el número de puertas del carro
    int getNumDoors() const {
        return numDoors;
    }

    // Implementación de la función displayInfo para Car
    void displayInfo() const override {
        cout << "Carro de la marca: " << getBrand() << ", Número de puertas: " << numDoors << endl;
    }
};

// Clase derivada (hija) Bike
class Bike : public Vehicle {
private:
    string bikeType;

public:
    // Constructor de Bike
    Bike(const string& brand, const string& bikeType) : Vehicle(brand), bikeType(bikeType) {}

    // Función para obtener el tipo de bicicleta
    string getBikeType() const {
        return bikeType;
    }

    // Implementación de la función displayInfo para Bike
    void displayInfo() const override {
        cout << "Bicicleta de la marca: " << getBrand() << ", Tipo de bicicleta: " << bikeType << endl;
    }
};

int main() {
    // Crear un objeto Car
    Car myCar("Toyota", 4);

    // Crear un objeto Bike
    Bike myBike("Giant", "Montaña");

    // Llamar a la función displayInfo de cada objeto
    myCar.displayInfo();
    myBike.displayInfo();

    return 0;
}
