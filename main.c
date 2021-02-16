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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

Parts of the code in this file have been copied from craigthomas' (Super)CHIP-8 emulator which can be found in https://github.com/craigthomas/Chip8C
*/

#include "memory.h"
#include "cpu.h"
#include "screen.h"
#include "input.h"
#include <string.h>

void emu_init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  Uint32 *parameter = (Uint32 *) malloc(sizeof(Uint32));
  *parameter = 1000/60;
  cpu_reset();
  dtimer = SDL_AddTimer((1000 / 60), dec_timers, parameter);
  memory_init(4096);
  screen_init();

}

void Quit() {
  screen_deinit();
  memory_deinit(memory);
  SDL_Quit();
  exit(0);
}

int load_rom(char *filename, int offset) {
  FILE *file;
  int status = 1;

  file = fopen(filename, "r"); // rb is unnecessary because the ROM itself is already binary
  if (file == NULL) {
    printf("Could not load ROM: %s\n", filename);
    status = 0;
  }
  else {
    printf("Successfully loaded ROM: %s\n", filename);
    while (!feof(file)) {
      fread(&memory[offset], 1, 1, file);
      offset++;
    }
    fclose(file);
  }
  return status;
}

int main(int argc, char **argv) {
  emu_init();
  unsigned int instructionpart1;
  unsigned int instructionpart2;
  int mode = 0;
  if(argc > 1) {
    if (strcmp(argv[1], "interactive") == 0) {
      printf("Booting into interactive mode\n");
    }
    else {
        printf("Booting into ROM mode with ROM file %s\n", argv[1]);
        int status = load_rom(argv[1], 0x200);
        if (status == 0) {
            exit(1);
        }
    }
  }
  else {
      printf("No ROM specified and no interactive mode flag. Exiting...\n");
      exit(0);
  }

  while (1) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          Quit();
          break;
      }
      if(argc > 1) {
        if (strcmp(argv[1], "interactive") == 0) {
          mode = 1;
          scanf("%X", &instructionpart1);
          scanf("%X", &instructionpart2);
          cpu.operation.BYTE.high = instructionpart1;
          cpu.operation.BYTE.low = instructionpart2;
        }
      }
      cpu_execute(mode);
    }
  }
  return 0;
}
