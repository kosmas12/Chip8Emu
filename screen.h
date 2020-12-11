//
// Created by kosmas on 11/12/20.
//

#ifndef CHIP8EMU_SCREEN_H
#define CHIP8EMU_SCREEN_H

#include <SDL2/SDL.h>

SDL_Window *emuWindow;
SDL_Surface *emuWindowSurface;
void screen_init();
void screen_deinit();

#endif //CHIP8EMU_SCREEN_H
