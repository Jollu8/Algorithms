///// @Jollu
// Quick Sorting


#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void quickSort(T &ar, size_t left, size_t right) {
    size_t l = left;
    size_t r = right;
    auto key = ar[(left + right) / 2];

    while (l <= r) {
        while (ar[l] < key) {
            l++;
        }
        while (ar[r] > key) {
            r--;
        }
        if (l <= r) {
            std::swap(ar[l++], ar[r--]);
        }
    }

    if (l < right) {
        quickSort(ar, l, right);
    }
    if (r > left) {
        quickSort(ar, left, r);
    }
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 0, 6, 5, 4, 3, 2, 73, 41};
    quickSort(vec, 0u, vec.size());

    auto print = [](auto i) { std::cout << i << ","; };
    std::for_each(vec.begin(), vec.end(), print);
}