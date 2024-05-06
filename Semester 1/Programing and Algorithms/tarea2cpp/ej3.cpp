/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ3***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<pair<string, int>> lista;
    int numPersonas;

    cout << "Ingrese el número de personas: ";
    cin >> numPersonas;

    if (numPersonas < 1) {
        cerr << "Número de personas no válido. Debe ser al menos 1." << endl;
        return 1;
    }

    // Solicitar al usuario que ingrese nombres y edades
    for (int i = 0; i < numPersonas; ++i) {
        string nombre;
        int edad;

        cout << "Ingrese el nombre de la persona " << i + 1 << ": ";
        cin >> nombre;

        cout << "Ingrese la edad de la persona " << i + 1 << ": ";
        cin >> edad;

        lista.push_back(make_pair(nombre, edad));
    }

    // Ordenar por nombre utilizando lambda
    sort(lista.begin(), lista.end(), [](const auto &a, const auto &b) {
        return a.first < b.first;
    });

    cout << "\nLista ordenada por nombre:\n";
    for (const auto &persona : lista) {
        cout << persona.first << " - " << persona.second << endl;
    }

    // Ordenar por edad utilizando lambda
    sort(lista.begin(), lista.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    cout << "\nLista ordenada por edad:\n";
    for (const auto &persona : lista) {
        cout << persona.first << " - " << persona.second << endl;
    }

    return 0;
}
