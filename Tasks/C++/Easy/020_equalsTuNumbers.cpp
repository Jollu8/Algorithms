//
// Created by jollu on 12/18/21.
//

//Easy: Задание №1
//Напишите программу, которая сравнивает два введенных с клавиатуры числа. Программа должна указать, какое число меньше, или, если числа равны — вывести соответствующее сообщение.
//
//Пример результата выполнения программы:
//
//Введите 2 целых числа: 48 54
//48 меньше 54

#include <iostream>


int main() {
    int a;
    int b;
    std::cout << "Enter to number: \n";
    std::cin >> a >> b;
    if (a == b) {
        std::cout << a << " is equal " << b << std::endl;
    } else if (a > b) {
        std::cout << a << " Less than " << b << std::endl;
    } else {
        std::cout << a << " Small than " << b << std::endl;
    }

}
