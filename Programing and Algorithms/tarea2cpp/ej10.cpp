/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 2 - EJ10***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

int main() {
    // Configuración de la semilla para generar números aleatorios
    srand(time(0));

    int numTiradas;
    cout << "Ingrese el número de tiradas para la simulación: ";
    cin >> numTiradas;

    int dentroCirculo = 0;

    for (int i = 0; i < numTiradas; ++i) {
        // Generar coordenadas aleatorias en el rango [0, 1]
        double x = static_cast<double>(rand()) / RAND_MAX;
        double y = static_cast<double>(rand()) / RAND_MAX;

        // Calcular la distancia desde el origen (0.5, 0.5)
        double distancia = sqrt((x - 0.5) * (x - 0.5) + (y - 0.5) * (y - 0.5));

        // Verificar si la distancia está dentro del círculo (radio 0.5)
        if (distancia <= 0.5) {
            dentroCirculo++;
        }
    }

    // Calcular la estimación de π
    double estimacionPi = 4.0 * dentroCirculo / numTiradas;

    cout << "Estimación de pi después de " << numTiradas << " tiradas: " << estimacionPi << endl;

    return 0;
}
