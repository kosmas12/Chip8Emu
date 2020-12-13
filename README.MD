# Chip8Emu

This is a simple emulator for the CHIP-8 that I am making for fun.
Currently it only initializes the CPU and RAM
and then triggers a CLS instruction after 1 second. 
It only has some memory that can be
of variable size, and it has memory reading and writing functions.
It also has registers for the CPU and a reset
function. This is very early WIP for now.

# Compiling
To compile, you need CMake. Any compiler that CMake supports (pretty much
every C/C++ compiler) will do. While most of the emulator is written
purely using the standard C library, it also requires SDL2, which
is used for the graphics. Then, to compile:

```
mkdir build
cd build
cmake ..
make
```

# Credits
While most of this emulator is coded by me, there are some parts that
I have copied out of craigthomas' [great (Super)CHIP-8 emulator](https://github.com/craigthomas/Chip8C)