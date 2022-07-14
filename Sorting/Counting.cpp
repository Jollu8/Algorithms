////@jollu

// Counting Sorting

#include <iostream>
#include <vector>


template<typename Collection, typename = typename Collection::iterator>
void counting_sorting(Collection &collection) noexcept {
    static_assert(std::is_unsigned<typename Collection::value_type>::value,
                  "Only unsigned int");
    typename Collection::value_type max_value = *std::max_element(collection.begin(), collection.end());
    Collection counted_collection(max_value + 1);

    for (typename Collection::size_type i = 0; i < collection.size(); i++)
        counted_collection.at(collection.at(i))++;

    collection.clear();
    for (typename Collection::size_type i = 0; i < counted_collection.size(); i++)
        for (typename Collection::size_type j = 0; j < counted_collection.at(i); j++)
            collection.push_back(i);
}


int main() {
    std::vector<unsigned int> vec = {1, 2, 5, 3, 4, 6, 8, 6, 5, 3, 3, 2, 5, 7,};
    counting_sorting(vec);

    for (auto &i: vec) {
        std::cout << i << " ";
    }
}
