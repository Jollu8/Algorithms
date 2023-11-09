cmake_minimum_required(VERSION 3.23)
project(Algorithms)
set(CMAKE_CXX_STANDARD 20)
add_executable(task main.cpp)
#add_executable(Allocator_pool Allocator/Pool.cpp)
#set_target_properties(Allocator_pool PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#        )
#add_executable(Allocator_liner Allocator/Linear.cpp)
#set_target_properties(Allocator_liner PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#
#add_executable(cache_fifo Cache/First_InFirst_Out.cpp)
#set_target_properties(cache_fifo
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#add_executable(cache_lru Cache/LeastRecentlyUsed.cpp)
#set_target_properties(cache_lru PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#
#
#add_executable(ComputationalGeometry_BresenHamLiner ComputationalGeometry/BresenhamsLine.cpp)
#set_target_properties(ComputationalGeometry_BresenHamLiner
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#        )
#add_executable(ComputationalGeometry_RamerDuglas ComputationalGeometry/RamerDuglasPeucker.cpp)
#set_target_properties(ComputationalGeometry_RamerDuglas
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#add_executable(ComputationalGeometry_ScanLine ComputationalGeometry/ScanLineMethod.cpp)
#set_target_properties(ComputationalGeometry_ScanLine
#        PROPERTIES
#        CXX_STANDARD 20
#        CXX_STANDARD_REQUIRED ON)
#
#add_executable(Container_ForwardList Containers/ForwardList.cpp)
#set_target_properties(Container_ForwardList
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#add_executable(Container_LinkedList Containers/linkedlist.cpp)
#set_target_properties(Container_LinkedList
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#add_executable(Container_Vector Containers/Vector.cpp)
#set_target_properties(Container_Vector
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#
#add_executable(Cryptography_BlowFish Cryptography/BlowFish.cpp)
#set_target_properties(Cryptography_BlowFish
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#add_executable(Cryptography_CeasarChipper Cryptography/CeasarChiper.cpp)
#set_target_properties(Cryptography_CeasarChipper
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#
#add_executable(Cryptography_DataEncryptStandard Cryptography/DataEncryptStandard.cpp)
#set_target_properties(Cryptography_DataEncryptStandard
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON )
#add_executable(Cryptography_DiffieHelman Cryptography/DiffieHelman.cpp)
#set_target_properties(Cryptography_DiffieHelman
#        PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON)
#




#include(FetchContent)
#
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG release-1.10.0
#)
#
#FetchContent_MakeAvailable(googletest)
#
#add_executable(gUnittest Gtests/tests.cpp)
#set_target_properties(gUnittest PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#        )
#
#target_link_libraries(gUnittest gtest_main gmock_main)



