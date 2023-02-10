#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix(4, 4);
    a.setMatrix({{7, 9, 3, 6},{8, 2, 1, 5},{5,3,8,1},{7,3,6,4}});
    a.print();
    std::cout << a.getDeterminant() << std::endl;
    a.saveToFile("matrices/m1.json");
}
