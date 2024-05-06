/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ1************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <vector>

// Función para imprimir un vector de enteros
void imprimirVector(const std::vector<int>& vec) {
    std::cout << "Vector: [ ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << "]\n";
}

int main() {
    // Crear un vector e inicializarlo
    std::vector<int> miVector = {1, 2, 3, 4, 5};

    // Imprimir el vector
    std::cout << "Vector inicial:\n";
    imprimirVector(miVector);

    // Agregar elementos al final del vector
    miVector.push_back(6);
    miVector.push_back(7);

    // Imprimir el vector después de agregar elementos al final
    std::cout << "\nVector después de agregar elementos al final:\n";
    imprimirVector(miVector);

    // Agregar elementos en el interior del vector (en la posición 2)
    miVector.insert(miVector.begin() + 2, 8);
    miVector.insert(miVector.begin() + 2, 9);

    // Imprimir el vector después de agregar elementos en el interior
    std::cout << "\nVector después de agregar elementos en el interior:\n";
    imprimirVector(miVector);

    return 0;
}
