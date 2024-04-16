cmake_minimum_required(VERSION 3.27)
project(DS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

set(SRCS
        AVL_tree.cpp

)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include/enjo)
target_compile_definitions(${PROJECT_NAME} PUBLIC)
target_link_libraries(${PROJECT_NAME} tools)

# workaround for successful build with spdlog headers
if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
            FMT_EXCEPTIONS=0
            WIN32_LEAN_AND_MEAN
            NOMINMAX)
    target_compile_options(${PROJECT_NAME} PUBLIC -U__cpp_char8_t)
endif ()


if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
    target_compile_options(${PROJECT_NAME} PUBLIC -Wno-format-nonliteral) # for fmt's chrono build
    if (CMAKE_C_COMPILER_ID MATCHES ".*Clang")
        target_compile_options(${PROJECT_NAME} PUBLIC -Wno-unknown-warning-option -Wno-deprecated-experimental-coroutine)
    else ()
        target_compile_options(${PROJECT_NAME} PUBLIC -Wno-return-type -Wno-missing-field-initializers -Wno-redundant-move -Wno-array-bounds -Wno-changes-meaning)
    endif ()
    target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHs-c-)
endif ()
target_compile_definitions(${PROJECT_NAME} PUBLIC FMT_EXCEPTIONS=0)

enable_testing()
include(../tools/cmake/add_unit_test.cmake)
link_libraries(DS tools)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_unit_test(test_binary_heap ${TEST_DIR} . TRUE TRUE)
