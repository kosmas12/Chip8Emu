//
// Created by kosmas on 11/12/20.
//

#include "cpu.h"

int cpu_running = 1;
int cpu_paused = 2;
int cpu_debug = 3;
int cpu_trace = 4;
int cpu_step = 5;
int cpu_stopped = 0;
int cpu_operationtime = 1000; // CPU tick length in nanoseconds

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
  cpu.operand.WORD = 0;
  cpu.state = cpu_paused;
  cpu.opcodestr = (char*) malloc(200);
}