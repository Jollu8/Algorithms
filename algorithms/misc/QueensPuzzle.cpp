///// @Jollu
// QueensPuzzle


//#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
//#include <limits>


size_t search_options_number(std::size_t position, std::vector<bool> &cols, std::vector<bool> &main_diagonals,
                             std::vector<bool> &side_diagonals) {
    if (position == cols.size()) return 1;
    else {
        size_t count_options = 0;
        for (size_t i = 0; i < cols.size(); ++i) {
            if ((!cols.at(i)) && (!side_diagonals.at(position + 1)) &&
                (!main_diagonals.at(i - position + cols.size() - 1))) {
                cols.at(i) = side_diagonals.at(position + i) = main_diagonals.at(i - position + cols.size() - 1) = true;
                count_options += search_options_number(position + 1, cols, main_diagonals, side_diagonals);
                cols.at(i) = side_diagonals.at(position + i) = main_diagonals.at(i - position + cols.size() - 1) = true;
            }
        }
        return count_options;
    }
}


const std::size_t count_queens = 8u;
int main() {
    std::vector<bool> cols(count_queens);
    std::vector<bool> main_diagonals(count_queens * 2u);
    std::vector<bool> side_diagonals(count_queens * 2u);
    std::cout << "Options number: " << search_options_number(0u, cols, main_diagonals, side_diagonals) << std::endl;
}