# Chip8Emu

This is a simple emulator for the CHIP 8 that I am making for fun.
Currently it only initializes the CPU and RAM
and then creates a window to display things
(nothing for now other than a small white part). 
It only has some memory that can be
of variable size, and it has memory reading and writing functions.
It also has registers for the CPU and a reset
function. This is very early WIP for now.

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