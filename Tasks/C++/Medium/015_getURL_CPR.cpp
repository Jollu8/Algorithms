

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



#include <iostream>
#include <cpr/cpr.h>


int main() {
    cpr::Payload post_request = cpr::Payload({{}});
    std::string get_request = "?";
    std::string input;
    while (input != "exit") {
        std::cout << "Available commands for input: «get», «post»" << std::endl;
        std::cout << "Enter request or command to execute: ";
        std::cin >> input;
        if (input == "get") {
            cpr::Response r = cpr::Get(cpr::Url("http://httpbin.org/get" + get_request));
            std::cout << r.text << std::endl;
            get_request = "?";
            post_request = cpr::Payload({{}});
        } else if (input == "post") {
            cpr::Response r = cpr::Post(cpr::Url("http://httpbin.org/post"),
                                        cpr::Payload(post_request));
            std::cout << r.text << std::endl;
            get_request = "?";
            post_request = cpr::Payload({{}});
        } else if (input == "exit") {
            break;
        } else {
            std::string input2;
            std::cout << "Enter second part of request: ";
            std::cin >> input2;
            get_request += input + "=" + input2 + "&";
        }
    }
    return 0;
}