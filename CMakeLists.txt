cmake_minimum_required(VERSION 3.8)

project(snake_multiplayer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lncurses")
add_executable(snake_multiplayer ${SOURCE_FILES})
