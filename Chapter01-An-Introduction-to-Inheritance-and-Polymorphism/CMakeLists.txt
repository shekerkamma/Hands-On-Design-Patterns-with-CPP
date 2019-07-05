cmake_minimum_required(VERSION 3.12)
project(Chapter02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(polyTest polyTest.cpp)
add_executable(emptyClasses emptyClasses.cpp)