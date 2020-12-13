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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.*/

#ifndef CHIP8EMU_SCREEN_H
#define CHIP8EMU_SCREEN_H

#include <SDL2/SDL.h>
#include "common.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

SDL_Window *emuWindow;
SDL_Surface *emuWindowSurface;
SDL_Surface *screenDrawingSurface;
void screen_init();
void clear_screen();
void screen_deinit();
void screen_draw(byte x, byte y, int color);
int screen_getpixelcolor(byte x, byte y);

#endif //CHIP8EMU_SCREEN_H
