#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

bool palindrome(const std::string  &text, std::string  palind) {
    std::reverse(palind.begin(), palind.end());
    return text == palind;
}




void tester() {
    assert(palindrome("text", "txet") == true);
    assert(palindrome("palan",  "nalap") == true);
    assert(palindrome("assert", "assert") == false);
    std::cout << "OK";
}

int main() {
    tester();

}