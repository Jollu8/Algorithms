///// @Jollu
// Euclidean Algorithm


//#include <string>
//#include <vector>
//#include <sstream>
#include <iostream>

size_t greatest_common_divisor(size_t lhs, size_t rhs) {
    if (lhs == rhs) return lhs;
    else if (lhs < rhs) return greatest_common_divisor(lhs, rhs - lhs);
    else return greatest_common_divisor(lhs - rhs, rhs);
}


int main() {
    std::cout << greatest_common_divisor(48, 12) << std::endl;
}