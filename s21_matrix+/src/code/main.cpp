#include "../include/s21_matrix_oop.h"

int main() {
    LinearAlgebra::Matrix result{2, 2};

    result(0, 0) = 1;
    result(0, 1) = 2;
    result(1, 1) = 3;
    result(1, 0) = 4;

    result = result + result;

    for (int i = 0; i < result.GetRows(); i++) {
        for (int j = 0; j < result.GetColumns(); j++) {
            std::cout << result.At(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}