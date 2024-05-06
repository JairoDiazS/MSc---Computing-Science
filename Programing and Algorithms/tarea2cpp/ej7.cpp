/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ7***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool estanBalanceados(const string& expresion) {
    stack<char> pila;

    for (char caracter : expresion) {
        switch (caracter) {
            case '(':
            case '[':
            case '{':
                pila.push(caracter);
                break;

            case ')':
                if (pila.empty() || pila.top() != '(') {
                    return false;
                }
                pila.pop();
                break;

            case ']':
                if (pila.empty() || pila.top() != '[') {
                    return false;
                }
                pila.pop();
                break;

            case '}':
                if (pila.empty() || pila.top() != '{') {
                    return false;
                }
                pila.pop();
                break;
        }
    }

    return pila.empty();
}

int main() {
    string expresion;

    cout << "Ingrese una expresion: ";
    getline(cin, expresion);

    if (estanBalanceados(expresion)) {
        cout << "Los paréntesis, corchetes y llaves están balanceados.\n";
    } else {
        cout << "Los paréntesis, corchetes y llaves NO están balanceados.\n";
    }

    return 0;
}
