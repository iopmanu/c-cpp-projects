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

double LinearAlgebra::Matrix::Determinant() const {
    if (rows != columns) {
        throw std::logic_error("Determinant calculation error. Matrix should be squared");
    }

    double answer = 1.0;

    if (rows == 1) {
        return At(0, 0);
    } else {
        int gaussFactor = 1;
        LinearAlgebra::Matrix temp{*this};
        temp.GaussAlgo(&gaussFactor);

        answer *= gaussFactor;

        for (int i = 0; i < rows; i++) {
            answer *= temp.At(i, i);
        }

        answer = (std::fabs(answer) < EPS) ? 0 : answer;
    }

    return answer;
}

void LinearAlgebra::Matrix::GaussAlgo(int *gaussFactor) {
    for (int i = 0; i < std::min(rows, columns); i++) {
        double element = At(i, i);
        int index = i;

        for (int j = i + 1; j < rows; j++) {
            if (std::fabs(At(j, i)) > std::fabs(element)) {
                element = At(i, i);
                index = j;
            }
        }

        // column with zero values
        if (std::fabs(element) < EPS)
            continue;
        else if (index != i) {
            (*gaussFactor) *= -1;
            SwapRows(i, index);
        }

        for (int j = i + 1; j < rows; j++) {
            AddRows(i, j, (-1) * At(j, i) / At(i, i));
        }
    }
}

void LinearAlgebra::Matrix::SwapRows(int one, int another) {
    if (one >= rows || another >= rows) {
        throw std::invalid_argument("Invalid indexes of rows to swap");
    } else {
        for (int i = 0; i < columns; i++) {
            std::swap((*this)(one, i), (*this)(another, i));
        }
    }
}

void LinearAlgebra::Matrix::AddRows(int one, int another, double factor) {
    if (one >= rows || another >= rows) {
        throw std::invalid_argument("Invalid indexes of rows to swap");
    } else {
        for (int i = 0; i < columns; i++) {
            (*this)(another, i) += At(one, i) * factor;
        }
    }
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::Minor(int row, int column) const {
    Matrix minor{rows - 1, columns - 1};

    int di = 0, dj = 0;

    for (int i = 0; i < rows - 1; i++) {
        if (i == row) di = 1;
        dj = 0;

        for (int j = 0; j < columns - 1; j++) {
            if (j == column) dj = 1;
            minor(i, j) = At(i + di, j + dj);
        }
    }

    return minor;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::CalcComplements() const {
    Matrix result{rows, columns};

    if (rows != columns) {
        throw std::logic_error("Impossible to calculate complements for not squared matrix");
    }

    if (rows == 1) {
        result(0, 0) = At(0, 0);
        return result;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Matrix minor = Minor(i, j);

            int8_t sign = ((i + j) % 2 == 0) ? 1 : -1;

            result(i, j) = minor.Determinant() * sign;
        }
    }

    return result;
}

LinearAlgebra::Matrix LinearAlgebra::Matrix::InverseMatrix() const {
    if (rows != columns) {
        throw std::logic_error(
            "To get inverse matrix, shape of the source matrix should be squared");
    }

    Matrix result{rows, columns};

    double determinant = Determinant();
    if (std::fabs(determinant) < EPS) {
        throw std::logic_error("Zero det in matrix invertion");
    }

    result = CalcComplements().Transpose();
    result *= (1 / determinant);

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