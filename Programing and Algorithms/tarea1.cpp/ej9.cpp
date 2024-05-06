/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 1 - EJ9***********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include "tarea1.cpp"

using namespace std;

int main(int argc, char **argv){
    if(argc < 3){
        printf("Uso: %s <argumento1> <argumento2> ... <argumentoN>\n", argv[0]);
        return 1; // Sale del programa con un código de error
    }

    cout << "Este programa toma el archivo que se ingresa como bandera y lee lso valores, \
despues, calcula la suma y el promedio y los escribe en el segundo archivo que se ingresa \
como bandera." << endl;

    vector<double> vals = r_numeros(argv[1]);

    //Se calcula la suma
    vector<double> res = {0, 0};
    for(int i=0; i<vals.size(); i++) res[0] += vals[i];
    res[1] = res[0] / vals.size();

    //Se escribe en el archivo
    w_numeros(res, argv[2]);

    return 0;
}