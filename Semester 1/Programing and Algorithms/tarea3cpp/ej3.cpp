/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 3 - EJ3************/
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
    // Constructor predeterminado
    Car() : make(""), model(""), year(0) {}

    // Constructor parametrizado
    Car(const string& make, const string& model, int year)
        : make(make), model(model), year(year) {}

    // Destructor
    ~Car() {
        cout << "Destructor llamado para: " << make << " " << model << endl;
    }

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
    // Crear un objeto Car usando el constructor predeterminado
    Car defaultCar;
    cout << "Default Car:\n";
    cout << "Make: " << defaultCar.getMake() << endl;
    cout << "Model: " << defaultCar.getModel() << endl;
    cout << "Year: " << defaultCar.getYear() << endl;

    // Crear un objeto Car usando el constructor parametrizado
    Car parametrizedCar("Toyota", "Camry", 2022);
    cout << "\nParametrized Car:\n";
    cout << "Make: " << parametrizedCar.getMake() << endl;
    cout << "Model: " << parametrizedCar.getModel() << endl;
    cout << "Year: " << parametrizedCar.getYear() << endl;

    // Modificar los datos usando funciones set
    parametrizedCar.setMake("Honda");
    parametrizedCar.setModel("Accord");
    parametrizedCar.setYear(2023);

    // Imprimir los datos actualizados
    cout << "\nDatos actualizados:\n";
    cout << "Make: " << parametrizedCar.getMake() << endl;
    cout << "Model: " << parametrizedCar.getModel() << endl;
    cout << "Year: " << parametrizedCar.getYear() << endl;

    return 0;
}
