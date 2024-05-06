/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ3************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int main() {
    // Semilla para generar números aleatorios
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Tamaño del vector
    const int tamano = 10;

    // Inicializar un vector de forma aleatoria
    std::vector<int> miVector;
    for (int i = 0; i < tamano; ++i) {
        miVector.push_back(std::rand() % 100);  // Números aleatorios entre 0 y 99
    }

    // Imprimir el vector inicial
    std::cout << "Vector inicial:\n";
    for (int num : miVector) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // Ordenar el vector
    std::sort(miVector.begin(), miVector.end());

    // Imprimir el vector ordenado
    std::cout << "Vector ordenado:\n";
    for (int num : miVector) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";

    // Encontrar el elemento más grande y el más pequeño
    int maximo = *std::max_element(miVector.begin(), miVector.end());
    int minimo = *std::min_element(miVector.begin(), miVector.end());

    std::cout << "Elemento más grande: " << maximo << "\n";
    std::cout << "Elemento más pequeño: " << minimo << "\n\n";

    // Aplicar un shuffle al vector
    std::random_shuffle(miVector.begin(), miVector.end());

    // Imprimir el vector después de aplicar el shuffle
    std::cout << "Vector después de aplicar shuffle:\n";
    for (int num : miVector) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}
