cmake_minimum_required(VERSION 3.27)
project(tools)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(ALGORITHMS_DIR ..)
set(TEST_DIR test)

if(SANITIZE)
    add_compile_options("-fsanitize=address")
    link_libraries("-fsanitize=address")
endif(SANITIZE)

set(SRCS
        runner.cpp
        logger.cpp
        include/enjo/tools/error.h

)

add_library(${PROJECT_NAME} EXCLUDE_FROM_ALL ${SRCS})

# workaround for successful build with spdlog headers
if (NOT MSVC)
    target_compile_options(tools PRIVATE -Werror)
else ()
    add_definitions(-DFMT_EXCEPTIONS=0)
endif ()


find_package(fmt REQUIRED)


if(NOT TARGET containers)
    add_subdirectory(${ALGORITHMS_DIR}/containers ${CMAKE_BINARY_DIR}/containers)
endif(NOT TARGET containers)

if(NOT TARGET DS)
    add_subdirectory(${ALGORITHMS_DIR}/DS ${CMAKE_BINARY_DIR}/Ds)
endif(NOT TARGET DS)

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC include/enjo)
target_link_libraries(${PROJECT_NAME} containers DS fmt::fmt)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wformat=2 -Wno-unused-parameter -Wno-unused-variable -Wno-ignored-qualifiers -Wno-missing-field-initializers)
    target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHs-c-)
endif()

target_compile_definitions(${PROJECT_NAME}  PUBLIC FMT_EXCEPTIONS=0)

add_executable(tmp_test EXCLUDE_FROM_ALL test/tmp_test.cpp)
