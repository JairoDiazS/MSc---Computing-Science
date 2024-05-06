/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ6************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Declarar una matriz 3x3 de tipo double
    Eigen::MatrixXd matriz(3, 3);

    // Inicializar la matriz
    matriz << 1, 2, 3,
               4, 5, 6,
               7, 8, 9;

    // Declarar un vector de tipo double
    Eigen::VectorXd vector(3);

    // Inicializar el vector
    vector << 1, 2, 3;

    std::cout << "Matriz de entrada:\n" << matriz << std::endl;
    std::cout << "Vector de entrada:\n" << vector << std::endl;

    // Realizar operaciones de álgebra lineal
    Eigen::MatrixXd resultado = matriz * vector;

    // Imprimir el resultado
    std::cout << "Resultado:\n" << resultado << std::endl;

    // Se obtiene el valor de la inversa 
    Eigen::MatrixXd matrizInversa = matriz.inverse();

    std::cout << "Inversa de la matriz:\n" << matrizInversa << std::endl;


    return 0;
}

