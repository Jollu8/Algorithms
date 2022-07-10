
//// for CmakeLists.txt
//cmake_minimum_required(VERSION 3.20.2)
//project(task2)
//
//set(CMAKE_CXX_STANDARD 20)
//set(JSON_BuildTests OFF CACHE INTERNAL "")
//
//add_subdirectory(nlohmann_json)
//
//add_subdirectory(src)
//set(MY_HEADER_DIR ${CMAKE_SOURCE_DIR}/header)
//target_link_libraries(task2 PRIVATE nlohmann_json::nlohmann_json)






#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>


using json = nlohmann::json;

//read json file ===============================================
void showJson(std::string st) {
    std::ifstream file(st);
    json j;
    file >> j;
    file.close();
// чтобы setw работал cxx les 17
    std::cout << std::setw(4) << j << std::endl;
}

void menu() {

    std::cout << "\n\n\nЗадача 2. Анализ данных о фильмах\n";
    std::cout << "If you want to know about task Enter -1\n";
    std::cout << "chose menu:  \n"
              << "1. Show base movies\n"
              << "2. find actor\n";
    std::cout << "For exit enter 9\n>";

}

void readFile(std::string st) {
    char ch;
    std::ifstream file(st);
    while (!file.eof()) {
        file >> std::noskipws >> ch;
        std::cout << ch;
    }
    file.close();
}

using json = nlohmann::json;

//find actor ==================================================
void findActor() {
    std::ifstream file("data.json");
    json j;
    file >> j;
    std::cout << j << std::endl;

    std::string name;
    std::cout << "Name:";
    std::cin >> name;

    for (auto it = j.begin(); it != j.end(); ++it) {
        json movie = it.value();
        json cast = movie["cast"];
        for (auto jt = cast.begin(); jt != cast.end(); ++jt) {
            std::string c_name = to_string(jt.value());
            if (c_name.find(name) != std::string::npos) {
                std::cout << name << " in " << it.key() << " as " << jt.key() << std::endl;
            }
        }
    }


}

namespace f_n {
    struct Actor {
        std::string name;
        std::string fulName;
        std::string live;
        int birth;
        bool gender;
    };
    struct Data_Movie {
        std::string name;
        std::string country;
        std::string director;
        std::string writer;
        double rate;
        int year;
        int time;
        f_n::Actor actor;

    };

    struct Movie {
        std::string name;
        f_n::Data_Movie dataMovie;
    };
}

int main() {
    int kb = 0;
    std::string movies = "movies.json";
    std::string task = "task2.txt";
    menu();
    std::cin >> kb;
    while (kb != 9) {
        switch (kb) {
            case -1:
                readFile(task);
                break;
            case 1:
                showJson(movies);
                break;
            case 2:
                findActor();
                break;
            default:
                std::cout << "False!  try again!\n";
        }
        menu();
        std::cin >> kb;
    }
    std::cout << "Bye!\n";


}