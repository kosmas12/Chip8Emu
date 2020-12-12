//
// Created by kosmas on 10/12/20.
//
#include <stdlib.h>
#include "memory.h"

void memory_init(int memorysize) {
  memory = (byte*) calloc(sizeof(byte), memorysize);
  if(memory != NULL) {
    printf("Initialized %d bytes of memory\n", memorysize);
  }
  else {
    printf("Couldn't initialize memory!\n");
    exit(1);
  }
}

byte read_memory(register int address) {
  return memory[address];
}

void write_memory(register word address, register byte value) {
  value = (value>>8) | (value<<8);
  memory[address.WORD] = value;
}

void memory_deinit(byte* memory) {
  free(memory);
  printf("Memory successfully deinitialized\n");
}