# Chip8Emu

This is a simple emulator for the CHIP-8 that I am making for fun.
Currently it initializes the CPU and RAM
and then loads a ROM and starts executing from 0x200.
 
It has some memory that can be
of variable size and memory reading and writing functions, and
it also has all registers for the CPU and a reset
function, along with the implementation of various opcodes. 

Additionally, it has a virtual screen that scales to 
use the whole window.

This is early WIP for now.

# Credits
While most of this emulator is coded by me, there are some parts that
I have copied out of craigthomas' 
[great (Super)CHIP-8 emulator](https://github.com/craigthomas/Chip8C),
like the implementation of the DRW instruction.

# Compiling
To compile, you need CMake. Any compiler that CMake supports (pretty much
every C/C++ compiler) will do.

While most of the code is written purely using the standard C library, 
Chip8Emu also requires SDL2, which  is used for the graphics and input.
Then, to compile:

```
mkdir build
cd build
cmake ..
make
```

Or to compile in debug mode with verbose output for what the CPU does:

```
mkdir build
cd build
cmake .. -DUSE_DEBUG=1
make
```

# Using
When running the emulator with no command line arguments, the
emulator will load a ROM specified in the load_rom() call in main()
and it will then start executing it from virtual memory address 0x200.

If you run the emulator with the `interactive` command line
argument, a real-time interpreter will start where you can type
opcodes and the emulator will execute them