
//
// Created by zholu on 03/11/2021.
//
#include <iostream>


class MyMonitor {
public:
    int x;
    int y;
    int width;
    int height;

    void move();

    void resize();

    void display();
};


//  func move monitor  ====================================
void MyMonitor::move() {
    int newX, newY;
    std::cout << "Please enter new beginning:" << std::endl;
    std::cin >> newX >> newY;
    while ((newX + width) > 80 && ((newY + height) > 50)) {
        std::cout << "Incorrect input, please try again" << std::endl;
        std::cin >> newX >> newY;
    }
    x = newX;
    y = newY;
}

//  func resize display ===================================
void MyMonitor::resize() {
    int newWidth, newHeight;
    std::cout << "Please enter new width and new height of the window" << std::endl;
    std::cin >> newWidth >> newHeight;
    while ((x + newWidth) > 80 && (y + newHeight) > 50) {
        std::cout << "Incorrect input, please try again" << std::endl;
        std::cin >> newWidth >> newHeight;
    }
}

//  func display ============================================
void MyMonitor::display() {
    for (int i = 0; i <= 50; i++) {
        for (int j = 0; j <= 80; j++) {
            if (i >= y && i <= (y + height) && j >= x && j <= (x + width)) std::cout << "1";
            else std::cout << "0";
        }
        std::cout << std::endl;
    }
}


int main() {
    MyMonitor Monitor;
    std::cout << "Please enter initial parameters of Window" << std::endl;
    std::cin >> Monitor.x >> Monitor.y >> Monitor.width >> Monitor.height;
    while ((Monitor.x + Monitor.width) > 80 && (Monitor.y + Monitor.height) > 50) {
        std::cout << "Incorrect entry, please try again" << std::endl;
        std::cin >> Monitor.x >> Monitor.y >> Monitor.width >> Monitor.height;
    }
    int answer;

    while (answer != 3) {
        std::cout << "Please choose a command" << std::endl;
        std::cout << "0. move Window" << std::endl;
        std::cout << "1. resize Window" << std::endl;
        std::cout << "2.display Window" << std::endl;
        std::cout << "3.exit" << std::endl;
        std::cin >> answer;
        switch (answer) {
            case 0:
                Monitor.move();
                break;
            case 1:
                Monitor.resize();
                break;
            case 2:
                Monitor.display();
                break;
            case 3:
                break;
            default:
                std::cout << "! Incorrect command. Try again !";
                break;
        }
    }
}