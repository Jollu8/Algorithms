///// @Jollu
// Diffie-Hellman Algorithm

#include <cmath>
#include <iostream>


long long int power(long long int a, long long int b,
                    long long int P) {
    if (b == 1)
        return a;

    else
        return (((long long int) pow(a, b)) % P);
}

int main() {
    long long int P, G, x, a, y, b, ka, kb;
    P = 23;
    G = 9;
    a = 4;
    x = power(G, a, P);
    b = 3;
    y = power(G, b, P);
    ka = power(y, a, P);
    kb = power(x, b, P);
    std::cout << ka << std::endl;
    std::cout << kb << std::endl;
}
