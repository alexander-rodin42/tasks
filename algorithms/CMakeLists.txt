cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Algorithms)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Sorting
add_executable(BubbleSorting ./sorting/BubbleSorting.cpp)
add_executable(QuickSorting ./sorting/QuickSorting.cpp)
add_executable(CountingSorting ./sorting/CountingSorting.cpp)
add_executable(InsertionSorting ./sorting/InsertionSorting.cpp)
add_executable(MergeSorting ./sorting/MergeSorting.cpp)
set_target_properties (BubbleSorting QuickSorting CountingSorting InsertionSorting MergeSorting PROPERTIES FOLDER "Sorting")
