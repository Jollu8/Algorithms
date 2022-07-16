///// @Jollu
// Stupid Sorting


#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, typename Predicate, typename = typename T::iterator>
void Shell_sorting(T &collection, Predicate comparator) noexcept {
    for (int i = 0; i < static_cast<int>(collection.size() - 1); ++i)
    {
        if (comparator(collection[i], collection[i + 1]))
        {
            std::swap(collection[i], collection[i + 1]);
            i = -1;
        }
    }
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 0, 6, 5, 4, 3, 2, 73, 41};
    Shell_sorting(vec, [](auto a, auto b) { return a > b; });
    auto print = [](auto i) { std::cout << i << ","; };
    std::for_each(vec.begin(), vec.end(), print);
}