/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ8************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar una matriz 3x3 simétrica
    Eigen::MatrixXd matriz(3, 3);
    matriz << 1, 2, 3,
               2, 4, 5,
               3, 5, 6;

    // Calcular eigenvalores y eigenvectores
    Eigen::EigenSolver<Eigen::MatrixXd> solver(matriz);
    Eigen::VectorXd eigenvalores = solver.eigenvalues().real();
    Eigen::MatrixXd eigenvectores = solver.eigenvectors().real();

    // Imprimir eigenvalores y eigenvectores
    std::cout << "Matriz original:\n" << matriz << "\n\n";
    std::cout << "Eigenvalores:\n" << eigenvalores << "\n\n";
    std::cout << "Eigenvectores:\n" << eigenvectores << "\n\n";

    return 0;
}
