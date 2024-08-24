cmake_minimum_required(VERSION 3.28)
project(nakio)

set(CMAKE_CXX_STANDARD 17)


list(APPEND CMAKE_PREFIX_PATH "/opt/unitree_robotics/lib/cmake")

## Find required packages
find_package(unitree_sdk2 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


add_executable(nakio tests/main.cpp
        include/start/start.h
        include/start/start.cpp
        include/stop/stop.cpp
        include/stop/stop.h
        include/vision/vision.cpp
        include/vision/vision.h
        include/follow/follow.cpp
        include/follow/follow.h
        include/carry/carry.cpp
        include/carry/carry.h
)

include_directories(${Python3_INCLUDE_DIRS})

target_include_directories(nakio PUBLIC ./include/carry)
target_include_directories(nakio PUBLIC ./include/follow)
target_include_directories(nakio PUBLIC ./include/start)
target_include_directories(nakio PUBLIC ./include/stop)
target_include_directories(nakio PUBLIC ./include/vision)
target_link_libraries(nakio unitree_sdk2)
target_link_libraries(nakio ${Python3_LIBRARIES})