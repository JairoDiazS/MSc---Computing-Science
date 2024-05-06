/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/**************Tarea 2 - EJ3***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <string>
#include <exprtk.hpp>

using namespace std;

int main() {
    string expression;

    cout << "Ingrese una expresión matemática: ";
    getline(cin, expression);

    exprtk::symbol_table<double> symbol_table;
    exprtk::expression<double> expr;

    symbol_table.add_constants();
    
    // Almacena el valor en una variable antes de agregarlo como variable a la tabla de símbolos
    double x_value = 0.0;
    symbol_table.add_variable("x", x_value);

    expr.register_symbol_table(symbol_table);

    exprtk::parser<double> parser;
    if (parser.compile(expression, expr)) {
        double result = expr.value();
        cout << "Resultado: " << result << endl;
    } else {
        cerr << "Error: Expresión no válida" << endl;
    }

    return 0;
}
