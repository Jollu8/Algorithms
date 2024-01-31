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
        include/libs/tools/defs.h
        include/libs/tools/utils.h
        ../containers/include/libs/containers/single_linked_list.h
        ../containers/single_linked_list.cpp
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

set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/libs)
target_link_libraries(${PROJECT_NAME} containers fmt::fmt)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wformat=2 -Wno-unused-parameter -Wno-unused-variable -Wno-ignored-qualifiers -Wno-missing-field-initializers)
    target_compile_options(${PROJECT_NAME} PRIVATE -fno-exceptions)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE /W3)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHs-c-)
endif()

target_compile_definitions(${PROJECT_NAME}  PUBLIC FMT_EXCEPTIONS=0)



#enable_testing()
#include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/add_unit_test.cmake)
#link_libraries(runner)
#set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
#
#configure_file(test/cname_blocking_test_filter.txt cname_blocking_test_filter.txt COPYONLY)
#configure_file(test/blocking_modes_test_filter.txt blocking_modes_test_filter.txt COPYONLY)
#configure_file(test/whitelist_test_filter.txt whitelist_test_filter.txt COPYONLY)
#configure_file(test/bad_test_filter.txt bad_test_filter.txt COPYONLY)
#configure_file(test/crash_regress_test_filter.txt crash_regress_test_filter.txt COPYONLY)
#
#add_unit_test(dns64_test ${TEST_DIR} "" TRUE TRUE)
#add_unit_test(dnsproxy_test ${TEST_DIR} "" TRUE TRUE)
#add_unit_test(listener_test ${TEST_DIR} "" TRUE FALSE)
#add_unit_test(truncate_test ${TEST_DIR} "" TRUE TRUE)
#
add_executable(tmp_test EXCLUDE_FROM_ALL test/tmp_test.cpp)
#add_executable(cache_benchmark EXCLUDE_FROM_ALL test/cache_benchmark.cpp)
#add_dependencies(tests listener_standalone)
#if (NOT MSVC)
#    target_link_libraries(listener_standalone resolv)
#endif()