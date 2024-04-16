///// @Jollu
// Maximum Amount OfSub Arrays


//#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

template<typename Collection, typename = typename Collection::iterator>
typename Collection::value_type find_max_sub_arrays_amount(Collection &collection) noexcept {
    static_assert(!std::is_unsigned<typename Collection::value_type>::value,
                  "Current implementation works only with signed types.");

    typename Collection::value_type current_amount = 0;
    typename Collection::value_type max_amount = std::numeric_limits<typename Collection::value_type>::min();
    for (typename Collection::size_type i = 0; i < collection.size(); i++) {
        current_amount = std::max(collection.at(i), current_amount + collection.at(i));
        max_amount = std::max(max_amount, current_amount);
    }

    return max_amount;
}


int main() {
    const std::vector<int> vec = {-1, 2, 4, -3, 5, 2, -5, 2};
    const int max_amount = find_max_sub_arrays_amount(vec);
    std::cout << "Max amount of sub arrays: " << max_amount << std::endl;
}