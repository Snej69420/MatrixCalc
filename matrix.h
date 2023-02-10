//
// Created by jens on 20/12/22.
//

#ifndef MATRIXCALC_MATRIX_H
#define MATRIXCALC_MATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "json.hpp"


using std::cout;
using std::endl;

using std::vector;

class Matrix {
public:

    /// Constructors
    Matrix();
    Matrix(int rows, int columns);
    explicit Matrix(const std::string& file);

    void saveToFile(const std::string& file);

    bool isEmpty() const;

    /// functions to print matrices and augmented matrices
    void printHelp(int size, int r, Matrix a = {}, int sizeA = 0);
    void print();
    void print(Matrix a);

    /// functions to set rows, columns, ... in the matrix
    void set(int r, int c, double value);
    void setRow(int r, vector<double> row);
    void setColumn(int c, vector<double> column);
    void setDiagonal(vector<double> diagonal);
    void setMatrix(vector<vector<double>> matrix);

    void makeIdentity();

    vector<double> getRow(int r) const;
    vector<double> getColumn(int c) const;
    vector<double> getDiagonal() const;

    int getRowNum() const;
    int getColumnNum() const;
    bool getIsVector() const;

    /// get all values in the matrix
    const vector<vector<double>> &getElements() const;

    /// functions to check what form the matrix is
    bool isSquare() const;
    bool isDiagonal();
    bool isStrictlyDiagonallyDominant();
    bool isDiagonallyDominant();
    bool isUpperTriangular();
    bool isLowerTriangular();
    bool isSymmetric();
    bool isIdentity();

    bool isNullRow(vector<double> r);
    int findZerosRow();
    int findZerosColumn();

    /// standard operations
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
    Matrix power(unsigned int b);

    Matrix createMinor(int r, int c);

    double getDeterminant();

    /// row operations for Gauss Jordan Eliminations
    void swapRows(int r0, int r1);
    vector<double> addingRows(vector<double> r0, vector<double> r1);
    vector<double> multiplyRow(double  n, vector<double> r0);

    /// solving the matrix
    Matrix solveTriangular(Matrix a, Matrix b, bool upper = false);
    Matrix Gauss_Jordan(Matrix a = {});

    std::vector<std::vector<double>> calculateColumnSpace();


private:
    /// find the element of the matrix consisting out of the most characters, helper function for print
    unsigned int biggestElement();

    vector<vector<double>> elements;
    int rowNum = 0;
    int columnNum = 0;
    bool isVector;

    double determinant = NAN;
    vector<double> eigenValues;
    vector<vector<double>> eigenVectors;
    bool symmetric;
    bool positiveDefinite;
    bool positiveSemiDefinite;
    bool negativeDefinite;
    bool negativeSemiDefinite;
    vector<double> singularValues;
    vector<vector<double>> singularVectors;

    bool printSteps = false;
};




#endif //MATRIXCALC_MATRIX_H
