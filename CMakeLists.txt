CMAKE_MINIMUM_REQUIRED(VERSION 3.27)

if (NOT CMAKE_INSTALL_PREFIX MATCHES "conan2")
    set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "cmake/conan_provider.cmake")
endif ()
project(algorithms CXX)
add_subdirectory(tools)

#enable_testing()
