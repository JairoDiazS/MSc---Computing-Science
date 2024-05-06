/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ10***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar una matriz 3x3
    Eigen::MatrixXd matriz(3, 3);
    matriz << 2, -1, 1,
               -3, -1, 2,
               -2, 1, 2;

    std::cout << "Matriz de entrada:\n" << matriz << std::endl;
    
    // Obtener la descomposición LU
    Eigen::PartialPivLU<Eigen::MatrixXd> lu(matriz);

    // Obtener las matrices L y U
    Eigen::MatrixXd L = lu.matrixLU().triangularView<Eigen::Lower>();
    Eigen::MatrixXd U = lu.matrixLU().triangularView<Eigen::Upper>();

    for (int i = 0; i < 3; ++i) {
        double diag_value = lu.matrixLU()(i, i);
        L(i,i) /= diag_value;
    }

    // Imprimir las matrices L y U
    std::cout << "Matriz L:\n" << L << "\n\n";
    std::cout << "Matriz U:\n" << U << "\n\n";

    return 0;
}
