///// @Jollu
// Fibonacci


#include <iostream>
#include <vector>

size_t fibonacci_non_recursive(size_t n) {
    std::vector<size_t> numbers(n, 0u);
    numbers.at(0) = 1u;
    numbers.at(1) = 1u;

    for (size_t i = 2u; i < numbers.size(); ++i) {
        numbers.at(i) = numbers.at(i - 1u) + numbers.at(i - 2u);
    }
    return numbers.back();
}

size_t fibonacci_sub_function(std::vector<size_t> &ns, size_t n) {
    if (ns.at(n) != 0u) return ns.at(n);
    else if (n == 0) return 0u;
    else if (n == 1) return 1u;
    else
        return ns.at(n) = fibonacci_sub_function(ns, n - 1) + \
    fibonacci_sub_function(ns, n - 2);
}

size_t fibonacci_recursive(size_t n) {
    std::vector<size_t> ns(n + 1, 0u);
    return fibonacci_sub_function(ns, n);
}

int main() {

    std::cout << fibonacci_recursive(50000u) << std::endl;
    std::cout << fibonacci_non_recursive(50000u) << std::endl;
}
