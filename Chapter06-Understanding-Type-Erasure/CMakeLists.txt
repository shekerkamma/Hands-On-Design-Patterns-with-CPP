cmake_minimum_required(VERSION 3.12)
project(Chapter06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(benchmark)

add_executable(smartptr smartptr.cpp)
add_executable(smartptr_extra smartptr_extra.cpp)
target_link_libraries(smartptr benchmark::benchmark)
