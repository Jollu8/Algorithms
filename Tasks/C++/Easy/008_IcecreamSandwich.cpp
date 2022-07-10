//
// Created by jollu on 12/17/21.
//
//
//Задание №1
//Сэндвич с мороженым — это строка, образованная двумя одинаковыми концами и разной серединой. Например:
//
//AABBBAA
//3&&3
//yyyyymmmmmmmmyyyyy
//        hhhhhhhhmhhhhhhhh
//
//Обратите внимание, что левый и правый концы сэндвича идентичны как по длине, так и по повторяющимся символам. Середину составляет третий (отличный от первых двух) набор символов.
//
//Следующее не является сэндвичем с мороженным:
//
//BBBBB // вы не можете иметь только мороженное (без сэндвича)
//AAACCCAA // вы не можете иметь неравные по длине окончания в сэндвиче
//AACDCAA // вы не можете иметь начинку из разных символов
//A // ваш сэндвич не может быть менее трех символов
//
//Напишите программу, которая возвращает true, если строка, введенная пользователем, является сэндвичем с мороженым, и false — в противном случае.
//
//Примеры:
//
//isIcecreamSandwich ("CDC") ➞ true
//isIcecreamSandwich ("AAABB") ➞ false
//isIcecreamSandwich ("AA") ➞ false
//
//Примечание: Сэндвич с мороженым должен иметь минимальную длину 3 символа, и как минимум 2 из этих символов должны быть различны.


#include <string>
#include <iostream>

bool isIcecreamSandwich(std::string_view str) {
    int buf = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == str[str.length() - 1 - i]) {
            if (str[i] != str[i + 1]) {
                ++buf;
            }
        }
    }
    std::cout << buf << "\n";
    if (buf == 3) {
        return true;
    }
    return false;
}

int main() {
    std::string str;
    std::cout << "Enter Sandwich string: \n>";
    std::cin >> str;
    std::string_view str1{str};
    std::cout << std::boolalpha << isIcecreamSandwich(str1) << std::endl;
}

