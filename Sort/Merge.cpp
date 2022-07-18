////@jollu

// Insert Sorting

#include <iostream>
#include <vector>


template<typename Collection, typename Predicate, typename = typename Collection::iterator>
void merge_sorting(Collection &collection, size_t begin, size_t end, Predicate predicate) noexcept {
    if (end - begin < 2)return;

    const size_t middle = (begin + end) / 2;
    merge_sorting(collection, begin, middle, predicate);
    merge_sorting(collection, middle, end, predicate);

    Collection buffer{};
    buffer.reserve(end - begin);
    size_t left = begin;
    size_t right = middle;

    while ((left < middle) && (right < end)) {
        if (predicate(collection.at(left), collection.at(right))) {
            buffer.push_back(collection.at(left));
            left++;
        } else {
            buffer.push_back(collection.at(right));
            right++;
        }
    }
    while (left < middle) {
        buffer.push_back(collection.at(left));
        left++;
    }
    while (right < end) {
        buffer.push_back(collection.at(right));
        right++;
    }
    std::copy(buffer.begin(), buffer.end(), collection.begin() + begin);
}


int main() {
    std::vector<unsigned int> vec = {1, 2, 5, 3, 4, 6, 8, 6, 5, 3, 3, 2, 5, 7,};
    merge_sorting(vec, 0, vec.size(), [](auto a, auto b) {
        return a > b;
    });

    for (auto &i: vec) {
        std::cout << i << " ";
    }
}