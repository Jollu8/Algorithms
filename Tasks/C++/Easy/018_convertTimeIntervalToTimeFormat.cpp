//
// Created by jollu on 12/18/21.
//

//Easy: Задание №1
//Напишите программу пересчета величины временного интервала, заданного в минутах, в величину, выраженную в часах и минутах.
//
//Пример результата выполнения программы:
//
//Введите временной интервал (в минутах): 150
//150 минут = 2 ч. 30 мин.


#include <iostream>
#include <vector>
#include <algorithm>

struct Hour {
    int hour;
    int minut;
};

Hour totalHour(int n) {
    Hour H;
    H.hour = 0;

    while (n > 59) {
        H.hour++;
        n -= 60;
    }
    H.minut = n;
    return H;
}

int main() {
    int n;
    std::cout << "Enter time interval in minutes: \n>";
    std::cin >> n;
    while (n <= 0) {
        std::cout << "Enter time interval in minutes: \n>";
        std::cin >> n;
    }
    Hour H;
    H = totalHour(n);
    std::cout << n << " minutes = " << H.hour << " h. " << H.minut << " min. " << std::endl;
}

