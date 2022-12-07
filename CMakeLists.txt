cmake_minimum_required(VERSION 3.23)
project(C_Code C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Code
        Y86Disasemmbler.c)
