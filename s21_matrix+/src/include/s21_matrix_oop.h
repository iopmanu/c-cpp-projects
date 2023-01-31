#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define EPS 1e-6

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace LinearAlgebra {
class S21Matrix {
private:
    int rows, columns;
    double *matrix;

public:
    S21Matrix();
    S21Matrix(int rows, int columns);
    S21Matrix(const S21Matrix &other);
    S21Matrix(S21Matrix &&other);
    ~S21Matrix();

    constexpr int GetCols() const noexcept { return columns; }
    constexpr int GetRows() const noexcept { return rows; }

    double &operator()(int row, int col);
    const double &At(int row, int col) const;

    void SetRows(const int &rows_);
    void SetColumns(const int &columns);

    S21Matrix operator+(const S21Matrix &other) const;
    S21Matrix operator-(const S21Matrix &other) const;
    S21Matrix operator*(const S21Matrix &other) const;
    S21Matrix operator*(const double number) const;

    bool operator==(const S21Matrix &other) noexcept;
    bool operator!=(const S21Matrix &other) noexcept;
    S21Matrix &operator=(const S21Matrix &other);
    S21Matrix &operator=(S21Matrix &&other) noexcept;
    S21Matrix &operator+=(const S21Matrix &other);
    S21Matrix &operator-=(const S21Matrix &other);
    S21Matrix &operator*=(const S21Matrix &other);
    S21Matrix &operator*=(double number);

    bool EqMatrix(const S21Matrix &other) const;
    void SumMatrix(const S21Matrix &other);
    void SubMatrix(const S21Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix &other);

    S21Matrix Transpose() const;
    S21Matrix CalcComplements() const;
    double Determinant() const;
    void GaussAlgo(int *gaussFactor);
    void SwapRows(int one, int another);
    void AddRows(int one, int another, double factor);
    S21Matrix Minor(int row, int column) const;
    S21Matrix InverseMatrix() const;
};
}  // namespace LinearAlgebra

#endif  // SRC_MATRIX_H_