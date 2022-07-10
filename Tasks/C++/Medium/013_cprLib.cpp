#include <iostream>
#include <string>
//#include <cpr/cpr.h>

////cmake_minimum_required(VERSION 3.20)
//project("http request" VERSION 1.0)
//
//
//set(CMAKE_CXX_STANDARD 17)
//
//set (BUILD_CPR_TESTS OFF)
//set (CMAKE_USE_OPENSSL OFF)
//set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
//set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
//include(FetchContent)
//FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
//FetchContent_MakeAvailable(cpr)
//
//add_executable(task1
//main.cpp)
//target_link_libraries(task1
//PRIVATE
//        cpr::cpr)
//



void httpget(char *str) {
    cpr::Response r = cpr::Get(cpr::Url(str));
    std::cout << r.text;
}

int mian() {
    char *str;
    char input = 0;
    std::cout << "===Menu===\n";
    std::cout << "1 get\n2 post\n3 put\n4 delete\n5 patch\n";
    std::cin >> input;

    while (!(input > '0' && input < '6')) {
        std::cout << "Chose correct menu; \n";
        std::cout << "===Menu===\n";
        std::cout << "1 get\n2 post\n3 put\n4 delete\n5 patch\n";
        std::cin >> input;
    }
    switch (input) {
        case '1':
            str = "http://httpbin.org/get";
            httpget(str);
            break;
        case '2':
            str = "http://httpbin.org/post";
            httpget(str);
            break;
        case '3':
            str = "http://httpbin.org/put";
            httpget(str);
            break;
        case '4':
            str = "http://httpbin.org/delete";
            httpget(str);
            break;
        case '5':
            str = "http://httpbin.org/patch";
            httpget(str);
            break;
    }

}
