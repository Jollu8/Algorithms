//
// Created by jollu on 12/17/21.
//

//Hard: Задание №3
//Напишите программу-телеграф, которая принимает от пользователя сообщение и
//выводит его на экран в виде последовательности точек и тире. Вывод точек и тире можно
//        сопровождать звуковым сигналом соответствующей длительности.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


struct Simb {
    char ch;
    std::string simb;
};

std::string encode(const std::vector<Simb> &vec, std::string str) {
    std::string result = "\n";

    for (auto &i: str) {
        if (i == ' ') {
            result.push_back('\n');
        }
        for (auto &iV: vec) {
            if (i == iV.ch) {
                result += iV.simb;
                result.push_back('|');
            }
        }
    }
    return result;
}

int main() {
    std::vector<Simb> vec{
            {'A', "._"},
            {'B', "_..."},
            {'C', "_._."},
            {'D', "_.."},
            {'E', "."},
            {'F', ".._."},
            {'G', "_ _."},
            {'H', "...."},
            {'I', ".."},
            {'J', "._ _ _"},
            {'K', "_._"},
            {'L', "._.."},
            {'M', "_ _"},
            {'N', "_."},
            {'O', "_ _ _"},
            {'P', "._ _."},
            {'Q', "_ _._"},
            {'R', "._."},
            {'S', "..."},
            {'T', "_"},
            {'U', ".._"},
            {'V', "..._"},
            {'W', "._ _"},
            {'X', "_.._"}};

    std::cout << "Enter a text to send Telegraph: \n>";
    std::string str;
    std::getline(std::cin, str);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    std::string result = encode(vec, str);
    std::cout << "This messages send: " << result << std::endl;
}



