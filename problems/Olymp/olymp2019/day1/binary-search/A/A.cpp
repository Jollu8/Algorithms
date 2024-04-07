#include <iostream>
#include <vector>
#include <algorithm>
#include <valarray>
#include <iomanip>
#include <cmath>


using ld = long double;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long double C;
    std::cin >> C;

    ld p = 1.;
    ld q = 1e10;
    const ld e = 1e-9;

    while (q - p > e) {
        ld x = (p + q) / 2.;
        if (x * x + std::sqrt(x) - C > 0) q = x;
        else p = x;
    }

    std::cout << std::fixed << std::setprecision(5) << (p + q) / 2.;
}
