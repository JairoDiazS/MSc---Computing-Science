/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ8***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Estructura para representar las aristas del grafo
struct Arista {
    int destino;
    int peso;
};

// Función para imprimir el camino más corto desde el nodo fuente al destino
void imprimirCamino(const vector<int>& padre, int destino) {
    if (padre[destino] == -1) {
        cout << destino;
        return;
    }
    imprimirCamino(padre, padre[destino]);
    cout << " -> " << destino;
}

// Implementación del algoritmo de Dijkstra
void dijkstra(const vector<vector<Arista>>& grafo, int fuente) {
    int n = grafo.size();

    // Inicializar vectores de distancias y padres
    vector<int> distancia(n, numeric_limits<int>::max());
    vector<int> padre(n, -1);

    // La distancia del nodo fuente a sí mismo es 0
    distancia[fuente] = 0;

    // Utilizar una cola de prioridad para mantener los nodos con menor distancia en la parte superior
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> colaPrioridad;
    colaPrioridad.push({0, fuente});

    while (!colaPrioridad.empty()) {
        int u = colaPrioridad.top().second;
        colaPrioridad.pop();

        // Iterar sobre los nodos vecinos de u
        for (const Arista& vecino : grafo[u]) {
            int v = vecino.destino;
            int pesoUV = vecino.peso;

            // Relajar la arista (u, v)
            if (distancia[u] + pesoUV < distancia[v]) {
                distancia[v] = distancia[u] + pesoUV;
                padre[v] = u;
                colaPrioridad.push({distancia[v], v});
            }
        }
    }

    // Imprimir las distancias y los caminos más cortos desde la fuente
    for (int i = 0; i < n; ++i) {
        cout << "Distancia desde " << fuente << " hasta " << i << ": " << distancia[i] << ", Camino: ";
        imprimirCamino(padre, i);
        cout << endl;
    }
}

int main() {
    int nodos, aristas;
    cout << "Ingrese el número de nodos y aristas del grafo: ";
    cin >> nodos >> aristas;

    vector<vector<Arista>> grafo(nodos);

    cout << "Ingrese las aristas en el formato (nodo_fuente nodo_destino peso):\n";
    for (int i = 0; i < aristas; ++i) {
        int fuente, destino, peso;
        cin >> fuente >> destino >> peso;
        grafo[fuente].push_back({destino, peso});
    }

    int nodoFuente;
    cout << "Ingrese el nodo fuente para el algoritmo de Dijkstra: ";
    cin >> nodoFuente;

    dijkstra(grafo, nodoFuente);

    return 0;
}
