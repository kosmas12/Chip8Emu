//
// Created by kosmas on 10/12/20.
//

#ifndef CHIP8EMU_MEMORY_H
#define CHIP8EMU_MEMORY_H

#include "common.h"

byte *memory;

int memory_init(int memorysize);
inline byte read_memory(register int address);
inline void write_memory(register word address, register byte value);


#endif //CHIP8EMU_MEMORY_H
