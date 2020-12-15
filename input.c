//
// Created by kosmas on 14/12/20.
//

#include "input.h"
#include "cpu.h"

/* Actual PC keyboard:      Emulated CHIP-8 keyboard:
     1 2 3 4                    1 2 3 C
     Q W E R                    4 5 6 D
     A S D F                    7 8 9 E
     Z X C V                    A 0 B F */

mappedKey keyMap[] = {
        {SDLK_1, 0x1},
        {SDLK_2, 0x2},
        {SDLK_3 , 0x3},
        {SDLK_4, 0xC},
        {SDLK_q, 0x4},
        {SDLK_w, 0x5},
        {SDLK_e, 0x6},
        {SDLK_r, 0xD},
        {SDLK_a, 0x7},
        {SDLK_s, 0x8},
        {SDLK_d, 0x9},
        {SDLK_f, 0xE},
        {SDLK_z, 0xA},
        {SDLK_x, 0x0},
        {SDLK_c, 0xB},
        {SDLK_v, 0xF}
};


byte findEmuKey(SDL_Keycode keycode) {
  for (int i = 0; i < ((sizeof(keyMap) / sizeof(mappedKey))); ++i) {
    if (keyMap[i].actualKey == keycode) {
      return keyMap[i].emuKey;
    }
  }
  return 0;
}

SDL_Keycode findActualKey(byte hexkey) {
  for (int i = 0; i < ((sizeof(keyMap) / sizeof(mappedKey))); ++i) {
    if (keyMap[i].emuKey == hexkey) {
      return keyMap[i].actualKey;
    }
  }
  return SDLK_SPACE;
}

int isKeyPressed(byte hexkey) {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  if (keys[findActualKey(hexkey)]) {
    return 1;
  }
  return 0;
}

void skp(byte reg) {
  if (isKeyPressed(cpu.registers[reg])) {
    cpu.pcounter.WORD++;
    printf("Set CPU Program Counter to address %X\n", cpu.pcounter.WORD);
  }
  else {
    printf("Key with value %X not pressed, not skipping instruction\n", cpu.registers[reg]);
  }
}

void sknp(byte reg) {
  if (!isKeyPressed(cpu.registers[reg])) {
    cpu.pcounter.WORD++;
    printf("Set CPU Program Counter to address %X\n", cpu.pcounter.WORD);
  }
  else {
    printf("Key with value %X pressed, not skipping instruction\n", cpu.registers[reg]);
  }
}

byte checkForPressedKey() {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  for (int i = 0; i < (sizeof(keyMap) / sizeof(struct mappedKey)); ++i) {
    if (keys[findActualKey(keyMap[i].emuKey)]) {
      return keyMap[i].emuKey;
    }
  }
  return 0;
}

void waitForKey(byte reg) {
  while (SDL_WaitEvent(&event) >= 0) {
    switch (event.type) {
      case SDL_KEYDOWN:
        cpu.registers[reg] = checkForPressedKey();
        break;
    }
  }
}