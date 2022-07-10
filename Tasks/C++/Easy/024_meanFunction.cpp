//значения функции
//
//по формуле решать y = ax^2 + bx + c


#include <iostream>
#include <cassert>


auto coordinate(int a, int x, int b, int c) {
    return ((a * (x * x)) + (b * x) + c);
}

void tester() {
    assert(coordinate(-8, -5, -2, 7) == -183);
    assert(coordinate(8, 2, 9, -10) == 40);
    std::cout << "OK" << std::endl;

}

int main() {
    tester();
}