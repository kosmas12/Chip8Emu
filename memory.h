//
// Created by kosmas on 10/12/20.
//

#ifndef CHIP8EMU_MEMORY_H
#define CHIP8EMU_MEMORY_H

typedef unsigned char byte;

typedef union {
    unsigned short int WORD;
    struct {
#ifdef BIG_ENDIAN
        //On Big Endian architectures, the bytes are stored in the order of high to low
          byte high, low;
#else
        //On Little Endian architectures, the bytes are stored in the order of low to high
        byte low, high;
#endif
    }BYTE;
}word;

byte *memory;

int memory_init(int memorysize);
inline byte read_memory(register int address);
inline void write_memory(register word address, register byte value);


#endif //CHIP8EMU_MEMORY_H
