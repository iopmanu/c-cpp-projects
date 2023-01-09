#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#define EPS 1e-7

#include <algorithm>
#include <exception>

namespace LinearAlgebra {
    class Matrix {
        private:
            std::size_t rows, columns;
            double **matrix;

        public:
            Matrix();
            Matrix(std::size_t rows, std::size_t columns);
            Matrix(const Matrix &other);
            Matrix(Matrix &&other);
            ~Matrix();

            constexpr std::size_t GetRows() const noexcept;
            constexpr std::size_t GetColumns() const noexcept;
            double &operator()(std::size_t row, std::size_t col);
            const double &At(std::size_t i, std::size_t j) const;

            void SetRows(const std::size_t &rows_);
            void SetColumns(const std::size_t &columns);

            Matrix operator+(const Matrix &other) const;
            Matrix operator-(const Matrix &other) const;
            Matrix operator*(const Matrix &other) const;
            Matrix operator*(double number)const;

            bool operator==(const Matrix &other) noexcept;
            Matrix &operator=(const Matrix &other);
            Matrix &operator=(Matrix &&other) noexcept;
            Matrix &operator+=(const Matrix &other);
            Matrix &operator-=(const Matrix &other);
            Matrix &operator*=(const Matrix &other);
            Matrix &operator*=(double number);

            bool EqMatrix(const Matrix &other) const;
            void SumMatrix(const Matrix &other) const;
            void SubMatrix(const Matrix &other) const;
            void MulNumber(double num) const;
            void MulMatrix(const Matrix&other) const;
            Matrix Transpose() const;
            Matrix CalcComplements() const;
            double Determinant() const;
            Matrix InverseMatrix() const;
    };
}

#endif // SRC_MATRIX_H_