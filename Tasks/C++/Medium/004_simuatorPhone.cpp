//
// Created by zholu on 03.11.2021.
//

#include <iostream>
#include <string>
#include <vector>


class AddressBook {
public:
    std::string name;
    std::string number;
};

class Mobile {
public:
    void add();

    void call();

    void sms();

};

std::vector<class AddressBook> list;

void Mobile::add() {
    AddressBook newContact;
    std::string buffer;
    std::cout << "Please Enter a name of Person" << std::endl;
    std::cin >> newContact.name;
    std::cout << "Please enter a number of person with +7 (10 additional digits)" << std::endl;
    std::cin >> buffer;
    while (buffer.size() != 12 && buffer[0] != '+' && buffer[1] != '7') {
        std::cout << "Incorrect input" << std::endl;
        std::cout << "Please enter again" << std::endl;
        std::cin >> buffer;
    }
    newContact.number = buffer;
    list.push_back(newContact);
};

void Mobile::call() {
    std::string buffer;
    std::cout << "Whom you want to call?" << std::endl;
    std::cin >> buffer;
    for (int i = 0; i < list.size(); i++) {
        if (buffer == list[i].name) {
            std::cout << "We're calling to " << list[i].name << " by number" << list[i].number << std::endl;
        } else if (buffer == list[i].number) {
            std::cout << "We're calling to " << list[i].name << " by number" << list[i].number << std::endl;
        } else std::cout << "There is no such kind of person" << std::endl;
    }
};

void Mobile::sms() {
    std::string buffer;
    std::string message;
    std::cout << "Please enter a message" << std::endl;
    std::cin >> std::ws;
    std::getline(std::cin, message);
    std::cout << "Whom you want to send it?" << std::endl;
    std::cin >> buffer;
    for (int i = 0; i < list.size(); i++) {
        if (buffer == list[i].name) {
            std::cout << "SMS " << message << " were sent to " << list[i].name << " by number" << list[i].number
                      << std::endl;
        } else if (buffer == list[i].number) {
            std::cout << "SMS " << message << " were sent to " << list[i].name << " by number" << list[i].number
                      << std::endl;
        } else std::cout << "There is no such kind of person" << std::endl;
    }
}


int main() {
    Mobile myMobile;
    int command = 100;
    while (command != 3) {
        std::cout << "Please choose a command" << std::endl;
        std::cout << "0. add a Person" << std::endl;
        std::cout << "1. call" << std::endl;
        std::cout << "2.SMS" << std::endl;
        std::cout << "3.exit" << std::endl;
        std::cin >> command;
        switch (command) {
            case 0:
                myMobile.add();
                break;
            case 1:
                myMobile.call();
                break;
            case 2:
                myMobile.sms();
                break;
            case 3:
                break;
            default:
                std::cout << "! Incorrect command. Try again !";
                break;
        }
    }
}