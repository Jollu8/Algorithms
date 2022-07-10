

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
    cpr::Response r;
    r = cpr::Get(cpr::Url("http://httpbin.org/html"),
                 cpr::Header({{"accept", "text/html"}}));


    std::cout << r.text.substr(r.text.find("<h1>") + 4, r.text.find("</h1>")
                                                        - r.text.find("<h1>")) << '\n';
}