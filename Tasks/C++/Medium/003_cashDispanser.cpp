#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {
    int nominal[] = { 100, 200, 500, 1000, 2000, 5000 };
    std::ifstream bank(".\\bank.bin", std::ios::binary);
    if (!bank.is_open()) {
        std::ofstream bank(".\\bank.bin", std::ios::binary);
    }
    int mas[1000];
    int miracle[1000];
    bank.read((char*)mas, sizeof(mas));
    for (int i = 0; i < 1000; ++i) miracle[i] = mas[i];
    bank.close();
    std::cout << "Welcome to the bank!\nWhat operation do you want to perform? ";
    char operation;
    std::cin >> operation;
    if (operation != '+' && operation != '-') {
        std::cerr << "Error data!\n";
        return 2;
    }
    if (operation == '+') {
        for (int i = 0; i < 1000; ++i) {
            mas[i] = nominal[std::rand() % 6];
        }
    }
    else {
        std::cout << "How much do you want to withdraw money? ";
        int number;
        std::cin >> number;
        if (number % 100 != 0) {
            std::cerr << "Error data: " << number << std::endl;
            return 3;
        }
        bool find = false;
        for (int i = 0; i < 6 && !find; ++i) {
            int balance = number;
            for (int j = 5 - i; j >= 0; --j) {
                if (nominal[j] > balance) continue;
                for (int k = 0; k < 1000; ++k) {
                    if (mas[k] == nominal[j]) {
                        if (mas[k] <= balance) {
                            balance -= mas[k];
                            mas[k] = 0;
                        }
                    }
                }
                if (balance == 0) {
                    find = true;
                    std::cout << "You have withdrawn " << number << std::endl;
                    break;
                }
            }
            for (int j = 0; j < 1000; ++j) mas[j] = miracle[j];
        }
        if (!find) {
            std::cout << "Operation is not possible!";
            return 4;
        }
    }
    std::ofstream out("bank.bin", std::ios::binary);
    out.write((char*)mas, sizeof(mas));
    out.close();
    return 0;
}