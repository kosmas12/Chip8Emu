//
// Created by kosmas on 11/12/20.
//

#ifndef CHIP8EMU_CPU_H
#define CHIP8EMU_CPU_H

#include "common.h"

typedef struct {
    byte registers[16];
    word indexreg;
    word spointer;
    byte stimer;
    byte dtimer;
    word pcounter;
    word operand;
}chip8regs;

chip8regs cpu;

#endif //CHIP8EMU_CPU_H
