//
// Created by kosmas on 11/12/20.
//

#include <SDL2/SDL.h>
#include "screen.h"

#if BIG_ENDIAN
Uint32 Rmask = 0xff000000;
Uint32 Gmask = 0x00ff0000;
Uint32 Bmask = 0x0000ff00;
Uint32 Amask = 0x000000ff;
#else
Uint32 rmask = 0x000000ff;
Uint32 gmask = 0x0000ff00;
Uint32 bmask = 0x00ff0000;
Uint32 amask = 0xff000000;
#endif

#define WHITE SDL_MapRGB(emuWindowSurface->format, 255, 255, 255)
#define BLACK SDL_MapRGB(emuWindowSurface->format, 0, 0, 0)

SDL_Window *emuWindow;

// For now do nothing other than fill the virtual screen with white
void screen_init() {
  SDL_Init(SDL_INIT_EVERYTHING);
  emuWindow = SDL_CreateWindow("Chip8Emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  emuWindowSurface = SDL_GetWindowSurface(emuWindow);
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(emuWindow);
}

void clear_screen() {
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(emuWindow);
}

void screen_deinit() {
  SDL_DestroyWindow(emuWindow);
}

void screen_draw(byte x, byte y, int color) {
  SDL_Rect pixel;
  Uint32 pixelcolor = BLACK;

  pixel.x = x * SCALE_MULTIPLIER;
  pixel.y = y * SCALE_MULTIPLIER;
  pixel.w = SCALE_MULTIPLIER;
  pixel.h = SCALE_MULTIPLIER;
  if (color) {
    pixelcolor = WHITE;
  }
  SDL_FillRect(emuWindowSurface, &pixel, pixelcolor);
  SDL_UpdateWindowSurface(emuWindow);
}

int screen_getpixelcolor(byte x, byte y) {
  Uint8 r, g, b;
  Uint32 color = 0;
  int pixelcolor = 0;
  x = x * SCALE_MULTIPLIER;
  y = y * SCALE_MULTIPLIER;
  Uint32 *pixels = (Uint32 *)emuWindowSurface->pixels;
  Uint32 pixel = pixels[(emuWindowSurface->w * y) + x];
  SDL_GetRGB(pixel, emuWindowSurface->format, &r, &g, &b);
  color = SDL_MapRGB(emuWindowSurface->format, r, g, b);
  if (color == WHITE) {
    pixelcolor = 1;
  }
  return pixelcolor;
}