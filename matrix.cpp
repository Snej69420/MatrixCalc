//
// Created by jens on 20/12/22.
//

#include "matrix.h"

Matrix::Matrix() {
    rowNum = 0;
    columnNum = 0;
    isVector = false;
    elements = {{}};
}

Matrix::Matrix(int row, int column){
    rowNum = row;
    columnNum = column;
    vector<double> r(column, 0);
    elements = vector<vector<double>>(row, r);
    isVector = false;
    if(row == 1 || column == 1){
        isVector = true;
    }
}

void Matrix::print() {
    for (int r = 0; r < rowNum; r++) {
        cout << "| ";
        for (int c = 0; c < columnNum; c++) {
            cout << elements[r][c];
            cout << " ";

        }
        cout << "|" << endl;
    }
    cout << endl;
}

bool Matrix::isSquare() const {
    if(rowNum == columnNum and !isVector){
        return true;
    }
    return false;
}

bool Matrix::isDiagonal() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            if(r == c){
                continue;
            }
            if(elements[r][c] != 0){
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isDiagonallyDominant() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        double sum = 0;
        for(int c = 0; c < columnNum; c++){
            if(r == c){
                continue;
            }
            sum += abs(elements[r][c]);
        }
        if(abs(elements[r][r]) < sum){
            return false;
        }
    }
    return true;
}

bool Matrix::isStrictlyDiagonallyDominant() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        double sum = 0;
        for(int c = 0; c < columnNum; c++){
            if(r == c){
                continue;
            }
            sum += abs(elements[r][c]);
        }
        if(abs(elements[r][r]) <= sum){
            return false;
        }
    }
    return true;
}

bool Matrix::isLowerTriangular() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            if(r < c && elements[r][c] != 0){return false;}
        }
    }
    return true;
}

bool Matrix::isUpperTriangular() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            if(c < r && elements[r][c] != 0){return false;}
        }
    }
    return true;
}

bool Matrix::isSymmetric() {
    if(!isSquare()){return false;}
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            if(r == c){
                continue;
            }
            if(elements[r][c] != elements[c][r]){return false;}
        }
    }
    return true;
}

bool Matrix::isIdentity() {
    if(!isDiagonal()){return false;}
    for(int r = 0; r < rowNum; r++){
        if(elements[r][r] != 1){return false;}
    }
    return true;
}

void Matrix::set(int r, int c, double value) {
    if(r >= rowNum || c >= columnNum){ return;}
    elements[r][c] = value;
}

void Matrix::setColumn(int c, vector<double> column) {
    if(c >= columnNum){ return;}
    for(int r = 0; r < rowNum; r++){
        if(r == column.size()){ return;}
        elements[r][c]= column[r];
    }
}

void Matrix::setDiagonal(vector<double> diagonal) {
    for(int e = 0; e < diagonal.size(); e++){
        elements[e][e] = diagonal[e];
    }
}

void Matrix::setRow(int r, vector<double> row) {
    if(r >= rowNum){ return;}
    for(int c = 0; c < columnNum; c++){
        if(c == row.size()){ return;}
        elements[r][c]= row[c];
    }
}

void Matrix::makeIdentity() {
    if(!isSquare()){ return;}
    Matrix temp = Matrix(rowNum, columnNum);
    for(int r = 0; r < rowNum; r++){
        elements[r][r] = 1;
    }
}

vector<double> Matrix::getColumn(int c) const{
    if(c >= columnNum){return {};}
    vector<double> res(rowNum);
    for(int r = 0; r < rowNum; r++){
        res[r] = elements[r][c];
    }
    return res;
}

vector<double> Matrix::getDiagonal() const{
    if(!isSquare()){return {};}
    vector<double> res(rowNum);
    for(int r = 0; r < rowNum; r++){
        res[r] = elements[r][r];
    }
    return res;
}

vector<double> Matrix::getRow(int r) const{
    if(r >= columnNum){return {};}
    vector<double> res(columnNum);
    for(int c = 0; c < rowNum; c++){
        res[c] = elements[r][c];
    }
    return res;
}

int Matrix::getRowNum() const {
    return rowNum;
}

int Matrix::getColumnNum() const {
    return columnNum;
}

bool Matrix::getIsVector() const {
    return isVector;
}

const vector<vector<double>> &Matrix::getElements() const {
    return elements;
}

bool Matrix::operator==(Matrix b){
    if(rowNum != b.rowNum || columnNum != b.columnNum){return false;}
    for(int r = 0; r < rowNum; r++){
        for(int c =0; c < columnNum; c++){
            if(elements[r][c] != b.elements[r][c]){return false;}
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& b){
    return !operator==(b);
}

Matrix& Matrix::operator=(const Matrix& b){
    rowNum = b.rowNum;
    columnNum = b.columnNum;
    elements = b.elements;
    isVector = b.isVector;
}

Matrix Matrix::operator+(const Matrix& b){
    if(rowNum != b.rowNum || columnNum != b.columnNum){return {};}
    Matrix res(rowNum, columnNum);
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            res.elements[r][c] = elements[r][c] + b.elements[r][c];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix& b){
    if(rowNum != b.rowNum || columnNum != b.columnNum){return {};}
    Matrix res(rowNum, columnNum);
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            res.elements[r][c] = elements[r][c] - b.elements[r][c];
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix& b){
    if(columnNum != b.rowNum){return {};}
    Matrix res = Matrix(rowNum, b.columnNum);
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < b.columnNum; c++){
            res.elements[r][c] += inproduct(getRow(r), b.getColumn(c));
        }
    }
    return res;
}

