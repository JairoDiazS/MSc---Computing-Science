/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ7************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar una matriz 4x4
    Eigen::MatrixXd matriz(4, 4);
    matriz << 2, 1, 0, 0,
               1, 2, 1, 0,
               0, 1, 2, 1,
               0, 0, 1, 2;

    // Calcular el determinante
    double determinante = matriz.determinant();

    // Imprimir la matriz y el determinante
    std::cout << "Matriz original:\n" << matriz << "\n\n";
    std::cout << "Determinante: " << determinante << "\n\n";

    // Verificar si la matriz es invertible
    if (determinante != 0.0) {
        // Calcular la inversa
        Eigen::MatrixXd matrizInversa = matriz.inverse();

        // Imprimir la inversa
        std::cout << "Matriz inversa:\n" << matrizInversa << "\n\n";

        // Verificar que A * A^{-1} = I
        Eigen::MatrixXd producto = matriz * matrizInversa;
        std::cout << "Producto de la matriz y su inversa:\n" << producto << "\n\n";
    } else {
        std::cout << "La matriz no es invertible (determinante igual a cero).\n";
    }

    return 0;
}
