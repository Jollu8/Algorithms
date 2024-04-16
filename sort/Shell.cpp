///// @Jollu
// Shell Sorting


#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, typename Predicate, typename = typename T::iterator>
void Shell_sorting(T &collection, Predicate comparator) noexcept {
    for (typename T::size_type step = collection.size() / 2; step > 0; step /= 2)
        for (typename T::size_type i = 0; i < collection.size(); i++)
            for (typename T::size_type j = i; (j > step - 1) && comparator(collection[j], collection[j - step]); j--)
                std::swap(collection[j], collection[j - step]);
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 0, 6, 5, 4, 3, 2, 73, 41};
    Shell_sorting(vec, [](auto a, auto b) { return a > b; });
    auto print = [](auto i) { std::cout << i << ","; };
    std::for_each(vec.begin(), vec.end(), print);
}