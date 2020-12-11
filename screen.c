//
// Created by kosmas on 11/12/20.
//

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

SDL_Rect screenrect = {0, 0, 64, 32};
SDL_Rect centerScreenRect = {285, 200, 64, 32}; //TODO: Fix x and y to center virtual screen

// For now do nothing other than fill the virtual screen with white
void screen_init() {
  screen = SDL_CreateRGBSurface(0, 128, 64, 32, Rmask, Gmask, Bmask, Amask); //TODO: Increase virtual screen size
  SDL_FillRect(screen, &screenrect, SDL_MapRGB(screen->format, 255, 255, 255));
  SDL_BlitSurface(screen, NULL, SDL_GetWindowSurface(emuWindow), &centerScreenRect);
  SDL_UpdateWindowSurface(emuWindow);
}

void screen_deinit() {
  SDL_FreeSurface(screen);
  SDL_DestroyWindow(emuWindow);
}