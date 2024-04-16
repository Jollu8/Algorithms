///// @Jollu
// Difference Between OrderedSets

#include <iostream>
#include <vector>


template<typename T>
std::vector<T> diff(const std::vector<T> &first, const std::vector<T> &second) {
    size_t first_in = 0;
    size_t second_in = 0;
    std::vector<T> res{};

    while (first_in < first.size() && second_in < second.size()) {
        if (first.at(first_in) == second.at(second_in)) {
            first_in++;
            second_in++;
        } else {
            if (first.at(first_in) < second.at(second_in)) {
                res.push_back(first.at(first_in));
                first_in++;
            } else {
                second_in++;
            }
        }
    }
    while (first_in < first.size()) {
        res.push_back(first.at(first_in));
        first_in++;
    }
    return res;
}

std::vector<double> diff(const std::vector<double> &first, const std::vector<double> &second) = delete;

int main() {
    const std::vector<int> f1{12, 34, 55, 34, 33332, 23};
    const std::vector<int> f2{12, 34, 55, 34, 24, 47};
    const std::vector<int> resultDifference(diff(f1, f2));
    for (const auto &element: resultDifference)
        std::cout << element << "  ";
    return EXIT_SUCCESS;
}