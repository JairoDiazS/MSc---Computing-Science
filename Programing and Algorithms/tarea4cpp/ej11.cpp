/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ11***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar un vector
    Eigen::VectorXd vector(3);
    vector << 1, 2, 3;

    // Calcular la norma euclidiana del vector
    double norma = vector.norm();

    std::cout << "Vector de entrada:\n" << vector << std::endl;

    // Imprimir la norma
    std::cout << "Norma Euclidiana del vector: " << norma << "\n";

    // Normalizar el vector
    Eigen::VectorXd vectorNormalizado = vector.normalized();

    // Imprimir el vector normalizado
    std::cout << "Vector normalizado:\n" << vectorNormalizado << "\n";

    return 0;
}
