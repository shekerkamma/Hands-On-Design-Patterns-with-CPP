cmake_minimum_required(VERSION 3.12)
project(Chapter09)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_FLAGS_DEBUG "-O0")
# set(CMAKE_C_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_C_FLAGS "-O0")

find_package(benchmark REQUIRED)

add_executable(city city.cpp)
add_executable(cout_chaining cout_chaining.cpp)
add_executable(named_args1 named_args1.cpp)
target_link_libraries(named_args1 benchmark::benchmark)
# add_executable(named_args1_extra named_args1_extra.cpp)
add_executable(named_args named_args.cpp)
target_link_libraries(named_args benchmark::benchmark)
# add_executable(named_args_extra named_args_extra.cpp)
# add_executable(poly_chain1 poly_chain1.cpp)
# add_executable(poly_chain2a poly_chain2a.cpp)
add_executable(poly_chain2 poly_chain2.cpp)
add_executable(poly_chain3 poly_chain3.cpp)

# macro(print_all_variables)
#     message(STATUS "print_all_variables------------------------------------------{")
#     get_cmake_property(_variableNames VARIABLES)
#     foreach (_variableName ${_variableNames})
#         message(STATUS "${_variableName}=${${_variableName}}")
#     endforeach()
#     message(STATUS "print_all_variables------------------------------------------}")
# endmacro()
# print_all_variables()