/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ6***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Contacto {
public:
    Contacto(const string& nombre = "", const string& telefono = "", const string& correo = "")
        : nombre(nombre), telefono(telefono), correo(correo) {}

    const string& getNombre() const { return nombre; }
    const string& getTelefono() const { return telefono; }
    const string& getCorreo() const { return correo; }

    friend istream& operator>>(istream& is, Contacto& contacto);
    friend ostream& operator<<(ostream& os, const Contacto& contacto);

private:
    string nombre;
    string telefono;
    string correo;
};

istream& operator>>(istream& is, Contacto& contacto) {
    return is >> contacto.nombre >> contacto.telefono >> contacto.correo;
}

ostream& operator<<(ostream& os, const Contacto& contacto) {
    return os << setw(15) << left << contacto.nombre
              << setw(15) << left << contacto.telefono
              << contacto.correo;
}

class Agenda {
public:
    void agregarContacto(const Contacto& nuevoContacto) {
        contactos.push_back(nuevoContacto);
        cout << "Contacto agregado exitosamente.\n";
    }

    void eliminarContacto(const string& nombre) {
        auto it = remove_if(contactos.begin(), contactos.end(),
                            [nombre](const Contacto& c) { return c.getNombre() == nombre; });

        if (it != contactos.end()) {
            contactos.erase(it, contactos.end());
            cout << "Contacto eliminado exitosamente.\n";
        } else {
            cout << "No se encontró un contacto con ese nombre.\n";
        }
    }

    void buscarContacto(const string& nombre) const {
        auto it = find_if(contactos.begin(), contactos.end(),
                          [nombre](const Contacto& c) { return c.getNombre() == nombre; });

        if (it != contactos.end()) {
            cout << "Contacto encontrado:\n" << *it << "\n";
        } else {
            cout << "No se encontró un contacto con ese nombre.\n";
        }
    }

    void listarContactos() const {
        if (contactos.empty()) {
            cout << "La agenda está vacía.\n";
        } else {
            cout << "Lista de contactos:\n";
            for (const auto& contacto : contactos) {
                cout << contacto << "\n";
            }
        }
    }

    void guardarAgenda(const string& nombreArchivo) const {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (const auto& contacto : contactos) {
                archivo << contacto << "\n";
            }
            cout << "Agenda guardada exitosamente en " << nombreArchivo << "\n";
        } else {
            cerr << "Error al abrir el archivo para guardar la agenda.\n";
        }
    }

    void cargarAgenda(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            contactos.clear();  // Limpiar la agenda actual

            Contacto c;
            while (archivo >> c) {
                contactos.push_back(c);
            }

            cout << "Agenda cargada exitosamente desde " << nombreArchivo << "\n";
        } else {
            cerr << "Error al abrir el archivo para cargar la agenda.\n";
        }
    }

private:
    vector<Contacto> contactos;
};

int main() {
    Agenda agenda;
    string nombreArchivo;

    cout << "Ingrese el nombre del archivo de la agenda: ";
    cin >> nombreArchivo;

    agenda.cargarAgenda(nombreArchivo);

    int opcion;
    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar contacto\n";
        cout << "2. Eliminar contacto\n";
        cout << "3. Buscar contacto\n";
        cout << "4. Listar contactos\n";
        cout << "5. Guardar agenda\n";
        cout << "0. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Contacto nuevoContacto;
                cout << "Ingrese el nombre/telefono/correo(separados por espacios): ";
                cin >> nuevoContacto;
                agenda.agregarContacto(nuevoContacto);
                break;
            }
            case 2: {
                string nombreEliminar;
                cout << "Ingrese el nombre del contacto a eliminar: ";
                cin >> nombreEliminar;
                agenda.eliminarContacto(nombreEliminar);
                break;
            }
            case 3: {
                string nombreBuscar;
                cout << "Ingrese el nombre del contacto a buscar: ";
                cin >> nombreBuscar;
                agenda.buscarContacto(nombreBuscar);
                break;
            }
            case 4:
                agenda.listarContactos();
                break;
            case 5:
                agenda.guardarAgenda(nombreArchivo);
                break;
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cerr << "Opción no válida. Intente nuevamente.\n";
        }

    } while (opcion != 0);

    return 0;
}