Matrix Matrix::operator*(double b){
    Matrix res(rowNum, columnNum);
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            res.elements[r][c] = elements[r][c]*b;
        }
    }
    return res;
}

Matrix Matrix::operator/(double b) {
    return operator*(1/b);
}

Matrix Matrix::transpose() const{
    Matrix res = Matrix(columnNum, rowNum);
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            res.elements[c][r] = elements[r][c];
        }
    }
    return res;
}

double Matrix::trace(){
    if(!isSquare()){
        return 0;
    }
    double res;
    for(int r = 0; r < rowNum; r++){
        res += elements[r][r];
    }
    return res;
}

double Matrix::inproduct(const Matrix& a){
    if(!isVector || !a.isVector){return 0;}
    if(rowNum*columnNum != a.rowNum*a.columnNum){return {};}
    Matrix temp = a;
    if(rowNum != a.rowNum){
        temp = a.transpose();
    }
    double res = 0;
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            res+= elements[r][c]*temp.elements[r][c];
        }
    }
    return res;
}

double Matrix::inproduct(const Matrix& a, const Matrix& b){
    if(!b.getIsVector() || !a.getIsVector()){return 0;}
    if(b.getRowNum()*b.getColumnNum() != a.getRowNum()*a.getColumnNum()){return {};}
    Matrix temp = a;
    if(b.getRowNum() != a.getRowNum()){
        temp = a.transpose();
    }
    double res = 0;
    for(int r = 0; r < b.getRowNum(); r++){
        for(int c = 0; c < b.getColumnNum(); c++){
            res+= b.getElements()[r][c]*temp.getElements()[r][c];
        }
    }
    return res;
}

double Matrix::inproduct(vector<double> a, vector<double> b) {
    if(a.size() != b.size()){return {};}
    double res = 0;
    for(int e = 0; e < a.size(); e++){
        res += a[e]*b[e];
    }
    return res;
}

Matrix Matrix::power(unsigned int b){
    if(!isSquare()){return {};}
    Matrix mult = *this;
    Matrix res = *this;
    if(isIdentity()){return res;}
    if(b == 0){
        res.makeIdentity();
        return res;
    }
    for(int t = 0; t < b; t++){
        res = mult*res;
    }
    return res;

}

int Matrix::findZerosRow() {
    int e = -1;
    int zeros = 0;
    for(int r = 0; r < rowNum; r++){
        int temp = 0;
        for(int c = 0; c < columnNum; c++){
            if(elements[r][c] == 0){temp++;}
        }
        if(temp > zeros){zeros = temp; e = r;}
    }
    return e;
}

int Matrix::findZerosColumn() {
    int e = -1;
    int zeros = 0;
    for(int c = 0; c < columnNum; c++){
        int temp = 0;
        for(int r = 0; r < rowNum; r++){
            if(elements[r][c] == 0){temp++;}
        }
        if(temp > zeros){zeros = temp; e = c;}
    }
    return e;
}

Matrix Matrix::createMinor(int r, int c) {
    Matrix minor = Matrix(rowNum-1, columnNum-1);
    for(int r0 = 0; r0 < rowNum; r0++){
        for(int c0 = 0; c0 < columnNum; c0++){
            if(c == c0 || r == r0){ continue;}
            int r1 = r0;
            int c1 = c0;
            if(r0 > r){r1--;}
            if(c0 > c){c1--;}
            minor.elements[r1][c1] = elements[r0][c0];
        }
    }
    return minor;
}

double Matrix::determinant() {
    if(!isSquare()){return {};}
    double res = 0;
    if(isDiagonal() || isUpperTriangular() || isLowerTriangular()){
        vector<double> diagonal = getDiagonal();
        res = diagonal[0];
        for(int e = 1; e < diagonal.size(); e++){
            res *= diagonal[e];
        }
        return res;
    }
    if(rowNum == 2 & columnNum == 2){
        return elements[0][0]*elements[1][1]-elements[1][0]*elements[0][1];
    }
    int r = findZerosRow();
    int c = findZerosColumn();
    vector<double> r0, c0;
    r0 = getRow(r); c0 = getColumn(c);
    bool row = true;
    if(count(r0.begin(), r0.end(), 0) < count(c0.begin(), c0.end(), 0)){
        row = false;
    }
    if(row){
        for(int e = 0; e < r0.size(); e++){
            res += elements[r][e]*pow(-1, r+e)* createMinor(r, e).determinant();
        }
        return res;
    }
    for(int e = 0; e < c0.size(); e++){
        res += elements[e][c]*pow(-1, c+e)* createMinor(e,c).determinant();
    }
    return res;

}
