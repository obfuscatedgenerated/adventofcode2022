# Advent of Code

This repository contains my solutions to the [Advent of Code](https://adventofcode.com/) puzzles, all in C!

**Heavy puzzle spoilers ahead! This is your only warning!**

Note: the input *should* be different for every participant. You should edit the input files in each source directory BEFORE running the CMake configuration step (or edit the outputted file from that step).

All solutions are tested on Windows 10 (64bit, GCC 12 with MinGW and Ninja) and Raspberry Pi OS (armhf Debian Buster, GCC 8.3.0 with Unix Makefiles).

## Building

*The makefile will build every program at once! If you don't want this, select the targets you want in the build command (step 5).*

1. Clone the repository: `git clone https://github.com/obfuscatedgenerated/adventofcode2022.git`
2. Create a build directory: `mkdir build`
3. Change into the build directory: `cd build`
4. Run CMake configuration step: `cmake ..` (you can choose a generator with the -G option. I recommend Unix Makefiles on Unix and MinGW Makefiles or Ninja on Windows)
5. Run the build step: `cmake --build .` (you can specify a target with the --target option, e.g. `cmake --build . --target 01-part1`)
6. Execute the program! You'll want to keep the copied input file(s) in the same directory as the executable.

## Directory

### 01 - Calorie Counting

* [Problem](https://adventofcode.com/2022/day/1)
* [Solution](src/01/)

*Targets: 01-part1, 01-part2*

### 02 - Rock Paper Scissors

* [Problem](https://adventofcode.com/2022/day/2)
* [Solution](src/02/)

*Targets: 02-part1, 02-part2*
