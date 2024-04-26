cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_executable(main ./src/main.cpp)
target_include_directories(main PUBLIC ./lib)
target_link_directories(main PUBLIC ./lib)
target_link_libraries(main PUBLIC libimage.a)
