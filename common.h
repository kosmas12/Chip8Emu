//
// Created by kosmas on 11/12/20.
//

#ifndef CHIP8EMU_COMMON_H
#define CHIP8EMU_COMMON_H

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


#endif //CHIP8EMU_COMMON_H
