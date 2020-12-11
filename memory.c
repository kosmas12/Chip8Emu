//
// Created by kosmas on 10/12/20.
//
#include <stdlib.h>
#include "memory.h"

int memory_init(int memorysize) {
  memory = (byte*) malloc((sizeof(byte) * memorysize));
  return memory != NULL;
}

byte read_memory(register int address) {
  return memory[address];
}

void write_memory(register word address, register byte value) {
  memory[address.WORD] = value;
}