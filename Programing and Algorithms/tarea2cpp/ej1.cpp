/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ1***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main() {
    string fn;
    int nwords, nchars;
    nwords = nchars = 0;
    char ch;
    cout << "Ingrese el nombre del archivo: ";
    cin >> fn;

    map<char, int> freq;

    ifstream file(fn);
    if(file.is_open()) {
        while (file.get(ch)){
            ch = tolower(ch);
            nchars++;
            if(isspace(ch)) nwords++;
            if(isalpha(ch)) freq[ch]++;
        }
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    cout << "El numero de palabras es: " << nwords << endl;
    cout << "El numero de caracteres es: " << nchars << endl;
    cout << "La frecuencia de las letras es la siguiente:" << endl;
    for(const auto &pair : freq){
        cout << pair.first << ": " << pair.second << endl;
    }

    file.close();

    return 0;
}