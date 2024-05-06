/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ1************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <string>

using namespace std;

class Car {
private:
    string make;
    string model;
    int year;

public:
    // Constructor
    Car(const string& make, const string& model, int year)
        : make(make), model(model), year(year) {}

    // Funciones set
    void setMake(const string& make) {
        this->make = make;
    }

    void setModel(const string& model) {
        this->model = model;
    }

    void setYear(int year) {
        this->year = year;
    }

    // Funciones get
    string getMake() const {
        return make;
    }

    string getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }
};

int main() {
    // Crear un objeto Car
    Car myCar("Toyota", "Camry", 2022);

    // Acceder a los datos usando funciones get
    cout << "Make: " << myCar.getMake() << endl;
    cout << "Model: " << myCar.getModel() << endl;
    cout << "Year: " << myCar.getYear() << endl;

    // Modificar los datos usando funciones set
    myCar.setMake("Honda");
    myCar.setModel("Accord");
    myCar.setYear(2023);

    // Imprimir los datos actualizados
    cout << "\nDatos actualizados:\n";
    cout << "Make: " << myCar.getMake() << endl;
    cout << "Model: " << myCar.getModel() << endl;
    cout << "Year: " << myCar.getYear() << endl;

    return 0;
}
