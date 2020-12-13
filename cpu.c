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

#include "cpu.h"
#include "screen.h"
#include "memory.h"

int cpu_running = 1;
int cpu_paused = 2;
int cpu_debug = 3;
int cpu_trace = 4;
int cpu_step = 5;
int cpu_stopped = 0;
int cpu_operationtime = 1000; // CPU tick length in nanoseconds

void ret() {
  cpu.spointer.WORD--;
  cpu.pcounter.BYTE.high = read_memory(cpu.spointer.WORD);
  cpu.spointer.WORD--;
  cpu.pcounter.BYTE.low = read_memory(cpu.spointer.WORD);
}

void jmp(unsigned int address) {
  cpu.pcounter.WORD = address;
  printf("CPU Program Counter set to address %X\n", address);
}

void ld(byte reg, byte value) {
    cpu.registers[reg] = value;
    printf("Set general-purpose register %X to %X\n", reg, value);
}

void ldi(unsigned short value) {
  cpu.indexreg.WORD = value;
  printf("Set index register to %X\n", value);
}

void se(byte reg, byte value) {
  if (cpu.registers[reg] == value) {
    cpu.pcounter.WORD+=2;
    printf("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    printf("Values not equal, not skipping instruction\n");
  }
}

void sne(byte reg, byte value) {
  if (cpu.registers[reg] != value) {
    cpu.pcounter.WORD+=2;
    printf("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    printf("Values equal, not skipping instruction\n");
  }
}

void cpu_execute(int mode) {
  byte x;
  byte y;
  byte source;          // Source register
  byte target;         // Target register
  byte tempb;         // A temporary byte
  int temp;          // A general-purpose temporary integer
  int i;
  int j;
  int k;
  int color;          // Store whether to change pixel state to on or off
  int currentcolor;   // Stores the value of the background pixel
  word tempw;         // A temporary word
  int xcor;
  int ycor;

  cpu.prevpcounter = cpu.pcounter;

  if (mode == 0) {
    cpu.operation.BYTE.high = read_memory(cpu.pcounter.WORD);
    cpu.pcounter.WORD++;
    cpu.operation.BYTE.low = read_memory(cpu.pcounter.WORD);
    cpu.pcounter.WORD++;
  }

  unsigned int fulloperand = cpu.operation.WORD & 0x0FFF;
  unsigned int operandp1 = (cpu.operation.WORD & 0x0F00) / 0x100; // Dividing gives us exclusively the operand with no 0s after it
  unsigned int operandp2 = (cpu.operation.WORD & 0x00F0) / 0x10;
  unsigned int operandp3 = cpu.operation.WORD & 0x000F;
  unsigned int twodigitoperand1 = (cpu.operation.WORD & 0x0FF0) / 0x10;
  unsigned int twodigitoperand2 = cpu.operation.WORD & 0x00FF;

  printf("Executing instruction ");
  switch (cpu.operation.BYTE.high & 0xF0) {
    case 0x00:
      switch (cpu.operation.BYTE.low) {
        case 0xE0:
          printf("0x00E0 - CLS\n");
          clear_screen();
          break;
        case 0xEE:
          printf("0x00EE - RET\n");
          ret();
          break;
        default:
          printf("0x00%X%X - Unimplemented Instruction\n", operandp2, operandp3);
          break;
      }
      break;
    case 0x10:
      printf("0x1%X - JMP to address %X\n", fulloperand, fulloperand);
      jmp(fulloperand);
      break;
    case 0x60:
      printf("0x6%X - LD value %X to register %X\n", fulloperand, twodigitoperand2, operandp1);
      ld(operandp1, twodigitoperand2);
      break;
    case 0xA0:
      printf("0xA%X - LD value %X to index register\n", fulloperand, fulloperand);
      ldi(fulloperand);
      break;
    case 0xD0:
      x = cpu.operation.BYTE.high & 0xF;
      y = (cpu.operation.BYTE.low & 0xF0) >> 4;
      tempw.WORD = cpu.indexreg.WORD;
      tempb = cpu.operation.BYTE.low & 0xF;
      cpu.registers[0xF] = 0;
      printf("0xD%X - DRW %d-byte sprite at location x %d and y %d\n", fulloperand, operandp3, operandp1, operandp2);
      for (i = 0; i < (cpu.operation.BYTE.low & 0xF); i++) {
        tempb = read_memory(cpu.indexreg.WORD + i);
        ycor = cpu.registers[y] + i;
        ycor = ycor % WINDOW_HEIGHT;

        for (j = 0; j < 8; j++) {
          xcor = cpu.registers[x] + j;
          xcor = xcor % WINDOW_WIDTH;

          color = (tempb & 0x80) ? 1 : 0;
          currentcolor = screen_getpixelcolor(xcor, ycor);

          cpu.registers[0xF] = (currentcolor && color) ? 1 : cpu.registers[0xF];
          color = color ^ currentcolor;

          screen_draw(xcor, ycor, color);
          tempb = tempb << 1;
        }
      }
      break;
    case 0x30:
      printf("0x3%X - Skip next instruction if register %X is Equal to %X\n", fulloperand, operandp1, twodigitoperand2);
      se(operandp1, twodigitoperand2);
      break;
    case 0x40:
      printf("0x4%X - Skip next instruction if register %X is Not Equal to %X\n", fulloperand, operandp1, twodigitoperand2);
      sne(operandp1, twodigitoperand2);
      break;
    default:
      printf("0x%X - Unimplemented Instruction\n", cpu.operation.WORD);
      break;
  }
}

void indexreg_init() {
  cpu.indexreg.WORD = 0;
  printf("Set index register to 0\n");
}

void timers_init() {
  cpu.dtimer = 0;
  printf("Set delay timer to 0\n");
  cpu.stimer = 0;
  printf("Set sound timer to 0\n");
}

void spointer_init() {
  cpu.spointer.WORD = 0x52;
  printf("Set Stack Pointer to 0x52 (start)\n");
}

void pcounter_init() {
  cpu.pcounter.WORD = 0x200;
  cpu.prevpcounter.WORD = 0x200;
  printf("Set Program Counter to 0x200 (start)\n");
}

void rpl_init() {
  for (int i = 0; i < 16; ++i) {
    cpu.rplregstorage[i] = 0;
    printf("Set RPL Register Storage %X to 0\n", i);
  }
}

void cpu_reset() {
  for (int i = 0; i < 16; ++i) {
    cpu.registers[i] = 0;
    printf("Set general purpose register %X to 0\n", i);
  }
  rpl_init();
  spointer_init();
  pcounter_init();
  timers_init();
  indexreg_init();
  cpu.operation.WORD = 0;
  cpu.state = cpu_paused;
  cpu.opcodestr = (char*) malloc(200);
}