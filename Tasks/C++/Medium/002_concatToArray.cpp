//
// Created by jollu on 12/18/21.
//
//Hard: Задание №3
//Напишите программу, которая объединяет два упорядоченных по возрастанию массива в один (тоже упорядоченный) массив.
//
//Пример результата выполнения программы:
//
//Введите элементы первого массива: 1 3 5 7 9
//Введите элементы второго массива: 2 4 6 8 10
//Массив-результат: 1 2 3 4 5 6 7 8 9 10


#include <iostream>
#include <vector>
#include <algorithm>


void unionVec(std::vector<int> &v1, std::vector<int> &v2,
              std::vector<int> &total) {
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(), std::back_inserter(total));
}

int main() {
    std::vector<int> v1{1, 3, 5, 7, 9};
    std::vector<int> v2{2, 4, 6, 8, 10};
    std::vector<int> total;
    unionVec(v1, v2, total);
    std::cout << "Result: ";
    for (auto i: total) {
        std::cout << i << " ";
    }

}
