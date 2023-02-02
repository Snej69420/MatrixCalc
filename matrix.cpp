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

Matrix::Matrix(const std::string& json) {
    std::ifstream input(json); // lees de inputfile
    nlohmann::json j;
    input >> j;
    if(j["type"] != "matrix"){
        return;
    }
    rowNum = j["rows"];
    columnNum = j["columns"];
    vector<double> t0(columnNum, 0);
    elements = vector<vector<double>>(rowNum, t0);
    isVector = false;
    if(rowNum == 1 || columnNum == 1){isVector = true;}
    int r = 0;
    int c = 0;
    for(const auto& e : j["matrix"]){
        c = 0;
        for(const auto& e0 : e){
            elements[r][c] = e0;
            c++;
        }
        r++;
    }
    }

bool Matrix::isEmpty() const {
    if(columnNum == 0 || rowNum == 0){
        return true;
    }
    return false;
}

unsigned int Matrix::biggestElement() {
    unsigned int size = 0;
    std::string temp;
    for (int r = 0; r < rowNum; r++) {
        for (int c = 0; c < columnNum; c++) {
            elements[r][c] += 0.0;
            std::ostringstream oss;
            oss << std::setprecision(8) << std::noshowpoint << elements[r][c];
            temp = oss.str();
            if(temp.size() > size){
                size = temp.size();
            }
        }
    }
    return size;
}

void Matrix::printHelp(int size, int r, Matrix a, int sizeA){
    int remaining = 0;
    std::string temp;
    cout << "| ";
    for (int c = 0; c < columnNum; c++) {
        std::ostringstream oss;
        oss << std::setprecision(8) << std::noshowpoint << elements[r][c];
        temp = oss.str();
        remaining = size - temp.size();
        for(int k = 0; k < remaining/2; k++){
            cout << " ";
        }
        cout << std::setprecision(8) << std::noshowpoint << elements[r][c];
        cout << " ";
        for(int k = 0; k < remaining/2; k++){
            cout << " ";
        }
        if(remaining%2 == 1){
            cout << " ";
        }

    }
    cout << "|";
    if(a.isEmpty()){ return;}
    cout << "| ";
    for (int c = 0; c < a.columnNum; c++) {
        std::ostringstream oss;
        oss << std::setprecision(8) << std::noshowpoint << a.elements[r][c];
        temp = oss.str();
        remaining = sizeA - temp.size();
        for(int k = 0; k < remaining/2; k++){
            cout << " ";
        }
        cout << a.elements[r][c];
        cout << " ";
        for(int k = 0; k < remaining/2; k++){
            cout << " ";
        }
        if(remaining%2 == 1){
            cout << " ";
        }
    }
    cout << "|";

}

void Matrix::print() {
    int size = biggestElement();
    int remaining = 0;
    std::string temp;
    for (int r = 0; r < rowNum; r++) {
        printHelp(size, r);
        cout << endl;
    }
    cout << endl;
}

