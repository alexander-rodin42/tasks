cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME SmartPointers)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Smart pointers
add_executable(SharedPtr ./source/SharedPtr.cpp)
add_executable(UniquePtr ./source/UniquePtr.cpp)

set_target_properties (SharedPtr UniquePtr PROPERTIES FOLDER "SmartPointers")
