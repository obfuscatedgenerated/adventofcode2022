cmake_minimum_required(VERSION 3.8.0)
project(adventofcode2022 C)

set(CMAKE_C_STANDARD 99)

# DAY 01

add_executable(01-part1 src/01/part1.c)
add_executable(01-part2 src/01/part2.c)

file(COPY src/01/01.txt DESTINATION ${CMAKE_BINARY_DIR})

# DAY 02

add_executable(02-part1 src/02/part1.c)
add_executable(02-part2 src/02/part2.c)
