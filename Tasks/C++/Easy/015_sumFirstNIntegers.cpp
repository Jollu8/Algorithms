//
// Created by jollu on 12/17/21.

//Medium: Задание №2
//
//Напишите программу, которая вычисляет сумму первых n целых положительных четных чисел.
//Количество
//        суммируемых чисел вводит пользователь.
//
//Пример результата выполнения программы:
//
//Введите количество суммируемых чисел: 12
//Сума первых 12 целых положительных четных чисел равна 156
//

#include <iostream>

void total(const int &n, int &n1) {
    n1 += n;
}

int main() {
    int n;
    int n1 = 0;
    bool b = true;
    std::cout << "Enter number: \n>";
    while (b && std::cin >> n) {
        if (n > 0) {
            total(n, n1);
            std::cout << "Enter number: or exit -1\n>";
        } else if (n == -1) {
            b = false;
        } else {
            std::cout << "Error! try again\n";
            std::cout << "Enter number: or for exit -1\n>";
        }
    }
    std::cout << "Total: " << n1 << std::endl;
}

