cmake_minimum_required(VERSION 3.28)
project(KIdefix)

set(CMAKE_CXX_STANDARD 17)


list(APPEND CMAKE_PREFIX_PATH "/opt/unitree_robotics/lib/cmake")

## Find required packages
find_package(unitree_sdk2 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


add_executable(KIdefix tests/main.cpp
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
        include/statemachine/statemachine.cpp
        include/statemachine/statemachine.h
)

include_directories(${Python3_INCLUDE_DIRS})

target_include_directories(KIdefix PUBLIC ./include/carry)
target_include_directories(KIdefix PUBLIC ./include/follow)
target_include_directories(KIdefix PUBLIC ./include/start)
target_include_directories(KIdefix PUBLIC ./include/stop)
target_include_directories(KIdefix PUBLIC ./include/vision)
target_include_directories(KIdefix PUBLIC ./include/statemachine)
target_link_libraries(KIdefix unitree_sdk2)
target_link_libraries(KIdefix ${Python3_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/picture)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/module)
set(SOURCE_FILE ${CMAKE_SOURCE_DIR}/include/vision/vision.py)
file(COPY ${SOURCE_FILE} DESTINATION ${CMAKE_BINARY_DIR}/module)
set(SOURCE_FILE ${CMAKE_SOURCE_DIR}/include/vision/traffic_signs.pt)
file(COPY ${SOURCE_FILE} DESTINATION ${CMAKE_BINARY_DIR}/module)