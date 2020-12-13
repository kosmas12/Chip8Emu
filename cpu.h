/*Created by kosmas on 11/12/20.

Chip8Emu - A CHIP-8 emulator made for fun
Copyright (C) 2020  Kosmas Raptis

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/

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

void cpu_execute(int mode);
void cpu_reset();
void spointer_init();
void pcounter_init();
void rpl_init();
void ret();
void se(byte reg, byte value);
void sne(byte reg, byte value);
void seregs(byte reg1, byte reg2);
void add (byte reg, byte value);
void sneregs(byte reg1, byte reg2);
unsigned int address;

#endif //CHIP8EMU_CPU_H
