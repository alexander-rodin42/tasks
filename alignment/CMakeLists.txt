cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME alignment)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)