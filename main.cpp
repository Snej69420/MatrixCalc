#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix(2,2);
    a.setRow(0,{1,2});
    a.setRow(1, {5,6});
    a.print();
    Matrix b = Matrix(2, 3);
    b.setRow(0,{9,4,1});
    b.setRow(1, {8,7,0});
    b.print();
    Matrix c = a*b;
    c.print();
}
