///// @Jollu
// Ternary Searching sorted Element

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>




template<typename T>
int ternary_search_max(const T &collection) {
    if (collection.empty()) return -1;

    int left = 0;
    int right = collection.size() - 1u;
    while (left != right) {
        const int m1 = left + (right - left) / 3;
        const int m2 = right - (right - left) / 3;
        if (collection[m2] > collection[m1]) left = m1 + 1;
        else right = m2 - 1;

    }
    return left;
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 7, 9};
    std::cout << "Index max Element: " << ternary_search_max(vec);
}