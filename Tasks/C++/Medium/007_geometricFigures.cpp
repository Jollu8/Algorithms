

//
// Created by zholu on 04/11/2021.
//

#include <iostream>

#include <string>

class Core {
public:
    std::string color = "Unknown";

    void colorChoose();
};


class Circle : public Core {
public:
    float radius = 0;

    explicit Circle(float m);

    void circleSize();

    void squareOutside() const;
};


class Display {
public:
    static void squareCreation();

    static void circleCreation();

    static void triangleCreation();

    static void rectangleCreation();

};


class Rectangle : public Core {
    float shortDistance = 0;
    float longDistance = 0;
public:
    Rectangle(float m, float n);

    void rectangleSize();

    void squareOutside() const;
};

class Square : public Core {
public:
    float distanceToEdge = 0;

    explicit Square(float m);

    void squareSize();

    static void squareOutside();
};

class Triangle : public Core {
public:
    float distanceToApex;

    explicit Triangle(float m);

    void triangleSize();

    void squareOutside() const;
};

Circle::Circle(float m) : radius(m) {

}

void Circle::circleSize() {
    colorChoose();
    std::cout << "Circle size is " << 3.14f * radius * radius << std::endl;
}

void Circle::squareOutside() const {
    std::cout << "Square outside has following size of edge: " << 2 * radius << std::endl;
}


void Core::colorChoose() {
    std::cout << "Please choose color of shape:" << std::endl;
    std::cout << "1. red" << std::endl;
    std::cout << "2. blue" << std::endl;
    std::cout << "3. green" << std::endl;
    int choose = 0;
    std::cin >> choose;
    switch (choose) {
        case (1):
            color = "red";
            break;
        case (2):
            color = "blue";
            break;
        case (3):
            color = "green";
            break;
    }
}

void Display::squareCreation() {
    float m;
    std::cout << "Please enter distance to edge: " << std::endl;
    std::cin >> m;
    Square mySquare(m);
    mySquare.squareSize();
    Square::squareOutside();
}

void Display::circleCreation() {
    float m;
    std::cout << "Please enter a radius: " << std::endl;
    std::cin >> m;
    Circle myCircle(m);
    myCircle.circleSize();
    myCircle.squareOutside();
}

void Display::triangleCreation() {
    float m;
    std::cout << "Please enter a distance from center to Apex: " << std::endl;
    std::cin >> m;
    Triangle myTriangle(m);
    myTriangle.triangleSize();
    myTriangle.squareOutside();
}

void Display::rectangleCreation() {
    float m, n;
    std::cout << "Please enter a short and long edges" << std::endl;
    std::cin >> m >> n;
    Rectangle myRectangle(m, n);
    myRectangle.rectangleSize();
    myRectangle.squareOutside();
}


Rectangle::Rectangle(float m, float n) : shortDistance(m), longDistance(n) {

}

void Rectangle::rectangleSize() {
    colorChoose();
    std::cout << "rectangle square is " << 4 * shortDistance * longDistance << std::endl;
}

void Rectangle::squareOutside() const {
    std::cout << "Square outside has following size of edge: " << longDistance << std::endl;
}

Square::Square(float m) : distanceToEdge(m) {

}

void Square::squareSize() {
    colorChoose();
    std::cout << "Square size is " << (2 * distanceToEdge) * (2 * distanceToEdge) << std::endl;
}

void Square::squareOutside() {
    std::cout << "It's equal" << std::endl;
}

Triangle::Triangle(float m) : distanceToApex(m) {

}

void Triangle::triangleSize() {
    colorChoose();

    std::cout << "Triangle square is " << 0.433f * (2 * 0.86f * distanceToApex) * (2 * 0.86f * distanceToApex)
              << std::endl;
}

void Triangle::squareOutside() const {
    std::cout << "Square outside has following size of edge: " << 0.86f * 2 * 0.86f * distanceToApex << std::endl;
}


int main() {
    int buffer = 0;
    while (buffer != 5) {
        std::cout << "Please choose what shape we will create" << std::endl;
        std::cout << "1. circle" << std::endl;
        std::cout << "2. square" << std::endl;
        std::cout << "3.triangle" << std::endl;
        std::cout << "4. rectangle" << std::endl;
        std::cout << "5. exit" << std::endl;
        std::cin >> buffer;
        switch (buffer) {
            case (1):
                Display::circleCreation();
                break;
            case (2):
                Display::squareCreation();
                break;
            case (3):
                Display::triangleCreation();
                break;
            case (4):
                Display::rectangleCreation();
                break;
            case (5):
                break;
            default:
                std::cout << "Incorrect command!!! Try again" << std::endl;
                break;
        }
    }
}