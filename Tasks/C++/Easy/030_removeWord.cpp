#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <vector>


std::string find_remove(std::string word, std::string text) {
    for (auto i: word) {
        std::string::size_type n = text.find(i);
        if (n != text.npos) {
            text.erase(text.begin() + n);
        }
    }
    return text;
}


void tester() {
    assert(find_remove("hello world", "hello worldr") == "r");
    assert(find_remove("go", "ogg") == "g");
    assert(find_remove("hello", "hello") == "");
//    assert(find_remove("", "") == "");
    std::cout << "OK";

}


int main() {
    tester();

}