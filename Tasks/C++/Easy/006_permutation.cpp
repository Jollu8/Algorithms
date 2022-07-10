#include  <vector>
#include  <string>
#include <iostream>
#include <algorithm>


std::vector<std::string> permutations(std::string s) {
    std::vector<std::string>vec;
    do {
        vec.push_back(s);
    } while (std::next_permutation(s.begin(), s.end()));

    return vec;
}

int main() {

    std::string str = "aabb";
    std::vector<std::string> vec;

    vec = permutations(str);
    for (auto i : vec) {
        std::cout << i << " ";
    }

}