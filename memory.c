/*Created by kosmas on 10/12/20.

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
  memory[address.WORD] = value;
}

void memory_deinit(byte* memory) {
  free(memory);
  printf("Memory successfully deinitialized\n");
}