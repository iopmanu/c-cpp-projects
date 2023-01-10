#include "../include/s21_matrix_oop.h"
#include <stdlib.h>

LinearAlgebra::Matrix::Matrix() : rows(0), columns(0), matrix(nullptr) {}

LinearAlgebra::Matrix::Matrix(int rows_, int columns_) : rows(rows_), columns(columns_) {
    if (rows < 1 || columns < 1) {
        throw std::invalid_argument("Wrong value of rows/columns");
    }

    matrix = new double[rows * columns]();
}

LinearAlgebra::Matrix::Matrix(const Matrix &other) : rows(other.rows), columns(other.columns) {
    matrix = new double[other.rows * other.columns];
    std::copy_n(other.matrix, other.rows * other.columns, matrix);
}

LinearAlgebra::Matrix::Matrix(Matrix &&other) {
    rows = std::move(other.rows);
    columns = std::move(other.columns);
    matrix = std::move(other.matrix);
}

LinearAlgebra::Matrix::~Matrix() {
    rows = 0;
    columns = 0;
    delete[] matrix;
}

double &LinearAlgebra::Matrix::operator()(int row, int col) {
    if (row >= rows || col >= columns) {
        throw std::invalid_argument("Wrong value of rows/columns");
    }

    return matrix[row * columns + col];
}

const double &LinearAlgebra::Matrix::At(int row, int col) const {
    if (row >= rows || col >= columns) {
        throw std::invalid_argument("Wrong value of rows/columns");
    }

    return matrix[row * columns + col];
}

void LinearAlgebra::Matrix::SetColumns(const int &columns_) {
    if (columns_ < 1) {
        throw std::invalid_argument("Wrong value of columns");
    }

    Matrix reshaped{rows, columns_};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < std::min(columns, columns_); j++) {
            reshaped(i, j) = At(i, j);
        }
    }

    columns = columns_;
    *this = reshaped;
}

void LinearAlgebra::Matrix::SetRows(const int &rows_) {
    if (rows_ < 1) {
        throw std::invalid_argument("Wrong value of rows");
    }

    Matrix reshaped{rows_, columns};

    for (int i = 0; i < std::min(rows, rows_); i++) {
        for (int j = 0; j < columns; j++) {
            reshaped(i, j) = At(i, j);
        }
    }

    rows = rows_;
    *this = reshaped;
}

bool LinearAlgebra::Matrix::EqMatrix(const Matrix &other) const {
    if (other.rows != rows || other.columns != columns) {
        return false;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (std::fabs(At(i, j) - other.At(i, j)) >= EPS) {
                return false;
            }
        }
    }

    return true;
}

void LinearAlgebra::Matrix::SumMatrix(const Matrix &other) {
    if (other.rows != rows || other.columns != columns) {
        throw std::logic_error("Rows and columns should be the same");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) += other.At(i, j);
        }
    }
}

void LinearAlgebra::Matrix::SubMatrix(const Matrix &other) {
    if (other.rows != rows || other.columns != columns) {
        throw std::logic_error("Rows and columns should be the same");
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) -= other.At(i, j);
        }
    }
}

void LinearAlgebra::Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) *= num;
        }
    }
}

void LinearAlgebra::Matrix::MulMatrix(const Matrix &other) {
    if (columns != other.rows) {
        throw std::logic_error(
            "Columns of the left matrix shoud be equal to rows of the right one");
    }

    Matrix result{rows, other.columns};

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.columns; j++) {
            for (int k = 0; k < columns; k++) {
                result(i, j) += At(i, k) * other.At(k, j);
            }
        }
    }

    *this = std::move(result);
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::Transpose() const {
    Matrix result{GetColumns(), GetRows()};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result(i, j) = At(j, i);
        }
    }

    return result;
}

bool LinearAlgebra::Matrix::operator==(const Matrix &other) noexcept { return EqMatrix(other); }
bool LinearAlgebra::Matrix::operator!=(const Matrix &other) noexcept { return !EqMatrix(other); }

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator=(const Matrix &other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;

        delete[] matrix;
        matrix = new double[other.rows * other.columns];
        std::copy_n(other.matrix, other.rows * other.columns, matrix);
    }

    return *this;
}

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator=(Matrix &&other) noexcept {
    if (this != &other) {
        std::swap(rows, other.rows);
        std::swap(columns, other.columns);
        std::swap(matrix, other.matrix);
    }

    return *this;
}

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator+=(const Matrix &other) {
    SumMatrix(other);
    return *this;
}

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator-=(const Matrix &other) {
    SubMatrix(other);
    return *this;
}

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator*=(const double num) {
    MulNumber(num);
    return *this;
}

LinearAlgebra::Matrix &LinearAlgebra::Matrix::operator*=(const Matrix &other) {
    MulMatrix(other);
    return *this;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator+(const Matrix &other) const {
    Matrix result{*this};
    result.SumMatrix(other);
    return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator-(const Matrix &other) const {
    Matrix result{*this};
    result.SubMatrix(other);
    return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator*(const Matrix &other) const {
    Matrix result{*this};
    result.MulMatrix(other);
    return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::operator*(const double num) const {
    Matrix result{*this};
    result.MulNumber(num);
    return result;
}