//
// Created by jollu on 12/18/21.
//
//Medium: Задание №2
//
//Напишите программу, которая выводит на экран сообщение в «телеграфном» стиле:
//буквы сообщения должны появляться по одной с некоторой задержкой.

#include <iostream>
#include <string>
#include <thread>
#include <chrono>


int main() {
    std::string text = "";
    int n = 0;
    std::cout << "Enter text: \n>";
    getline(std::cin, text);
    std::cout << "Enter the speed of print text: \n>";
    std::cin >> n;
    for (auto ch: text) {
        std::cout << ch;
        std::this_thread::sleep_for(std::chrono::milliseconds(n));
    }
    std::cout << "Press Enter to exit";
    std::cin.get();
}

