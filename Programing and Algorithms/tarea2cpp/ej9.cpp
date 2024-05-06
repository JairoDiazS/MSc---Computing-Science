/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ9***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo de texto: ";
    cin >> nombreArchivo;

    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo.\n";
        return 1;
    }

    string palabra;
    cout << "Ingrese la palabra a buscar: ";
    cin >> palabra;

    map<string, int> frecuenciaPalabras;

    string linea;
    while (getline(archivo, linea)) {
        istringstream streamLinea(linea);
        string palabraEnLinea;

        while (streamLinea >> palabraEnLinea) {
            // Eliminar caracteres no deseados (puedes ajustar esto según tus necesidades)
            palabraEnLinea.erase(remove_if(palabraEnLinea.begin(), palabraEnLinea.end(),
                                                [](unsigned char c) { return ispunct(c); }),
                                 palabraEnLinea.end());

            // Convertir a minúsculas para hacer la búsqueda sin distinción entre mayúsculas y minúsculas
            transform(palabraEnLinea.begin(), palabraEnLinea.end(), palabraEnLinea.begin(), ::tolower);

            // Incrementar la frecuencia de la palabra
            if (palabraEnLinea == palabra) {
                frecuenciaPalabras[palabra]++;
            }
        }
    }

    // Mostrar la frecuencia de la palabra
    cout << "La palabra '" << palabra << "' aparece " << frecuenciaPalabras[palabra] << " veces en el texto.\n";

    return 0;
}
