////@jollu

// Insertion Sorting

#include <iostream>
#include <vector>


template<typename Collection, typename Predicate, typename = typename Collection::iterator>
void insertion_sorting(Collection &collection, Predicate predicate) noexcept {
    for (auto i = 1; i < collection.size(); i++) {
        for (auto j = i; (j > 0) && predicate(collection[j], collection[j - 1]); j--) {
            std::swap(collection[j], collection[j - 1]);
        }
    }

}


int main() {
    std::vector<unsigned int> vec = {1, 2, 5, 3, 4, 6, 8, 6, 5, 3, 3, 2, 5, 7,};
    insertion_sorting(vec, [](auto a, auto b) {
        return a > b;
    });

    for (auto &i: vec) {
        std::cout << i << " ";
    }
}
