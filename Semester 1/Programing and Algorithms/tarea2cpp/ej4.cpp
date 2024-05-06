/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ4***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void listarArchivos(const std::string& ruta) {
    std::cout << "Archivos en " << ruta << ":\n";
    for (const auto& entrada : fs::directory_iterator(ruta)) {
        std::cout << "  " << entrada.path().filename() << '\n';
    }
}

void crearArchivo(const std::string& ruta, const std::string& nombreArchivo) {
    fs::path rutaCompleta = ruta;
    rutaCompleta /= nombreArchivo;

    std::ofstream archivo(rutaCompleta);
    if (archivo.is_open()) {
        std::cout << "Archivo creado: " << rutaCompleta << '\n';
    } else {
        std::cerr << "Error al crear el archivo.\n";
    }
}

void eliminarArchivo(const std::string& ruta, const std::string& nombreArchivo) {
    fs::path rutaCompleta = ruta;
    rutaCompleta /= nombreArchivo;

    if (fs::exists(rutaCompleta)) {
        fs::remove(rutaCompleta);
        std::cout << "Archivo eliminado: " << rutaCompleta << '\n';
    } else {
        std::cerr << "El archivo no existe.\n";
    }
}

int main() {
    std::string rutaActual = ".";  // Ruta actual inicial, se puede cambiar según sea necesario
    std::string comando;

    do {
        std::cout << "\nComandos disponibles:\n";
        std::cout << "  listar\n";
        std::cout << "  crear <nombre_archivo>\n";
        std::cout << "  eliminar <nombre_archivo>\n";
        std::cout << "  salir\n";

        std::cout << "Ingrese un comando: ";
        std::cin >> comando;

        if (comando == "listar") {
            listarArchivos(rutaActual);
        } else if (comando == "crear") {
            std::string nombreArchivo;
            std::cout << "Ingrese el nombre del archivo a crear: ";
            std::cin >> nombreArchivo;
            crearArchivo(rutaActual, nombreArchivo);
        } else if (comando == "eliminar") {
            std::string nombreArchivo;
            std::cout << "Ingrese el nombre del archivo a eliminar: ";
            std::cin >> nombreArchivo;
            eliminarArchivo(rutaActual, nombreArchivo);
        } else if (comando == "salir") {
            std::cout << "Saliendo del programa.\n";
        } else {
            std::cerr << "Comando no reconocido. Intente nuevamente.\n";
        }

    } while (comando != "salir");

    return 0;
}