#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>


bool fourth(int n) {

    if (n % 4 != 0) return false;
    while (n > 0) {
        n = n / 4;
    }
    return n == 0;
}


void tester() {
    assert(fourth(16) == true);
    assert(fourth(15) == false);
    assert(fourth(64) == true);
    assert(fourth(256) == true);
    assert(fourth(245) == false);
    std::cout << "OK";
}

int main() {
    tester();

}