///// @Jollu
// 832. Quick Sort Recursive
// used std::nth_element


#include <cstddef>
#include <algorithm>
#include <iostream>
#include <list>


template<typename It>
void quick_sort_recursive(const It &start, const It &end) {
    if (end - start < 2) return;
    It res = start + (end - start) / 2;
    std::nth_element(start, res, end);
    quick_sort_recursive(start, res);
    quick_sort_recursive(res, end);
}

void quick_sort_recursive(const std::vector<double> start, const std::vector<double> &end) = delete;

int main() {
    std::vector<int> vec{1, 41, 2, 3, 4, 5, 6, 4, 3, 4, 5, 7, 8, 5, 4, 33, 73};
    quick_sort_recursive(vec.begin(), vec.end());
    for (auto i: vec) {
        std::cout << i << ",";
    }
}
