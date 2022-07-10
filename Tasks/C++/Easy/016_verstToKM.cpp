//
// Created by jollu on 12/18/21.
//

#include <iostream>
#include <iostream>

//Easy: Задание №1
//Напишите программу пересчета расстояния из верст в километры (1 верста = 1.0668 км).
//
//Пример результата выполнения программы:
//
//Введите расстояние в верстах: 100
//100 верст = 106.68 км


double resulVerse(int i) {
    return (double) i * 1.0668;
}

int main() {
    int n;
    std::cout << "Enter distance in verse: \n>";
    std::cin >> n;
    while (n <= 0) {
        std::cout << "Error. try again: \n>";
        std::cin >> n;
    }
    double res = resulVerse(n);
    std::cout << n << " verse = " << res << " km\n";
}
