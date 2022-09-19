cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME Algorithms)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Search
add_executable(BinarySearch ./search/BinarySearch.cpp)
add_executable(LinearSearch ./search/LinearSearch.cpp)
add_executable(TernarySearch ./search/TernarySearch.cpp)
set_target_properties (BinarySearch LinearSearch TernarySearch PROPERTIES FOLDER "Search")

# Sorting
add_executable(BubbleSorting ./sorting/BubbleSorting.cpp)
add_executable(QuickSorting ./sorting/QuickSorting.cpp)
add_executable(CountingSorting ./sorting/CountingSorting.cpp)
add_executable(InsertionSorting ./sorting/InsertionSorting.cpp)
add_executable(MergeSorting ./sorting/MergeSorting.cpp)
add_executable(SelectionSorting ./sorting/SelectionSorting.cpp)
add_executable(ShellSorting ./sorting/ShellSorting.cpp)
add_executable(StupidSorting ./sorting/StupidSorting.cpp)
set_target_properties (BubbleSorting QuickSorting CountingSorting InsertionSorting MergeSorting
						SelectionSorting ShellSorting StupidSorting PROPERTIES FOLDER "Sorting")
