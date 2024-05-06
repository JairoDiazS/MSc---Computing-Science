/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ4***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(){
    //Se define el apuntador a funcion
    double (*funcion)(double, double);
    double a, b;
    int opt;
    cout << "Ingrese dos valores para realizar una operacion." << endl;
    cin >> a >> b;
    cout << "Ingrese la operacion que desee realizar con estos numeros" << endl;
    cout << "1.- Suma." << endl;
    cout << "2.- Resta." << endl;
    cout << "3.- Multiplicacion." << endl;
    cout << "4.- Division." << endl;
    cin >> opt;
    switch(opt){
        case 1:
            funcion = suma;
            break;
        case 2:
            funcion = resta;
            break;
        case 3:
            funcion = multiplicacion;
            break;
        case 4:
            funcion = division;
            break;
        default: 
            cout << "Opcion invalida." << endl;
            exit(1);
    }

    cout << "El resultado de la operacion es: " << funcion(a,b) << endl;

    return 0;
}
