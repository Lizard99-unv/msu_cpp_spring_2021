#pragma once
#include <iostream>


class Matrix
{
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t size;
    public:
        ProxyRow();
        ProxyRow(size_t j);
        int getSize();
        ProxyRow& operator= (ProxyRow &prox);
        int32_t& operator[](size_t j);
        ~ProxyRow();
    };
public:
    Matrix(size_t i, size_t j);
    int getRow() const;
    int getCol() const;
    ProxyRow& operator[](size_t i);
    Matrix& operator *= (int32_t num);
    Matrix& operator += (const Matrix& matrix);
    bool operator == (const Matrix& matrix) const;
    bool operator != (const Matrix& matrix) const;
    friend std::ostream& operator<< (std::ostream &out, const Matrix &matrix);
    ~Matrix();
private:
    ProxyRow *rows_;
    size_t row_numbers;
    size_t col_numbers;
};

std::ostream& operator<< (std::ostream &out, const Matrix &matrix);