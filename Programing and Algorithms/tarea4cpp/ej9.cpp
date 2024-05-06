/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ9************/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Dense>

int main() {
    // Definir e inicializar la matriz A y el vector b
    Eigen::MatrixXd A(3, 3);
    A << 2, -1, 1,
         -3, -1, 2,
         -2, 1, 2;

    Eigen::VectorXd b(3);
    b << 8, -11, -3;

    std::cout << "Matriz de entrada:\n" << A << std::endl;
    std::cout << "Vector de entrada:\n" << b << std::endl;

    // Resolver el sistema de ecuaciones Ax = b
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

    // Imprimir la solución
    std::cout << "Solución x:\n" << x << "\n\n";

    return 0;
}
