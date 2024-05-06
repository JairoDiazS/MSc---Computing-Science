/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ2************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>

// Función para limpiar y normalizar una palabra
std::string limpiarPalabra(const std::string& palabra) {
    std::string limpia = palabra;
    // Convertir a minúsculas
    for (char& c : limpia) {
        c = tolower(c);
    }
    // Eliminar caracteres no alfabéticos
    limpia.erase(std::remove_if(limpia.begin(), limpia.end(), [](char c) { return !isalpha(c); }), limpia.end());
    return limpia;
}

int main() {
    std::map<std::string, int> frecuenciaPalabras;
    std::string texto;

    std::cout << "Ingrese un texto (presione Ctrl + D en una nueva línea para finalizar):\n";

    // Leer el texto desde la terminal
    while (std::cin >> texto) {
        // Limpiar y normalizar la palabra antes de contabilizarla
        std::string palabra = limpiarPalabra(texto);
        if (!palabra.empty()) {
            frecuenciaPalabras[palabra]++;
        }
    }

    // Imprimir la frecuencia de las palabras
    std::cout << "\nFrecuencia de palabras:\n";
    for (const auto& par : frecuenciaPalabras) {
        std::cout << par.first << ": " << par.second << " veces\n";
    }

    return 0;
}
