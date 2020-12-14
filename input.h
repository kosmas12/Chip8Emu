//
// Created by kosmas on 14/12/20.
//

#ifndef CHIP8EMU_INPUT_H
#define CHIP8EMU_INPUT_H
#include "common.h"

typedef struct mappedKey {
    SDL_Keycode actualKey;
    byte emuKey;
}mappedKey;

byte findEmuKey(SDL_Keycode keycode);
SDL_Keycode findActualKey(byte hexkey);
int isKeyPressed(byte hexkey);
void skp(byte reg);
void sknp(byte reg);
void waitForKey(byte reg);
byte checkForPressedKey();

#endif //CHIP8EMU_INPUT_H
