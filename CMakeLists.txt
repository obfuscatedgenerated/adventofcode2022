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

file(COPY src/02/02.txt DESTINATION ${CMAKE_BINARY_DIR})

# DAY 03

add_executable(03-part1 src/03/part1.c)
add_executable(03-part2 src/03/part2.c)

file(COPY src/03/03.txt DESTINATION ${CMAKE_BINARY_DIR})

# DAY 04

add_executable(04-part1 src/04/part1.c)
add_executable(04-part2 src/04/part2.c)

file(COPY src/04/04.txt DESTINATION ${CMAKE_BINARY_DIR})

# DAY 05

add_executable(05-part1 src/05/part1.c)
add_executable(05-part2 src/05/part2.c)

file(COPY src/05/05-head.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY src/05/05-moves.txt DESTINATION ${CMAKE_BINARY_DIR})