cmake_minimum_required(VERSION 3.28)
project(nakio)

set(CMAKE_CXX_STANDARD 17)

add_executable(nakio main.cpp
        example/build_test.cpp)
