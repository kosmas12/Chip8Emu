cmake_minimum_required(VERSION 3.1)
project(Chip8Emu C)

set(CMAKE_C_STANDARD 11)

add_executable(Chip8Emu main.c memory.h memory.c)