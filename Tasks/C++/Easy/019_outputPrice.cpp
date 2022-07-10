//
// Created by jollu on 12/18/21.
//


//Medium: Задание №2
//
//Напишите программу, которая выводит на экран таблицу стоимости,
//например, яблок в диапазоне от 100 г до 1 кг с шагом 100 г.
//
//Пример результата выполнения программы:
//
//Введите цену 1 кг яблок: 16.50
//Вес    Стоимость
//        (г)     (руб.)
//100      1.65
//200      3.30
//300      4.95
//400      6.60
//500      8.25
//600      9.90
//700      11.55
//800      13.20
//900      14.85
//1000     16.50

#include <iostream>
#include <iomanip>


void task2() {
    double priceApple;
    int kg = 100;
    std::cout << "Enter price for 1kg apples: \n>";
    std::cin >> priceApple;
    while (priceApple <= 0) {
        std::cout << "Enter price for 1kg apples: \n>";
        std::cin >> priceApple;
    }
    priceApple = (priceApple / 100) * 10;
    double percent = priceApple;
    std::cout << "g\t\t  " << std::setw(10) << std::left
              << std::setw(5) << "(rub.)" << std::left << std::endl;
    while (kg < 1001) {
        std::cout << std::setw(10) << kg << std::left
                  << std::setw(5) << priceApple << std::left << std::endl;
        kg += 100;
        priceApple += percent;
    }


}
