//
// Created by jens on 20/12/22.
//

#ifndef MATRIXCALC_MATRIX_H
#define MATRIXCALC_MATRIX_H

#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;

using std::vector;

class Matrix {
public:
    Matrix();
    Matrix(int rows, int columns);

    void print();

    void set(int r, int c, double value);
    void setRow(int r, vector<double> row);
    void setColumn(int c, vector<double> column);
    void setDiagonal(vector<double> diagonal);
    void makeIdentity();

    vector<double> getRow(int r) const;
    vector<double> getColumn(int c) const;
    vector<double> getDiagonal() const;

    int getRowNum() const;
    int getColumnNum() const;
    bool getIsVector() const;

    const vector<vector<double>> &getElements() const;

    bool isSquare() const;
    bool isDiagonal();
    bool isStrictlyDiagonallyDominant();
    bool isDiagonallyDominant();
    bool isUpperTriangular();
    bool isLowerTriangular();
    bool isSymmetric();
    bool isIdentity();

    bool operator==(Matrix b);
    bool operator!=(const Matrix& b);
    Matrix& operator=(const Matrix& b);
    Matrix operator+(const Matrix& b);
    Matrix operator-(const Matrix& b);
    Matrix operator*(const Matrix& b);
    Matrix operator*(double b);
    Matrix operator/(double b);

    Matrix transpose() const;
    double trace();
    double inproduct(const Matrix& a);
    double inproduct(const Matrix& a, const Matrix& b);
    double inproduct(vector<double> a, vector<double> b);
    Matrix power(double b);



private:
    vector<vector<double>> elements;
    int rowNum;
    int columnNum;
    bool isVector;
};




#endif //MATRIXCALC_MATRIX_H
