//
// Created by jollu on 12/17/21.
//

//Задание №2
//
//Напишите программу, которая определяет минимальное число в последовательности положительных чисел, которую ввел пользователь. Если в последовательности есть отрицательные числа,
//то вы должны сообщить об этом пользователю и предложить повторить ввод еще раз.

#include <vector>
#include <iostream>
#include <algorithm>

int sort(std::vector<int> &vec) {
    std::sort(vec.begin(), vec.end());
    return vec[0];
}

int main() {
    std::vector<int> vec{};
    bool b = true;
    int digit;
    std::cout << "Enter digit: \n>";
    while (b && std::cin >> digit) {
        if (digit == -1) {
            b = false;
        } else if (digit < 0) {
            std::cout << "Digit less than zero. Try again\n>";
        } else {
            vec.push_back(digit);
            std::cout << "Enter digit: \n>";
        }
    }
    int lessDigit = sort(vec);
    std::cout << lessDigit << std::endl;

}
