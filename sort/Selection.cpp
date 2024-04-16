///// @Jollu
// Selection Sorting


#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, typename Predicate, typename = typename T::iterator>
void selection_sorting(T &collection, Predicate comparator) noexcept {
    for (typename T::size_type i = 0; i < collection.size() - 1; i++) {
        typename T::size_type key_element_index = i;
        for (typename T::size_type j = i + 1; j < collection.size(); j++)
            if (comparator(collection[j], collection[key_element_index]))
                key_element_index = j;

        if (key_element_index != i)
            std::swap(collection[i], collection[key_element_index]);
    }
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 0, 6, 5, 4, 3, 2, 73, 41};
    selection_sorting(vec, [](auto a, auto b) { return a > b; });
    auto print = [](auto i) { std::cout << i << ","; };
    std::for_each(vec.begin(), vec.end(), print);
}