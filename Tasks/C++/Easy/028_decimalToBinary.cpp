#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>


std::string binary(int n) {
    std::string str;
    while (n > 0) {
        int i = n % 2;
        n = n / 2;
        str += std::to_string(i);
    }
    std::reverse(str.begin(), str.end());
    return str;
}


void tester() {
    assert(binary(14) == "1110");
    assert(binary(127) == "1111111");
    assert(binary(5) == "101");
    assert(binary(88) == "1011000");
    std::cout << "OK";
}

int main() {
    tester();

}