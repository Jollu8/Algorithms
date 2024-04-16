///// @Jollu
// Intersection Of The Ordered Sets

#include <iostream>
#include <vector>



template<typename T>
std::vector<T> intersection(const std::vector<int> &first, const std::vector<T> &second) {
    std::size_t first_in = 0;
    std::size_t second_in = 0;
    std::vector<T> res{};


    while (first_in < first.size() && second_in < second.size()) {
        if (first.at(first_in) == second.at(second_in)) {
            res.push_back(first.at(first_in));
            first_in++;
            second_in++;
        } else {
            if (first.at(first_in) < second.at(second_in)) {
                first_in++;
            } else {
                second_in++;
            }
        }
    }
    return res;
}

std::vector<double> intersection(const std::vector<double> &first, const std::vector<double> &second) = delete;

int main() {
    const std::vector<int> firstSet{1, 2, 3, 5, 8};
    const std::vector<int> secondSet{3, 6, 8, 12, 24, 47};
    const std::vector<int> resultIntersection(intersection(firstSet, secondSet));
    for (const auto &element: resultIntersection)
        std::cout << element << "  ";
}