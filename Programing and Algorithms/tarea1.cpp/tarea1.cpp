/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/************Tarea 1 Cabecera**********/
/*******Programacion y Algoritmos******/
/**************31/10/2023**************/
/**************************************/
/**************************************/

#include <stdlib.h>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#include "tarea1.h"

using namespace std;

//Rutina para leer desde un archivo
vector<double> r_numeros(const char *fn){
    //Se abre el archivo en modo lectura
    ifstream file(fn);

    //Se verifica si se abrio correctamente
    if(!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return vector<double>();
    }

    //Se define el vector
    vector<double> vec;
    double temp;

    //Se rellena el vector
    while(file >> temp) vec.push_back(temp);

    //Se cierra el archivo
    file.close();

    //Se retorna el vector
    return vec;
}

void w_numeros(vector<double> &vec, const char *fn){
    //Se abre el archivo en modo escritura
    ofstream file(fn);

    //Se verifica si se abrio correctamente
    if(!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    //Se imprime lo que se requiere
    for(int i=0; i<vec.size(); i++) file << vec[i] << endl;

    //Se cierra el archivo
    file.close();
}

/*Rutina que toma un apuntador a un arreglo y su tamanio y retornla la suma de
sus elementos.*/
double sumaArreglo(double *arr, int sz){
    int i;
    double res = 0.0;
    for(i=0; i<sz; i++) res += arr[i];

    return res;
}

//Subrutina de una dangling function
void dangling_function(vector<int>& a, int n){
    //El vector se llena con n valores aleatorios
    int i, temp;
    for(i=0; i<n; i++){
        temp = rand() % 101;
        a.push_back(temp);
    } 
}

//Suma
double suma(double a, double b){
    return a+b;
}

//Resta
double resta(double a, double b){
    return a-b;
}

//multiplicacion
double multiplicacion(double a, double b){
    return a*b;
}

//Division
double division(double a, double b){
    if(b!=0) return a/b;
    std::cout << "Division por 0.\n";
    return 0;
}

double safeDivision(double numerador, double denominador){
    try {
        if (denominador == 0) {
            throw runtime_error("Division por cero no permitida.");
        }
        return numerador / denominador;
    } catch (const runtime_error& error) {
        // Se maneja la excepcion y se reporta al usuario
        cerr << "Error: " << error.what() << endl;
        return 0.0;
    }
}


//Subrutina para generar numeros aleatorios en un arreglo
void randArray(double *arr, int sz){

    double temp;
    int i;
    for(i=0; i<sz; i++){
        temp = rand()%101; //Aleatorios entre 0 y 100
        arr[i] = temp;
    }

}

