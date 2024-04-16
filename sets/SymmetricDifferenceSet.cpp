///// @Jollu
// Symmetric Difference Of Ordered Sets

#include <iostream>
#include <vector>

template<typename T, template<class> class V>
V<T> symmetric_dif(const V<T> &first, const V<T> &second) {
    size_t first_in = 0;
    size_t second_in = 0;
    V<T> res;
    while (first_in < first.size() && second_in < second.size()) {
        if (first.at(first_in) < second.at(second_in)) {
            res.push_back(first.at(first_in));
            first_in++;
        } else if (first.at(first_in) > second.at(second_in)) {
            res.push_back(second.at(second_in));
            second_in++;
        } else {
            first_in++;
            second_in++;
        }
    }
    while (first_in < first.size()) {
        res.push_back(first.at(first_in));
        first_in++;
    }
    while (second_in < second.size()) {
        res.push_back(second.at(second_in));
        second_in++;
    }
    return res;
}

std::vector<double> symmetric_dif(const std::vector<double> &first, const std::vector<double> &second) = delete;

int main() {
    const std::vector<int> firstSet{1, 2, 3, 5, 8};
    const std::vector<int> secondSet{3, 6, 8, 12, 24, 47};
    const std::vector<int> resultUnion(symmetric_dif(firstSet, secondSet));
    for (const auto &element: resultUnion)
        std::cout << element << "  ";
}