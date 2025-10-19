cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME lab_algorithms)
project(${PROJECT_NAME})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

message(STATUS "Done")
