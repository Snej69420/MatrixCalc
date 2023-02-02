#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix("matrices/lower.json");
    a = a.Gauss_Jordan();
    a.print();

}
