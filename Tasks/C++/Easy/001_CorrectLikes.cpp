// You probably know the "like" system from Facebook and other pages. People can "like" blog posts, pictures or other items. We want to create the text that should be displayed next to such an item.

// Implement the function which takes an array containing the names of people that like an item. It must return the display text as shown in the examples:

// []                                -->  "no one likes this"
// ["Peter"]                         -->  "Peter likes this"
// ["Jacob", "Alex"]                 -->  "Jacob and Alex like this"
// ["Max", "John", "Mark"]           -->  "Max, John and Mark like this"
// ["Alex", "Jacob", "Mark", "Max"]  -->  "Alex, Jacob and 2 others like this"

// #include <iostream>
// #include <vector>
// #include <string>

std::string likes(const std::vector<std::string> &names) {
    if (names.empty()) return "no one likes this";
    if (names.size() == 1) return names[0] + " likes this";
    if (names.size() == 2) return names[0] + " and " + names[1] + " like this";
    if (names.size() == 3) return names[0] + ", " + names[1] + " and " + names[2] + " like this";
    if (names.size() > 3) {
        int n = names.size() - 2;
        return names[0] + ", " + names[1] + " and " + std::to_string(n) + " others like this";
    }
}

int main() {
    std::vector<std::string> str1{"Peter"};
    std::vector<std::string> str2{"Jacob", "Alex"};
    std::vector<std::string> str3{"Max", "John", "Mark"};
    std::vector<std::string> str4{"Alex", "Jacob", "Mark", "Max"};
    std::vector<std::string>vec;
    std::cout << likes(vec) << std::endl;
    std::cout << likes(str1) << std::endl;
    std::cout << likes(str2) << std::endl;
    std::cout << likes(str3) << std::endl;
    std::cout << likes(str4) << std::endl;
}