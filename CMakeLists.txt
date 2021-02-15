cmake_minimum_required(VERSION 3.1)
project(Chip8Emu C)
find_package(SDL2 REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(Chip8Emu main.c memory.h memory.c common.h cpu.h cpu.c screen.h screen.c input.h input.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
configure_file(${CMAKE_SOURCE_DIR}/beep.wav ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

option(USE_DEBUG "Enter debug mode" OFF)
if (USE_DEBUG)
    add_definitions(-DDEBUG)
endif()
