# Chip8Emu

This is a simple emulator for the CHIP 8 that I am making for fun.
Currently it doesn't do anything, it only has some memory that can be
of variable size, and it has memory reading and writing functions.
It also has registers for the CPU. This is very early WIP for now.

# Compiling
To compile, you need CMake. Any compiler that CMake supports (pretty much
every C/C++ compiler) will do. There are no other dependencies, since this
emulator uses only the C standard library.

```
mkdir build
cd build
cmake ..
make
```