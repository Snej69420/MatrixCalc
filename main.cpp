#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix(3,3);
    a.setRow(0,{4,2,0});
    a.setRow(1,{6,6,6});
    a.setRow(2, {6,0,9});
    a.print();
    cout << a.determinant() << endl;
}
