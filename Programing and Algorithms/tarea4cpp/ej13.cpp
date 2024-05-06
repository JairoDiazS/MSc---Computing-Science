/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ13***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar un vector y una matriz de tamaño dinámico
    Eigen::VectorXd vector(3);
    vector << 1, 2, 3;

    Eigen::MatrixXd matriz(4, 3);
    matriz << 1, 2, 3,
              4, 5, 6,
              7, 8, 9,
              10, 11, 12;

    std::cout << "Vector:\n" << vector << "\n\n";
    std::cout << "Matriz:\n" << matriz << "\n\n";

    // Calcular el producto de la matriz por el vector
    Eigen::VectorXd resultado = matriz * vector;

    std::cout << "Resultado del producto matriz por vector:\n" << resultado << "\n";

    return 0;
}
