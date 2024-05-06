/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ14***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar una matriz 3x3
    Eigen::MatrixXd matriz(3, 3);
    matriz << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;

    std::cout << "Matriz original:\n" << matriz << "\n\n";

    // Calcular el promedio de cada fila
    Eigen::VectorXd promedioFilas = matriz.rowwise().mean();

    std::cout << "Promedio de cada fila:\n" << promedioFilas.transpose() << "\n\n";

    // Normalizar cada columna
    for (int i = 0; i < matriz.cols(); ++i) {
        matriz.col(i).normalize();
    }

    std::cout << "Matriz normalizada por columnas:\n" << matriz << "\n";

    return 0;
}
