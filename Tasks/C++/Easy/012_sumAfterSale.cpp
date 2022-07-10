//
// Created by jollu on 12/17/21.
//
#include <iostream>
#include <vector>
//
//Medium: Задание №2
//
//Напишите программу вычисления стоимости покупки с учетом скидки. Скидка в 3% предоставляется, если сумма покупки больше 500 руб., в 5% — если сумма покупки больше 1000 руб.
//
//Пример результата выполнения программы:
//
//Введите сумму покупки: 640
//Вам предоставляется скидка в 3%
//Сумма с учетом скидки: 620.80 руб.


double percent(double n, int &sale) {
    int n1 = n;
    if (n > 0 && n <= 500) {
        return n;
    } else if (n > 500 && n <= 1000) {
        sale = 3;
        return n1 - ((n / 100) * sale);
    } else {
        sale = 5;
        return n1 - ((n / 100) * sale);
    }
}

int main() {
    int sale = 0;
    double price;
    std::cout << "Enter price sum: ";
    std::cin >> price;
    double income = percent(price, sale);
    std::cout << "You are given a discount in " << sale << "%" << std::endl;
    std::cout << "Discount amount: " << income << " rub." << std::endl;
}


