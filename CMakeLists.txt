cmake_minimum_required(VERSION 3.8.0)
project(adventofcode2022 C)

set(CMAKE_C_STANDARD 99)

add_executable(01 src/01/main.c)

file(COPY src/01/01.txt DESTINATION ${CMAKE_BINARY_DIR})