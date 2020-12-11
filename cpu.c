//
// Created by kosmas on 11/12/20.
//

#include "cpu.h"

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