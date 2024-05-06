/**************************************/
/**************************************/
/**********Jairo Saul Diaz Soto********/
/*************Tarea 4 - EJ15***********/
/*******Programacion y Algoritmos******/
/**************28/11/2023**************/
/**************************************/
/**************************************/

#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <chrono>

int main() {
    // Crear una matriz dispersa 100x100 con pocos elementos distintos de 0
    Eigen::SparseMatrix<double> sparseMatriz(100, 100);

    // Establecer algunos valores no nulos
    sparseMatriz.coeffRef(1, 1) = 1.0;
    sparseMatriz.coeffRef(2, 2) = 2.0;
    sparseMatriz.coeffRef(3, 3) = 3.0;

    // Crear un vector denso
    Eigen::VectorXd vectorDenso(100);
    vectorDenso.setRandom();

    // Medir el tiempo de la multiplicación con la matriz dispersa
    auto startSparse = std::chrono::high_resolution_clock::now();
    Eigen::VectorXd resultadoSparse = sparseMatriz * vectorDenso;
    auto endSparse = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoSparse = endSparse - startSparse;

    // Convertir la matriz dispersa a densa
    Eigen::MatrixXd matrizDensa = sparseMatriz.toDense();

    // Medir el tiempo de la multiplicación con la matriz densa
    auto startDense = std::chrono::high_resolution_clock::now();
    Eigen::VectorXd resultadoDense = matrizDensa * vectorDenso;
    auto endDense = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoDense = endDense - startDense;

    // Comparar los resultados
    std::cout << "Resultado con matriz dispersa:\n" << resultadoSparse.transpose() << "\n\n";
    std::cout << "Resultado con matriz densa:\n" << resultadoDense.transpose() << "\n";

    // Imprimir los tiempos de ejecución
    std::cout << "\nTiempo de ejecución con matriz dispersa: " << tiempoSparse.count() << " segundos\n";
    std::cout << "Tiempo de ejecución con matriz densa: " << tiempoDense.count() << " segundos\n";

    return 0;
}
