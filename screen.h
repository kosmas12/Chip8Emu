//
// Created by kosmas on 11/12/20.
//

#ifndef CHIP8EMU_SCREEN_H
#define CHIP8EMU_SCREEN_H

#include <SDL2/SDL.h>
#include "common.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320
#define SCALE_MULTIPLIER 10

SDL_Window *emuWindow;
SDL_Surface *emuWindowSurface;
void screen_init();
void clear_screen();
void screen_deinit();
void screen_draw(byte x, byte y, int color);
int screen_getpixelcolor(byte x, byte y);

#endif //CHIP8EMU_SCREEN_H
