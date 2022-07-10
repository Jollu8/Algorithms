//
// Created by jollu on 12/17/21.
//

//Hard: Задание №3
//Напишите программу, реализующую игру «Угадай число». Компьютер загадывает число от 0 до 999 (используйте генерацию случайных чисел), а пользователь угадывает его. На каждом шаге угадывающий делает предположение, а задумавший число — сообщает, сколько цифр из числа угаданы и сколько из угаданных цифр занимают правильные позиции в числе. Например, если задумано число 725 и выдвинуто предположение, что задумано число 523, то угаданы две цифры (5 и 2), и одна из них занимает верную позицию. Например:
//
//Компьютер загадал трехзначное число. Вы должны его отгадать. После очередного числа вам будет сообщено, сколько цифр угадано и сколько из них находится на своих местах.
//Ваш вариант: 123
//Угадано: 0. На своих местах: 0
//Ваш вариант: 456
//Угадано: 1. На своих местах: 0
//Ваш вариант: 654
//Угадано: 2. На своих местах: 2
//Ваш вариант: 657
//Угадано:  2. На своих местах: 2
//Ваш вариант: 658
//Угадано: 3. На своих местах: 3
//***Вы угадали число 658!***

#include <iostream>
#include <string>
#include <stdlib.h>


//    считает совпадение и сколько из них на месте если два строка одинаковые сразу возвращает count
int count(std::string str1, std::string str2, int &mean, bool &b) {
    if (str1 == str2) {
        b = false;
        mean = 3;
        return 3;
    }
    int count = 0;
    for (int i = 0; i < str1.size(); i++) {
        if (str1[i] == str2[i]) {
            count++;
        }
    }
//
    for (int i = 0; i < str1.size(); i++) {
        for (int j = 0; j < str1.size(); j++) {
            if (str1[i] == str2[j]) {
                mean++;
            }
        }
    }
    return count;
}

// проеверяет в наличии is digit
bool correctDigit(std::string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


int main() {
    int r = std::rand() % 99;
    int mean = 0;
    std::string rand = std::to_string(r);
    std::string str;
    std::cout << "Entre guess digit from 0 to 999\n>";

    bool b = true;
    while (b && std::cin >> str) {
        if (correctDigit(str)) {
            int count1 = count(rand, str, mean, b);
            std::cout << "Guessed " << mean << ". In place: " << count1 << std::endl;
        } else {
            std::cout << "Enter correct digits: \n";
        }
        if (b) {
            std::cout << "Entre guess digit from 0 to 999\n>";

        }
    }
}

