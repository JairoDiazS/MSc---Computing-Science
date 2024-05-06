/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ4************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <vector>
#include <algorithm>

// Función personalizada para comparar pares según la longitud de la cadena
bool compararPorLongitud(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
    if (a.second.length() == b.second.length()) {
        return a.first < b.first;
    }
    return a.second.length() < b.second.length();
}

int main() {
    // Inicializar un vector de pares
    std::vector<std::pair<int, std::string>> miVector = {
        {3, "aaa"},
        {1, "bb"},
        {2, "cccc"},
        {4, "dd"}
    };

    // Imprimir el vector inicial
    std::cout << "Vector inicial:\n";
    for (const auto& par : miVector) {
        std::cout << "(" << par.first << ", " << par.second << ") ";
    }
    std::cout << "\n\n";

    // Ordenar el vector utilizando la función personalizada
    std::sort(miVector.begin(), miVector.end(), compararPorLongitud);

    // Imprimir el vector ordenado
    std::cout << "Vector ordenado por longitud de cadena:\n";
    for (const auto& par : miVector) {
        std::cout << "(" << par.first << ", " << par.second << ") ";
    }
    std::cout << "\n\n";

    // Ordenar el vector utilizando una función lambda
    std::sort(miVector.begin(), miVector.end(), [](const auto& a, const auto& b) {
        if (a.second.length() == b.second.length()) {
            return a.first < b.first;
        }
        return a.second.length() < b.second.length();
    });

    // Imprimir el vector ordenado con la función lambda
    std::cout << "Vector ordenado por longitud de cadena (con función lambda):\n";
    for (const auto& par : miVector) {
        std::cout << "(" << par.first << ", " << par.second << ") ";
    }
    std::cout << "\n";

    return 0;
}
