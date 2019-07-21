cmake_minimum_required(VERSION 3.12)
project(Chapter05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(benchmark REQUIRED)
enable_testing()
find_package(GTest REQUIRED)

add_executable(memory1 memory1.cpp)
target_link_libraries(memory1 GTest::GTest GTest::Main)
add_executable(mutex1 mutex1.cpp)
target_link_libraries(mutex1 GTest::GTest GTest::Main)
add_executable(scoped_ptr1_bm scoped_ptr1_bm.cpp)
target_link_libraries(scoped_ptr1_bm benchmark::benchmark)
add_executable(scoped_ptr1 scoped_ptr1.cpp)
target_link_libraries(scoped_ptr1 GTest::GTest GTest::Main)
