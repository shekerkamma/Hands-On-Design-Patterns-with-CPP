cmake_minimum_required(VERSION 3.12)
project(Chapter08)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(function_call function_call.cpp)
add_executable(not_equal not_equal.cpp)
add_executable(not_equal_friend not_equal_friend.cpp)
add_executable(registry registry.cpp)
add_executable(visitor visitor.cpp)
