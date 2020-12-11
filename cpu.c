//
// Created by kosmas on 11/12/20.
//

#include "cpu.h"

void cpu_execute() {
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

  switch (cpu.operand.BYTE.high & 0xF0) {
    break;
  }
}

void spointer_init() {
  cpu.spointer.WORD = 0x52;
  printf("Set Stack Pointer to 0x52 (start)\n");
}

void pcounter_init() {
  cpu.pcounter.WORD = 0x200;
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
}