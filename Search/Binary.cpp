///// @Jollu
// Binary Searching sorted Element

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


template<typename T>
using ValType = typename T::value_type;

template<typename T>
using SizeType = typename T::size_type;

template<typename T, template<class> typename Container>
T binary_none_recursive_search(Container<T> &collection, T value) {
//    std::sort(collection.begin(), collection.end()); // if collection not sorted
    std::size_t begin = 0u;
    std::size_t end = collection.size();
    while (begin <= end) {
        std::size_t middle = (begin + end) / 2;
        if (collection[middle] == value) return value;
        else if (collection[middle] > value) end = middle - 1;
        else begin = middle + 1;
    }
    return -1;
}

template<typename T>
int binary_search_recursive(const T &collection, const ValType<T> &value) noexcept {
    std::function<int(const T &, const ValType<T> &, SizeType<T>, SizeType<T>)> search_impl;
    search_impl = [&search_impl](const auto &collection, const auto &value, const auto begin, const auto end) -> int {
        const SizeType<T> middle = (begin + end) / 2;
        if (begin <= end) {
            if (collection[middle] < value) {
                return search_impl(collection, value, middle + 1, end);
            } else if (collection[middle] > value) {
                return search_impl(collection, value, begin, middle - 1);
            } else {
                return static_cast<int>(middle);
            }
        }

        return -1;
    };

    return search_impl(collection, value, 0u, collection.size());
}

int main() {
    std::vector<int> vec = {1, 2, 4, 6, 7, 8, 99, 6, 5, 4, 3, 71, 73};
    std::sort(vec.begin(), vec.end());
    std::cout << "Index: " << binary_search_non_recursive(vec, 57) << std::endl;
    std::cout << "Index: " << binary_search_recursive(vec, 57) << std::endl;
    return EXIT_SUCCESS;
}
