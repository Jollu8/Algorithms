// Split Strings
// Complete the solution so that it splits the string into pairs of two characters. If the string contains an odd number of characters then it should replace the missing second character of the final pair with an underscore ('_').

// Examples:

// solution("abc") // should return {"ab", "c_"}
// solution("abcdef") // should return {"ab", "cd", "ef"}


#include  <iostream>
#include <string>
#include <vector>

#include <string>
#include <vector>

std::vector<std::string> solution(const std::string &str)
{
    std::vector<std::string> vec;
    if (str.empty()) {
        return vec;
    } else {
        std::string s;
        for(int i = 0; i <  str.size(); i++ ) {
            if((str.begin() + i + 1) == str.end()) {
                s = str[i];
                s += "_";
                vec.push_back(s);
                return vec;
            } else {
                s = str[i];
                s += str[i + 1];
                vec.push_back(s);
                i++;
            }
        }
        return vec;
    }
}


int main() {
    std::string str = "HelloWorld2";
    auto v = solution(str);
    for(auto i : v) {
        std::cout << i << " ";
    }
}
