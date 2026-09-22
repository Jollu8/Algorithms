///// @Jollu
// EratosthenesSieve


#include <string>
#include <vector>
#include <sstream>
#include <iostream>


std::vector<int> generate_prime_numbers(int max_number) {
    if (max_number <= 1) return {};

    std::vector<int> result;
    std::vector<bool> sieve(max_number + 1, true);
    for (auto i = 2; i <= max_number; ++i) {
        for (auto j = i * i; j <= max_number; j += i) {
            sieve[j] = false;
        }
    }

    for (auto i = 2u; i < sieve.size(); ++i) {
        if (sieve[i])result.push_back(i);
    }
    return result;
}

int main() {
    auto prime_numbers = generate_prime_numbers(40);
    for (auto number: prime_numbers) {
        std::cout << number << " ";
    }
}