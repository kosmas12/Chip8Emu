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

Parts of the code have been copied from craigthomas' (Super)CHIP-8 emulator which can be found in https://github.com/craigthomas/Chip8C*/

#include <SDL2/SDL.h>
#include "screen.h"

#ifdef LITTLE_ENDIAN
Uint32 Rmask = 0xff000000;
Uint32 Gmask = 0x00ff0000;
Uint32 Bmask = 0x0000ff00;
Uint32 Amask = 0x000000ff;
#else
Uint32 Rmask = 0x000000ff;
Uint32 Gmask = 0x0000ff00;
Uint32 Bmask = 0x00ff0000;
Uint32 Amask = 0xff000000;
#endif

#define WHITE SDL_MapRGB(screenDrawingSurface->format, 255, 255, 255)
#define BLACK SDL_MapRGB(screenDrawingSurface->format, 0, 0, 0)

// For now do nothing other than fill the virtual screen with white
void screen_init() {
  emuWindow = SDL_CreateWindow("Chip8Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  emuWindowSurface = SDL_GetWindowSurface(emuWindow);
  screenDrawingSurface = SDL_CreateRGBSurface(0, 64, 32, 32, Rmask, Gmask, Bmask, Amask); // Will be used to render
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(emuWindow);
}

void clear_screen() {
  SDL_FillRect(screenDrawingSurface, NULL, SDL_MapRGB(screenDrawingSurface->format, 0, 0, 0));
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(emuWindow);
}

void screen_deinit() {
  SDL_DestroyWindow(emuWindow);
}

void screen_draw(byte x, byte y, int color) {
  SDL_Rect pixel;
  Uint32 pixelcolor = BLACK;

  pixel.x = x;
  pixel.y = y;
  pixel.w = 1;
  pixel.h = 1;
  if (color) {
    pixelcolor = WHITE;
  }
  SDL_FillRect(screenDrawingSurface, &pixel, pixelcolor);
  SDL_BlitScaled(screenDrawingSurface, NULL, emuWindowSurface, NULL);
  SDL_UpdateWindowSurface(emuWindow);
}

int screen_getpixelcolor(byte x, byte y) {
  Uint8 r, g, b;
  Uint32 color = 0;
  int pixelcolor = 0;;
  Uint32 *pixels = (Uint32 *)emuWindowSurface->pixels;
  Uint32 pixel = pixels[(emuWindowSurface->w * y) + x];
  SDL_GetRGB(pixel, emuWindowSurface->format, &r, &g, &b);
  color = SDL_MapRGB(emuWindowSurface->format, r, g, b);
  if (color == WHITE) {
    pixelcolor = 1;
  }
  return pixelcolor;
}