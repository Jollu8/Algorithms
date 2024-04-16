////@jollu

// Bubble Sorting

#include <iostream>
#include <vector>


template<typename Collection, typename Comparator, typename = typename Collection::size_type>
void bubble_sorting(Collection &collection, Comparator comparator) noexcept {
    for (typename Collection::size_type i = 0; i < collection.size(); i++) {
        for (typename Collection::size_type j = 0; j < collection.size() - 1; j++) {
            if (comparator(collection[j], collection[j + 1])) {
                std::swap(collection[j], collection[j + 1]);
            }
        }
    }

}


int main() {
    std::vector<int> vec = {1, 2, 5, 3, 4, 6, 8, 6, 5, 3, 3, 2, 5, 7,};
    bubble_sorting(vec, [](auto a, auto b) {
        return a < b;
    });

    for (auto &i: vec) {
        std::cout << i << " ";
    }
}