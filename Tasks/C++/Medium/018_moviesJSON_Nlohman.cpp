//Задача 1. Информация о фильме с кинопортала
//        pushpin Что нужно сделать:
//Запишите подробную информацию о киноленте в виде JSON-файла. Выберите понравившуюся вам картину на любимом портале, проанализируйте информацию о ней и составьте JSON-словарь.
//
//В информации должны присутствовать: страна и дата создания киноленты, студия, которая вела съёмки, автор сценария, режиссёр и продюсер киноленты. Обязательно добавьте информацию обо всех главных действующих лицах и тех актёрах, которые их сыграли.
//
//pushpin Что оценивается:
//Валидность созданного JSON-документа.
//
//pushpin Как отправить работу на проверку:
//Пришлите ссылку на repl.it или файл .срр с решением через форму ниже.


//// for CmakeLists.txt
//cmake_minimum_required(VERSION 3.20.2)
//project(task1)
//
//set(CMAKE_CXX_STANDARD 17)
//set(JSON_BuildTests OFF CACHE INTERNAL "")
//add_subdirectory(nlohmann_json)
//
//
//add_executable(task1 main.cpp)
//target_link_libraries(task1 PRIVATE nlohmann_json::nlohmann_json)


//// for json  file

//{
//"titanic1": [
//{
//"name": "Titanic",
//"country": "US",
//"director": "James Cameron",
//"writer": "James Cameron",
//"rate": 7.8,
//"year": 1997,
//"time": 174,
//"actor": [
//{
//"name": "Leonardo",
//"fulName": "DiCaprio",
//"live": "US",
//"birth": 1986,
//"gender": true
//},
//{
//"name": "Kate",
//"fulName": "Winslet",
//"live": "UK",
//"birth": 1988,
//"gender": false
//},
//{
//"name": "Billy",
//"fulName": "Zane",
//"live": "US",
//"birth": 1982,
//"gender": true
//},
//{
//"name": "Kathy",
//"fulName": "Bates",
//"live": "BL",
//"birth": 1975,
//"gender": false
//},
//{
//"name": "Frances",
//"fulName": "Fisher",
//"live": "US",
//"birth": 1968,
//"gender": false
//},
//{
//"name": "Gloria",
//"fulName": "Stuart",
//"live": "US",
//"birth": 1955,
//"gender": false
//},
//{
//"name": "Bill",
//"fulName": "Paxton",
//"live": "UK",
//"birth": 1973,
//"gender": true
//},
//{
//"name": "Bernard",
//"fulName": "Hill",
//"live": "US",
//"birth": 1957,
//"gender": true
//},
//{
//"name": "David",
//"fulName": "Garber",
//"live": "US",
//"birth": 1967,
//"gender": true
//},
//{
//"name": "Jonathan",
//"fulName": "Hyde",
//"live": "GR",
//"birth": 1975,
//"gender": true
//},
//{
//"name": "Suzy",
//"fulName": "Amis",
//"live": "IZ",
//"birth": 1976,
//"gender": false
//}
//]
//}
//],
//"titanic2": [
//{
//"name": "Titanic",
//"country": "US",
//"director": "James Cameron",
//"writer": "James Cameron",
//"rate": 7.8,
//"year": 1997,
//"time": 174,
//"actor": [
//{
//"name": "Leonardo",
//"fulName": "DiCaprio",
//"live": "US",
//"birth": 1986,
//"gender": true
//},
//{
//"name": "Kate",
//"fulName": "Winslet",
//"live": "UK",
//"birth": 1988,
//"gender": false
//},
//{
//"name": "Billy",
//"fulName": "Zane",
//"live": "US",
//"birth": 1982,
//"gender": true
//},
//{
//"name": "Kathy",
//"fulName": "Bates",
//"live": "BL",
//"birth": 1975,
//"gender": false
//},
//{
//"name": "Frances",
//"fulName": "Fisher",
//"live": "US",
//"birth": 1968,
//"gender": false
//},
//{
//"name": "Gloria",
//"fulName": "Stuart",
//"live": "US",
//"birth": 1955,
//"gender": false
//},
//{
//"name": "Bill",
//"fulName": "Paxton",
//"live": "UK",
//"birth": 1973,
//"gender": true
//},
//{
//"name": "Bernard",
//"fulName": "Hill",
//"live": "US",
//"birth": 1957,
//"gender": true
//},
//{
//"name": "David",
//"fulName": "Garber",
//"live": "US",
//"birth": 1967,
//"gender": true
//},
//{
//"name": "Jonathan",
//"fulName": "Hyde",
//"live": "GR",
//"birth": 1975,
//"gender": true
//},
//{
//"name": "Suzy",
//"fulName": "Amis",
//"live": "IZ",
//"birth": 1976,
//"gender": false
//}
//]
//}
//],
//"titanic3": [{
//"name"
//:
//"Titanic",
//"country"
//:
//"US",
//"director"
//:
//"James Cameron",
//"writer"
//:
//"James Cameron",
//"rate"
//:
//7.8,
//"year"
//:
//1997,
//"time"
//:
//174,
//"actor"
//:
//[
//{
//"name": "Leonardo",
//"fulName": "DiCaprio",
//"live": "US",
//"birth": 1986,
//"gender": true
//},
//{
//"name": "Kate",
//"fulName": "Winslet",
//"live": "UK",
//"birth": 1988,
//"gender": false
//},
//{
//"name": "Billy",
//"fulName": "Zane",
//"live": "US",
//"birth": 1982,
//"gender": true
//},
//{
//"name": "Kathy",
//"fulName": "Bates",
//"live": "BL",
//"birth": 1975,
//"gender": false
//},
//{
//"name": "Frances",
//"fulName": "Fisher",
//"live": "US",
//"birth": 1968,
//"gender": false
//},
//{
//"name": "Gloria",
//"fulName": "Stuart",
//"live": "US",
//"birth": 1955,
//"gender": false
//},
//{
//"name": "Bill",
//"fulName": "Paxton",
//"live": "UK",
//"birth": 1973,
//"gender": true
//},
//{
//"name": "Bernard",
//"fulName": "Hill",
//"live": "US",
//"birth": 1957,
//"gender": true
//},
//{
//"name": "David",
//"fulName": "Garber",
//"live": "US",
//"birth": 1967,
//"gender": true
//},
//{
//"name": "Jonathan",
//"fulName": "Hyde",
//"live": "GR",
//"birth": 1975,
//"gender": true
//},
//{
//"name": "Suzy",
//"fulName": "Amis",
//"live": "IZ",
//"birth": 1976,
//"gender": false
//}
//]}
//]
//}

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


int main() {
    std::ifstream file("C:\\Users\\zholu\\Desktop\\CPP_primer\\SkillBox\\c++\\skillbox_32\\task1_1\\titanic.json");
    nlohmann::json j;
    file >> j;
    std::cout << j << std::endl;

    std::string name;
    std::cout << "Name:";
    std::cin >> name;

    for (auto it = j.begin(); it != j.end(); ++it) {
        nlohmann::json movie = it.value();
        nlohmann::json cast = movie["cast"];
        for (auto jt = cast.begin(); jt != cast.end(); ++jt) {
            std::string c_name = to_string(jt.value());
            if (c_name.find(name) != std::string::npos) {
                std::cout << name << " in " << it.key() << " as " << jt.key() << std::endl;
            }
        }
    }
}


