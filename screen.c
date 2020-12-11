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

SDL_Window *emuWindow;

// For now do nothing other than fill the virtual screen with white
void screen_init() {
  emuWindowSurface = SDL_GetWindowSurface(emuWindow);
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 255, 255, 255));
  SDL_UpdateWindowSurface(emuWindow);
}

void clear_screen() {
  SDL_FillRect(emuWindowSurface, NULL, SDL_MapRGB(emuWindowSurface->format, 0, 0, 0));
  SDL_UpdateWindowSurface(emuWindow);
}

void screen_deinit() {
  SDL_DestroyWindow(emuWindow);
}