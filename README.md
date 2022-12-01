# Advent of Code

This repository contains my solutions to the [Advent of Code](https://adventofcode.com/) puzzles, all in C!

## Building

*The makefile will build every program at once! If you don't want this, select the targets you want in the build command (step 5).*

1. Clone the repository: `git clone https://github.com/obfuscatedgenerated/adventofcode2022.git`
2. Create a build directory: `mkdir build`
3. Change into the build directory: `cd build`
4. Run CMake configuration step: `cmake ..` (you can choose a generator with the -G option. I recommend Unix Makefiles on Unix and MinGW Makefiles on Windows)
5. Run the build step: `cmake --build .` (you can specify a target with the --target option, e.g. `cmake --build . --target 01`)

## Directory

### 01 - Calorie Counting

* [Problem](https://adventofcode.com/2022/day/1)
* [Solution](src/01/)

### 02 - ???

