#include <iostream>
#include "matrix.h"

int main() {
    Matrix a = Matrix(3,3);
    a.setRow(0,{420,420,420});
    a.setRow(1,{6,6,6});
    a.setRow(2, {69,69,69});
    a.print();
    cout << a.determinant() << endl;
}
