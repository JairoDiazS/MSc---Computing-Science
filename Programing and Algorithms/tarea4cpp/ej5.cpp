/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ5************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

int main() {
    // Leer enteros desde la terminal con std::istream_iterator
    std::cout << "Ingrese una secuencia de enteros (Ctrl+D para finalizar):\n";
    std::vector<int> miVector{
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>()
    };

    // Ordenar el vector con std::sort
    std::sort(miVector.begin(), miVector.end());

    // Imprimir los valores ordenados con std::ostream_iterator
    std::cout << "Valores ordenados: ";
    std::ostream_iterator<int> salida(std::cout, " ");
    std::copy(miVector.begin(), miVector.end(), salida);
    std::cout << "\n";

    return 0;
}
