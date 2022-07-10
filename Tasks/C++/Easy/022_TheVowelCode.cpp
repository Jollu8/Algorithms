#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <map>

const std::map<char, char> code{
        {'a', '1'},
        {'e', '2'},
        {'i', '3'},
        {'o', '4'},
        {'u', '5'}
};

std::string encode(const std::string &str) {
    std::string s;
    for (auto i: str) {
        if (i == code.find(i)->first) {
            s += code.find(i)->second;
        } else {
            s += i;
        }
    }
    return s;
}

std::string decode(const std::string &str) {
    std::string s;
    for (auto i: str) {
        for(auto it : code) {
            if(i == it.second) {
                s += it.first;
            }
        }
        if(i < '1' || i > '4') {
            s+= i;
        }
    }
    return s;
}



int main() {
    std::cout << encode("hello world") << std::endl;
    std::cout << decode("h2ll4 w4rld") << std::endl;

}