///// @Jollu
// Generation Of All Subsets Of The Set

#include <iostream>
#include <ranges>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

using v_int = std::vector<int>;

void gen_subsets(const v_int &sourceSet, v_int &subset, size_t pos) {
    if (pos == sourceSet.size()) {
        std::ranges::copy(subset, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return;
    } else {
        subset.push_back(sourceSet.at(pos));
        gen_subsets(sourceSet, subset, pos + 1);
        subset.pop_back();
        gen_subsets(sourceSet, subset, pos + 1);
    }
}

int main() {
    std::vector<int> subset{};
    std::vector<int> source_set = {1, 2, 3};
    gen_subsets(source_set, subset, 0);
}

