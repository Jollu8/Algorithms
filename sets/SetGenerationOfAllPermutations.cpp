///// @Jollu
// Generation Of All Permutations From Set

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <ranges>
#include <algorithm>

void
gen_permutations(const std::vector<int> &sourceSet, std::vector<int> &permutations, std::vector<bool> boolElements) {
    if (sourceSet.size() == permutations.size()) {
        std::ranges::copy(permutations, std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
        return;
    } else {
        for (auto i = 0; i < sourceSet.size(); i++) {
            boolElements.at(i) = true;
            permutations.push_back(sourceSet.at(i));
            gen_permutations(sourceSet, permutations, boolElements);
            boolElements.at(i) = false;
            permutations.pop_back();
        }
    }
}

int main() {
    std::vector<int> permutations{};
    std::vector<int> source_set = {10, 20, 30};
    std::vector<bool> chosen_elements(source_set.size());
    gen_permutations(source_set, permutations, chosen_elements);
}