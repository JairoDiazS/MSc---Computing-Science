/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ12***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar una matriz 5x5
    Eigen::MatrixXd matriz(5, 5);
    matriz << 1, 2, 3, 4, 5,
              6, 7, 8, 9, 10,
              11, 12, 13, 14, 15,
              16, 17, 18, 19, 20,
              21, 22, 23, 24, 25;

    std::cout << "Matriz original:\n" << matriz << "\n\n";

    // Extraer un bloque 3x3 de la matriz
    Eigen::MatrixXd bloque3x3 = matriz.block(1, 1, 3, 3);

    std::cout << "Bloque 3x3 extraído:\n" << bloque3x3 << "\n\n";

    // Reemplazar un bloque 2x2 por una matriz identidad
    matriz.block(2, 2, 2, 2) = Eigen::MatrixXd::Identity(2, 2);

    std::cout << "Matriz después del reemplazo:\n" << matriz << "\n\n";

    return 0;
}
