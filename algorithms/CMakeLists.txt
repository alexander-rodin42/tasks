cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Algorithms)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Sorting
add_executable(BubbleSorting ./sorting/BubbleSorting.cpp)
add_executable(QuickSorting ./Sorting/QuickSorting.cpp)
add_executable(CountingSorting ./Sorting/CountingSorting.cpp)
set_target_properties (BubbleSorting QuickSorting CountingSorting PROPERTIES FOLDER "Sorting")