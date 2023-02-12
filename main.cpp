#include <iostream>
#include <chrono>
#include "matrix.h"

int main() {
    Matrix a;
    a.generateMatrix(11,11);
    a.print();
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "Determinant " << a.getDeterminant() << std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    cout << duration.count() << " seconds" << endl;
}