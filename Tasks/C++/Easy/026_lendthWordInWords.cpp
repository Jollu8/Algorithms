//max length word in words
//
//
//void tester() {
//    assert(max_word("i love segment tree") == 7);
//    assert(max_word("for jumps from river") == 5);
//    std::cout << "OK";
//}

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

int max_word(const std::string &text) {
    std::stringstream s(text);
    std::string word;
    int n = 0;
    while (s >> word) {
        if (n < word.length()) n = word.length();
    }
    return n;
}

void tester() {
    assert(max_word("i love segment tree") == 7);
    assert(max_word("for jumps from river") == 5);
    std::cout << "OK";
}

int main() {
    tester();

}