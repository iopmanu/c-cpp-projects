#include "../include/s21_matrix_oop.h"

void printing(LinearAlgebra::Matrix source) {
    for (int i = 0; i < source.GetRows(); i++) {
        for (int j = 0; j < source.GetColumns(); j++) {
            std::cout << source.At(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    LinearAlgebra::Matrix result{2, 2};
    LinearAlgebra::Matrix another{2, 2};

    result(0, 0) = 1;
    result(0, 1) = 2;
    result(1, 0) = 4;
    result(1, 1) = 3;

    another(0, 0) = 1;
    another(0, 1) = 2;
    another(1, 0) = 13;
    another(1, 1) = 7;

    result -= another * result;
    LinearAlgebra::Matrix alg = result.InverseMatrix();
    printing(alg);

    std::cout << "\n\n\n";

    printing(result);
    return 0;
}