//
// Created by jollu on 12/18/21.
//
//Medium: Задание №2
//
//Напишите программу, которая вычисляет среднее арифметическое последовательности дробных чисел, вводимых с клавиатуры. После ввода пользователем последнего числа программа должна вывести минимальное и максимальное числа из последовательности. Количество чисел последовательности вводит пользователь.
//
//Пример результата выполнения программы:
//
//Введите количество чисел последовательности: 5
//Введите последовательность: 5.4 7.8 3.0 1.5 2.3
//Среднее арифметическое: 4.00
//Минимальное число: 1.5
//Максимальное число: 7.8

#include <iostream>
#include <vector>


struct Result {
    double midle;
    double low;
    double high;
};


Result result(std::vector<double> v) {
    Result res;
    res.low = v[0];
    res.high = 0;
    res.midle = 0;
    for (int i = 0; i < v.size(); i++) {
        res.midle += v[i];
        if (res.low > v[i]) {
            res.low = v[i];
        } else if (res.high < v[i]) {
            res.high = v[i];
        }
    }
    res.midle = res.midle / v.size();
    return res;
}

void task2() {
    int n;
    int count = 0;
    double number;
    std::vector<double> vec;
    std::cout << "Enter count float digits: \n>";
    std::cin >> n;
    while (count < n) {
        count++;
        std::cout << "Enter Float number: \n>";
        std::cin >> number;
        vec.push_back(number);
    }
    Result res;
    res = result(vec);
    std::cout << "Midle Arithmetic: " << res.midle << '\n';
    std::cout << "Minimum number: " << res.low << '\n';
    std::cout << "Maximum number: " << res.high << std::endl;
}



