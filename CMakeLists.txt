cmake_minimum_required(VERSION 3.15)
project(sudokuX_LP1AED1 C)

set(CMAKE_C_STANDARD 99)

add_executable(sudokuX_LP1AED1 main.c sudokuX.c sudokuX.h test.c backtracking.c)