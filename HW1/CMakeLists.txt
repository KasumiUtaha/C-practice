cmake_minimum_required(VERSION 3.13)
project(AP)
cmake_policy(SET CMP0144 NEW)


set(CMAKE_CXX_STANDARD 20)

set(GTEST_ROOT "C:\\Program Files (x86)\\googletest-distribution\\lib\\cmake\\GTest")

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(main
        src/main.cpp
        src/hw1.cpp
        src/unit_test.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
)

