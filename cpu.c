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
#include "input.h"

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
  OUTPUT("CPU Program Counter set to address %X\n", address);
}

void ld(byte reg, byte value) {
    cpu.registers[reg] = value;
    OUTPUT("Set general-purpose register %X to %X\n", reg, value);
}

void ldi(unsigned short value) {
  cpu.indexreg.WORD = value;
  OUTPUT("Set index register to %X\n", value);
}

void se(byte reg, byte value) {
  if (cpu.registers[reg] == value) {
    cpu.pcounter.WORD+=2;
    OUTPUT("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    OUTPUT("Values not equal, not skipping instruction\n");
  }
}

void sne(byte reg, byte value) {
  if (cpu.registers[reg] != value) {
    cpu.pcounter.WORD+=2;
    OUTPUT("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    OUTPUT("Values equal, not skipping instruction\n");
  }
}

void seregs(byte reg1, byte reg2) {
  if (cpu.registers[reg1] == cpu.registers[reg2]) {
    cpu.pcounter.WORD+=2;
    OUTPUT("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    OUTPUT("Registers not equal, not skipping instruction\n");
  }
}

void add(byte reg, byte value) {
  cpu.registers[reg] += value;
  OUTPUT("Register %X now set to %X\n", reg, cpu.registers[reg]);
}

void sneregs(byte reg1, byte reg2) {
  if (cpu.registers[reg1] != cpu.registers[reg2]) {
    cpu.pcounter.WORD+=2;
    OUTPUT("CPU Program Counter set to address %X\n", cpu.pcounter.WORD);
  }
  else {
    OUTPUT("Registers equal, not skipping instruction\n");
  }
}

void bit_or(byte reg1, byte reg2) {
  cpu.registers[reg1] = cpu.registers[reg1] | cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to %X\n", reg1, cpu.registers[reg1]);
}

void bit_and(byte reg1, byte reg2) {
  cpu.registers[reg1] = cpu.registers[reg1] & cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to %X\n", reg1, cpu.registers[reg1]);
}

void bit_xor(byte reg1, byte reg2) {
  cpu.registers[reg1] = cpu.registers[reg1] ^ cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to %X\n", reg1, cpu.registers[reg1]);
}

void addregs(byte reg1, byte reg2) {
  int setcarry = 0;
  cpu.registers[reg1] += cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to %X, carry flag ", reg1, cpu.registers[reg1]);
  if (cpu.registers[reg1] > 255) {
    cpu.registers[0xF] = 1;
    setcarry = 1;
  }
  if (setcarry == 1) {
    OUTPUT("set to 1\n");
  }
  else {
    OUTPUT("unchanged\n");
  }
}

void subregs(byte reg1, byte reg2) {
  OUTPUT("Carry flag ");
  if (cpu.registers[reg1] > cpu.registers[reg2]) {
    cpu.registers[0xF] = 1;
    OUTPUT("set to 1\n");
  }
  else {
    OUTPUT("unchanged\n");
  }
  cpu.registers[reg1] -= cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to %X\n", reg1, cpu.registers[reg1]);
}

void shr(byte reg) {
  OUTPUT("Carry flag ");
  if (reg & 1) {
    cpu.registers[0xF] = 1;
    OUTPUT("set to 1\n");
  }
  else {
    OUTPUT("unchanged\n");
  }
  cpu.registers[reg] /= 2;
}

void subnregs(byte reg1, byte reg2) {
  OUTPUT("Carry flag ");
  if (cpu.registers[reg2] > cpu.registers[reg1]) {
    cpu.registers[0xF] = 1;
    OUTPUT("set to 1\n");
  }
  else {
    OUTPUT("unchanged\n");
  }
  cpu.registers[reg1] -= (cpu.registers[reg2] - cpu.registers[reg1]);
  OUTPUT("Set general-purpose register %X to %X\n", reg1, cpu.registers[reg1]);
}

void shl(byte reg) {
  int msb;
  int bits = sizeof(byte) * 8;
  msb = 1 << (bits - 1);
  OUTPUT("Carry flag ");
  if(cpu.registers[reg] & msb) {
    OUTPUT("set to 1\n");
  }
  else {
    OUTPUT("unchanged\n");
  }
  cpu.registers[reg] *= 2;
}

void call(unsigned int address) {
  write_memory(cpu.spointer, cpu.pcounter.BYTE.low);
  cpu.spointer.WORD++;
  write_memory(cpu.spointer, cpu.pcounter.BYTE.high);
  cpu.spointer.WORD++;
  cpu.pcounter.WORD = address;
  OUTPUT("Set CPU Program Counter to %X\n", address);
}

void stor(byte reg) {
  word address;
  address.WORD = cpu.indexreg.WORD;
  for (int i = 0; i <= reg; ++i) {
    write_memory(address, cpu.registers[i]);
    OUTPUT("Wrote value %X to memory address %X\n", memory[(cpu.indexreg.WORD + i)], (cpu.indexreg.WORD + i));
    address.WORD++;
  }
}

void lddecimal(byte reg) {
  word address;
  address.WORD = cpu.indexreg.WORD;
  byte store = cpu.registers[reg] / 100;
  write_memory(address, store);
  OUTPUT("Stored value %X in memory address %X\n", store, cpu.indexreg.WORD);

  address.WORD++;
  store = (cpu.registers[reg] % 100) / 10;
  write_memory(address, store);
  OUTPUT("Stored value %X in memory address %X\n", store, cpu.indexreg.WORD);

  address.WORD++;
  store = (cpu.registers[reg] % 100) % 10;
  write_memory(address, store);
  OUTPUT("Stored value %X in memory address %X\n", store, cpu.indexreg.WORD);
}

void ldfromdt(byte reg) {
  cpu.registers[reg] = cpu.dtimer;
  OUTPUT("Set general-purpose register %X to %X\n", reg, cpu.registers[reg]);
}

void lddt(byte reg) {
  cpu.dtimer = cpu.registers[reg];
  OUTPUT("Set Delay Timer to %X\n", cpu.dtimer);
}

void ldst(byte reg) {
  cpu.stimer = cpu.registers[reg];
  OUTPUT("Set Sound Timer to %X\n", cpu.stimer);
}

void addindex(byte reg) {
  cpu.indexreg.WORD += cpu.registers[reg];
  OUTPUT("Index register set to %X\n", cpu.indexreg.WORD);
}

void storfrommem(byte reg) {
  word address;
  address.WORD = cpu.indexreg.WORD;
  for (int i = 0; i <= reg; i++) {
    cpu.registers[i] = read_memory(address.WORD);
    address.WORD++;
  }
}

void ldregs(byte reg1, byte reg2) {
  cpu.registers[reg1] = cpu.registers[reg2];
  OUTPUT("Set general-purpose register %X to value %X\n", reg1, cpu.registers[reg1]);
}

void rndand(byte reg, byte value) {
  cpu.registers[reg] = (rand() % 255) & value;
  OUTPUT("Set general-purpose register %X to %X\n", reg, cpu.registers[reg]);
}

Uint32 dec_timers(Uint32 delay) {
  if (cpu.dtimer > 0) {
    cpu.dtimer--;
  }
  if (cpu.stimer > 0) {
    cpu.stimer--;
  }
  return delay;
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
  cpu.dtimer = 240;
  cpu.stimer = 2;

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

  OUTPUT("Executing instruction ");
  switch (cpu.operation.BYTE.high & 0xF0) {
    case 0x00:
      switch (cpu.operation.BYTE.low) {
        case 0xE0:
          OUTPUT("0x00E0 - CLS\n");
          clear_screen();
          break;
        case 0xEE:
          OUTPUT("0x00EE - RET\n");
          ret();
          break;
        default:
          OUTPUT("0x0%X - SYS - Jump to machine code routine in address\n", fulloperand);
          jmp(fulloperand);
          break;
      }
      break;
    case 0x10:
      OUTPUT("0x1%X - JMP to address %X\n", fulloperand, fulloperand);
      jmp(fulloperand);
      break;
    case 0x20:
      OUTPUT("0x2%X - CALL subroutine in address %X\n", fulloperand, fulloperand);
      call(fulloperand);
      break;
    case 0x30:
      OUTPUT("0x3%X - Skip next instruction if register %X is Equal to %X\n", fulloperand, operandp1, twodigitoperand2);
      se(operandp1, twodigitoperand2);
      break;
    case 0x40:
      OUTPUT("0x4%X - Skip next instruction if register %X is Not Equal to %X\n", fulloperand, operandp1, twodigitoperand2);
      sne(operandp1, twodigitoperand2);
      break;
    case 0x50:
      OUTPUT("0x5%X0 - Skip next instruction if register %X is Equal to %X\n", twodigitoperand1, operandp1, operandp2);
      seregs(operandp1, operandp2);
      break;
    case 0x60:
      OUTPUT("0x6%X - LD value %X to register %X\n", fulloperand, twodigitoperand2, operandp1);
      ld(operandp1, twodigitoperand2);
      break;
    case 0x70:
      OUTPUT("0x7%X - ADD %X to register %X and store in register %X\n", fulloperand, twodigitoperand2, operandp1, operandp1);
      add(operandp1, twodigitoperand2);
      break;
    case 0x80:
      switch (cpu.operation.BYTE.low & 0xF) {
        case 0x0:
          OUTPUT("0x8%X0 - LD register %X with value of register %X", twodigitoperand1, operandp1, operandp2);
          ldregs(operandp1, operandp2);
          break;
        case 0x1:
          OUTPUT("0x8%X1 - Bitwise OR on registers %X and %X and store the result in register %X\n", twodigitoperand1, operandp1, operandp2, operandp1);
          bit_or(operandp1, operandp2);
          break;
        case 0x2:
          OUTPUT("0x8%X2 - Bitwise AND on registers %X and %X and store the result in register %X\n", twodigitoperand1, operandp1, operandp2, operandp1);
          bit_and(operandp1, operandp2);
          break;
        case 0x3:
          OUTPUT("0x8%X3 - Bitwise XOR on registers %X and %X and store the result in register %X\n", twodigitoperand1, operandp1, operandp2, operandp1);
          bit_xor(operandp1, operandp2);
          break;
        case 0x4:
          OUTPUT("0x8%X4 - ADD registers %X and %X and store the result in register %X, set carry flag if needed\n", twodigitoperand1, operandp1, operandp2, operandp1);
          addregs(operandp1, operandp2);
          break;
        case 0x5:
          OUTPUT("0x8%X5 - SUB register %X from %X and store the result in register %X, set carry flag if register %X > %X\n", twodigitoperand1, operandp2, operandp1, operandp1, operandp1, operandp2);
          subregs(operandp1, operandp2);
          break;
        case 0x6:
          OUTPUT("0x8%X6 - SHR register %X and if LSb=1, set carry flag. Then divide by 2\n", twodigitoperand1, operandp1);
          shr(operandp1);
          break;
        case 0x7:
          OUTPUT("0x8%X7 - SUBN register %X from %X and store the result in register %X, set carry flag if register %X < %X\n", twodigitoperand1, operandp1, operandp2, operandp1, operandp1, operandp2);
          subnregs(operandp1, operandp2);
          break;
        case 0xE:
          OUTPUT("0x8%X6 - SHL register %X and if MSb=1, set carry flag. Then multiply by 2\n", twodigitoperand1, operandp1);
          shl(operandp1);
          break;
        default:
          OUTPUT("0xE%X - Wrong opcode\n", fulloperand); // Since all 0x8 opcodes are implemented, an unimplemented instruction would be a wrong one
          break;
      }
    case 0x90:
      OUTPUT("0x9%X0 - Skip next instruction if register %X is Not Equal to register %X \n", twodigitoperand2, operandp1, operandp2);
      sneregs(operandp1, operandp2);
      break;
    case 0xA0:
      OUTPUT("0xA%X - LD value %X to index register\n", fulloperand, fulloperand);
      ldi(fulloperand);
      break;
    case 0xB0:
      OUTPUT("0xB%X - JMP to address %X + value in register 0", fulloperand, fulloperand);
      jmp(fulloperand + cpu.registers[0]);
      break;
    case 0xC0:
      OUTPUT("0xC%X - Generate a random number from 0 to 255, AND it with %X, and store in %X\n", fulloperand, twodigitoperand2, operandp1);
      rndand(operandp1, twodigitoperand2);
      break;
    case 0xD0:
      x = cpu.operation.BYTE.high & 0xF;
      y = (cpu.operation.BYTE.low & 0xF0) >> 4;
      tempw.WORD = cpu.indexreg.WORD;
      tempb = cpu.operation.BYTE.low & 0xF;
      cpu.registers[0xF] = 0;
      OUTPUT("0xD%X - DRW %d-byte sprite at location x %d and y %d\n", fulloperand, operandp3, operandp1, operandp2);
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
    case 0xE0:
      switch (cpu.operation.BYTE.low & 0xFF) {
        case 0x9E:
          OUTPUT("0xE%X9E - SKip next instruction if key with the value of register %X is Pressed\n", operandp1, operandp1);
          skp(operandp1);
          break;
        case 0xA1:
          OUTPUT("0xE%XA1 - SKip next instruction if key with the value of register %X is Not Pressed\n", operandp1, operandp1);
          sknp(operandp1);
          break;
      }
      break;
    case 0xF0:
      switch (cpu.operation.BYTE.low) {
        case 0x07:
          OUTPUT("0xF%X07 - Place value of Delay Timer to register %X\n", operandp1, operandp1);
          ldfromdt(operandp1);
          break;
        case 0x0A:
          OUTPUT("0xF%X0A - Wait until key is pressed and store key to register %X", operandp1, operandp1);
          waitForKey(operandp1);
          break;
        case 0x15:
          OUTPUT("0xF%X15 - Set Delay Timer to the value of register %X\n", operandp1, operandp1);
          lddt(operandp1);
          break;
        case 0x18:
          OUTPUT("0xF%X18 - Set Sound Timer to the value of register %X\n", operandp1, operandp1);
          ldst(operandp1);
          break;
        case 0x1E:
          OUTPUT("0xF%X1E - ADD the index register to register %X and store in index register\n", operandp1, operandp1);
          addindex(operandp1);
          break;
        case 0x29:
          OUTPUT("0xF%X29 - LD index register with location of sprite %X", operandp1, operandp1);
          ldi((cpu.registers[operandp1] * 5));
          break;
        case 0x33:
          OUTPUT("0xF%X33 - LD decimal hundreds digit of register %X in location index, tens in index i + 1, ones in i + 2\n", operandp1, operandp1);
          lddecimal(operandp1);
          break;
        case 0x55:
          OUTPUT("0xF%X55 - STOR registers 0 through %X to memory starting from the location pointed to by the index register\n", operandp1, operandp1);
          stor(operandp1);
          break;
        case 0x65:
          OUTPUT("0xF%X55 - STOR to registers 0 through %X from memory starting from the location pointed to by the index register\n", operandp1, operandp1);
          storfrommem(operandp1);
          break;
      }
      break;
    default:
      OUTPUT("0x%X - Unimplemented Instruction\n", cpu.operation.WORD);
      break;
  }
}

void indexreg_init() {
  cpu.indexreg.WORD = 0;
  OUTPUT("Set index register to 0\n");
}

void timers_init() {
  cpu.dtimer = 0;
  OUTPUT("Set delay timer to 0\n");
  cpu.stimer = 0;
  OUTPUT("Set sound timer to 0\n");
}

void spointer_init() {
  cpu.spointer.WORD = 0x52;
  OUTPUT("Set Stack Pointer to 0x52 (start)\n");
}

void pcounter_init() {
  cpu.pcounter.WORD = 0x200;
  cpu.prevpcounter.WORD = 0x200;
  OUTPUT("Set Program Counter to 0x200 (start)\n");
}

void rpl_init() {
  for (int i = 0; i < 16; ++i) {
    cpu.rplregstorage[i] = 0;
    OUTPUT("Set RPL Register Storage %X to 0\n", i);
  }
}

void cpu_reset() {
  for (int i = 0; i < 16; ++i) {
    cpu.registers[i] = 0;
    OUTPUT("Set general purpose register %X to 0\n", i);
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