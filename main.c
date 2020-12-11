#include "memory.h"
#include "cpu.h"
#include "screen.h"

void emu_init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  emuWindow = SDL_CreateWindow("Chip8Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  cpu_reset();
  memory_init(4096);
  screen_init();
}

void Quit() {
  screen_deinit();
  memory_deinit(memory);
  SDL_Quit();
  exit(0);
}

int main() {
  SDL_Event event;
  emu_init();
  while (1) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          Quit();
          break;
      }
    }
  }
  return 0;
}
