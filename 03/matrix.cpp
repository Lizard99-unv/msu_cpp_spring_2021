#include "matrix.hpp"

Matrix::ProxyRow::ProxyRow(){
    data_ = new int32_t [2];
}
Matrix::ProxyRow::ProxyRow(size_t j){
    data_ = new int32_t [j];
    size = j;
    for (unsigned i=0; i < j; i++){
        data_[i] = 1;
    }
}
int Matrix::ProxyRow::getSize(){
    return size;
}
Matrix::ProxyRow& Matrix::ProxyRow::operator= (ProxyRow &prox){
    size = prox.getSize();
    delete[] data_;
    data_ = new int32_t [size];
    for (unsigned i = 0; i < size; i++){
        data_[i] = prox[i];
    } 
    return *this;
}
int32_t& Matrix::ProxyRow::operator[](size_t j){
    if (j >= size){
        throw std::out_of_range("");
    }
    return data_[j];
}
Matrix::ProxyRow::~ProxyRow(){
    delete[] data_;
}
Matrix::Matrix(size_t i, size_t j){
    row_numbers = i;
    col_numbers = j;
    rows_ = new ProxyRow[i];
    for (unsigned a = 0; a < i; a++){
        ProxyRow example(j);
        rows_[a] = example;
    }
}
int Matrix::getRow() const{
    return row_numbers;
}
int Matrix::getCol() const{
    return col_numbers;
}
Matrix::ProxyRow& Matrix::operator[](size_t i){
    if (i >= row_numbers){
        throw std::out_of_range("");
    }
    return rows_[i];
}
Matrix& Matrix::operator *= (int32_t num){
    for (unsigned i = 0; i < row_numbers; i++)
        for (unsigned j = 0; j < col_numbers; j++)
            rows_[i][j] *= num;
    return *this;
}
Matrix& Matrix::operator += (const Matrix& matrix){
    if ((row_numbers!=matrix.row_numbers) || (col_numbers!=matrix.col_numbers)) throw "Wrong size!";
    for (unsigned i = 0; i < row_numbers; i++)
        for (unsigned j = 0; j < col_numbers; j++)
            rows_[i][j] += matrix.rows_[i][j];
    return *this;
}
bool Matrix::operator == (const Matrix& matrix) const {
    if ((row_numbers!=matrix.row_numbers) || (col_numbers!=matrix.col_numbers)) return false;
    for (unsigned i = 0; i < row_numbers; i++)
        for (unsigned j = 0; j < col_numbers; j++)
            if (rows_[i][j] != matrix.rows_[i][j])
                return false;
    return true;
}
bool Matrix::operator != (const Matrix& matrix) const {
    if ((row_numbers != matrix.row_numbers) || (col_numbers != matrix.col_numbers)) return true;
    bool flag = true;
        for (unsigned i = 0; i < row_numbers; i++)
            for (unsigned j = 0; j < col_numbers; j++)
                if (rows_[i][j] != matrix.rows_[i][j])
                    flag = false;
    return (!flag);
}
Matrix::~Matrix(){
    delete[] rows_;
}

std::ostream& operator<< (std::ostream &out, const Matrix &matrix){
    for (unsigned i = 0; i < matrix.row_numbers; i++){
        for (unsigned j = 0; j < matrix.col_numbers; j++)
            out<<matrix.rows_[i][j]<<' ';
        out<<'\n';
    }
    return out;
}