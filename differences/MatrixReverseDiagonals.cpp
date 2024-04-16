///// @Jollu
// Matrix Reverse Diagonals


//#include <string>
#include <vector>
//#include <sstream>
#include <iostream>

void print_reverse_diagonals(const std::vector<std::vector<int>> &matrix) {
    const size_t matrix_size = matrix.size();
    for (auto i = 0u; i < matrix_size; ++i) {
        auto k = i;
        auto j = 0u;
        for (; (k >= 0) && (j < matrix_size); --k, --j)
            std::cout << matrix[k][j];

        std::cout << std::endl;
    }
    for (auto j = 1u; j < matrix_size; ++j) {
        auto k = j;
        auto i = matrix_size - 1;
        for (; (i >= 0) && (k < matrix_size); --i, ++k)
            std::cout << matrix[i][k];
        std::cout << std::endl;
    }
}


int main() {
    const std::vector<std::vector<int>> matrix = {
            {2, 4, 5, 1},
            {1, 0, 3, 2},
            {9, 8, 2, 4},
            {9, 7, 8, 6}
    };

    print_reverse_diagonals(matrix);
}