cmake_minimum_required(VERSION 3.12)
project(Chapter02)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(funcTemplates funcTemplates.cpp)
add_executable(classTemplates classTemplates.cpp)
add_executable(variableTemplates variableTemplates.cpp)
add_executable(variadicTemplates variadicTemplates.cpp)
add_executable(lambdas lambdas.cpp)
