#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix("matrices/lower.json");
    Matrix b = Matrix(3,1);
    b.setColumn(0, {4,7,1});
    a.Gauss_Jordan(b).print();

}
