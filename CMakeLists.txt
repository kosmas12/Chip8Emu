cmake_minimum_required(VERSION 3.1)
project(Chip8Emu C)
find_package(SDL2 REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(Chip8Emu main.c memory.h memory.c common.h cpu.h cpu.c screen.h screen.c input.h input.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})