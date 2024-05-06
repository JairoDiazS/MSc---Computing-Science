/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ5***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <fstream>
#include <vector>

const int N = 9;

using namespace std;

// Función para imprimir el tablero de Sudoku
void imprimirTablero(const vector<vector<int>>& tablero) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para verificar si es seguro colocar un número en una posición específica
bool esSeguro(const vector<vector<int>>& tablero, int fila, int columna, int numero) {
    // Verificar en la fila y columna
    for (int i = 0; i < N; ++i) {
        if (tablero[fila][i] == numero || tablero[i][columna] == numero) {
            return false;
        }
    }

    // Verificar en el cuadrante 3x3
    int cuadranteInicioFila = fila - fila % 3;
    int cuadranteInicioColumna = columna - columna % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[cuadranteInicioFila + i][cuadranteInicioColumna + j] == numero) {
                return false;
            }
        }
    }

    return true;
}

// Función de backtracking para resolver el Sudoku
bool resolverSudoku(vector<vector<int>>& tablero) {
    for (int fila = 0; fila < N; ++fila) {
        for (int columna = 0; columna < N; ++columna) {
            if (tablero[fila][columna] == 0) {
                for (int numero = 1; numero <= 9; ++numero) {
                    if (esSeguro(tablero, fila, columna, numero)) {
                        tablero[fila][columna] = numero;

                        if (resolverSudoku(tablero)) {
                            return true;
                        }

                        tablero[fila][columna] = 0; // Deshacer el intento si no lleva a una solución válida
                    }
                }

                return false; // No hay solución válida para esta celda
            }
        }
    }

    return true; // Se ha completado todo el tablero
}

int main() {
    string nombreArchivo;

    cout << "Ingrese el nombre del archivo de Sudoku: ";
    cin >> nombreArchivo;

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo.\n";
        return 1;
    }

    // Ingresar el tablero Sudoku desde el archivo
    vector<vector<int>> tablero(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            archivo >> tablero[i][j];
        }
    }

    archivo.close();

    cout << "\nTablero Sudoku ingresado:\n";
    imprimirTablero(tablero);

    if (resolverSudoku(tablero)) {
        cout << "\nSolución del Sudoku:\n";
        imprimirTablero(tablero);
    } else {
        cout << "\nNo hay solución válida para el Sudoku ingresado.\n";
    }

    return 0;
}
