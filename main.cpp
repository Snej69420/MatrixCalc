#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix("matrices/m1.json");
    a.print();
    Matrix b = Matrix(3,1);
    b.setColumn(0, {5,4,8});
    b.print();
    a.Gauss_Jordan(b);
}
