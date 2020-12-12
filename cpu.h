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
    word prevpcounter; // Last program counter address
    word operation;
    byte rplregstorage[16];
    char *opcodestr; // Opcode stored as string
    int state; // Current CPU state
}chip8regs;

chip8regs cpu;

void cpu_execute();
void cpu_reset();
void spointer_init();
void pcounter_init();
void rpl_init();
void ret();
unsigned int address;

#endif //CHIP8EMU_CPU_H