void Matrix::print(Matrix a) {
    int size = biggestElement();
    int remaining = 0;
    int sizeA = a.biggestElement();
    std::string temp;
    for (int r = 0; r < rowNum; r++) {
        printHelp(size, r, a, sizeA);
        cout << endl;
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
            sum += std::abs(elements[r][c]);
        }
        if(std::abs(elements[r][r]) < sum){
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
            sum += std::abs(elements[r][c]);
        }
        if(std::abs(elements[r][r]) <= sum){
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

bool Matrix::isNullRow(vector<double> r) {
    for(int e = 0; e < r.size(); e++){
        if(r[e] != 0){return false;}
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

void Matrix::setMatrix(vector<vector<double>> matrix) {
    if(matrix.size() != rowNum){ return;}
    for(const auto& i : matrix){
        if(i.size() != columnNum){ return;}
    }
    for(int r = 0; r < rowNum; r++){
        for(int c = 0; c < columnNum; c++){
            elements[r][c] = matrix[r][c];
        }
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
    if(r >= rowNum){return {};}
    vector<double> res(columnNum);
    for(int c = 0; c < columnNum; c++){
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

void Matrix::swapRows(int r0, int r1){
    vector<double> temp = getRow(r0);
    setRow(r0, getRow(r1));
    setRow(r1, temp);
}

vector<double> Matrix::addingRows(vector<double> r0, vector<double> r1) {
    if(r0.size() != r1.size()){return {};}
    vector<double> temp(r0.size(), 0);
    for(int e = 0; e < r0.size(); e++){
        temp[e] = r0[e] + r1[e];
    }
    return temp;
}

vector<double> Matrix::multiplyRow(double n, vector<double> r0) {
    for(int e = 0; e < r0.size(); e++){
        r0[e] = r0[e]*n;
    }
    return r0;
}

Matrix Matrix::solveTriangular(Matrix a, Matrix b, bool upper) {
    int startRow = 0; int endRow = a.rowNum;
    int startColumn = 0; int endColumn = a.columnNum;
    if(upper){
        startRow = -endRow+1; endRow = 1;
        startColumn = -endColumn+1; endColumn = 1;
    }
    vector<double> result(b.rowNum, 0);

    for(int r = startRow; r < endRow; r++){
        result[abs(r)] = b.elements[abs(r)][0];
        cout << "x" << abs(r) << " = " << b.elements[abs(r)][0];
        for(int c = startColumn; c < endColumn; c++){
            if(c > r){ break;}
            if(c == r){
                cout << endl << "x" << abs(r) << " = " << result[abs(r)]/a.elements[abs(r)][abs(c)] << endl;
                result[abs(r)] = result[abs(r)]/a.elements[abs(r)][abs(c)];
                break;
            }
            std::string oper = " + ";
            if(-result[abs(c)]*a.elements[abs(r)][abs(c)] < 0){
                oper = " - ";
            }
            cout << oper << std::abs(result[abs(c)]*a.elements[abs(r)][abs(c)]);
            result[abs(r)] -= result[abs(c)]*a.elements[abs(r)][abs(c)];
        }
    }
    Matrix res = Matrix(b.rowNum, b.columnNum);
    res.setColumn(0, result);
    return res;

}

Matrix Matrix::Gauss_Jordan(Matrix a) {
    Matrix org = *this;
    Matrix b = a;

    bool echelonForm = false;
    if(a.isEmpty()){ echelonForm = true;
    }
    if(org.rowNum != b.rowNum and not echelonForm){ return {};}

    bool inverse = false;
    if(a.isIdentity() && rowNum == b.rowNum && columnNum == b.columnNum and !echelonForm){
        if(determinant() == 0){ return {};}
        inverse = true;
    }
    if(!inverse && a.columnNum != 1 && !echelonForm){ return {};}

    int r = 0;
    int c = 0;
    int row0 = 0;
    int row1 = 0;

    std::cout << "Original: \n";
    org.print(b);
    bool noSolution = false;
    bool infiniteSolutions = false;
    for(c = 0; c < org.columnNum; c++){
        double biggest = 0;
        for(r = 0+c; r < org.rowNum; r++){
            double current = std::abs(org.elements[r][c]);
            if(current > biggest){biggest = current; row1 = r;}
        }
        if(printSteps) { cout << "Swap: row " << row0 << " <-> row " << row1 << endl; }
        org.swapRows(row0, row1);
        b.swapRows(row0, row1);
        if(printSteps) { org.print(b); }
        if(printSteps) {cout << "Multiply row " << row0 << " with " << 1/org.getRow(row0)[c] << endl;}
        double mult = 1/org.getRow(row0)[c];
        org.setRow(row0, multiplyRow(mult, org.getRow(row0)));
        b.setRow(row0, multiplyRow(mult, b.getRow(row0)));
        if(printSteps) { org.print(b); }
        for(r = 0; r < org.rowNum; r++){
            if(r == row0){ continue;}
            std::string oper = " ";
            if(-org.getRow(r)[c] >= 0){
                oper = " + ";
            }
            if(printSteps) { cout << "row " << r << oper << -org.getRow(r)[c] << " * row " << row0 << endl; }
            mult = -org.getRow(r)[c];
            vector<double> temp = multiplyRow(mult,org.getRow(row0));
            vector<double> temp1 = multiplyRow(mult, b.getRow(row0));
            org.setRow(r, addingRows(org.getRow(r), temp));
            b.setRow(r, addingRows(b.getRow(r), temp1));
            if(printSteps) { org.print(b); }
            if(isNullRow(org.getRow(r)) && b.elements[r][0] != 0){
                noSolution = true;
                break;
            }
            if(isNullRow(org.getRow(r)) && b.elements[r][0] == 0){
                infiniteSolutions = true;
                break;
            }
        }
        if(noSolution || infiniteSolutions){ break;}
        row0++;
    }
    if(noSolution){
        cout << "This system has no solutions!" << endl;
        return {};
    }
    if(infiniteSolutions){
        cout << "This system has infinitely many solutions!" << endl;
        return {};
    }
    if(echelonForm){
        std::cout << "Echelon form: \n";
        return org;
    }
    if(inverse){return b;}
    if(org.isDiagonal()){
        return b;
    }
    if(org.isLowerTriangular()){
        return solveTriangular(org, b);
    }
    if(org.isUpperTriangular()){
        return solveTriangular(org, b, true);
    }
}

std::vector<std::vector<double>> Matrix::calculateColumnSpace() {

}