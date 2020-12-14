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



#ifndef CHIP8EMU_COMMON_H
#define CHIP8EMU_COMMON_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

SDL_Event event;

typedef unsigned char byte;

typedef union {
    unsigned short int WORD;
    struct {
#ifdef LITTLE_ENDIAN
        //On Little Endian architectures, the bytes are stored in the order of low to high
        byte low, high;
#else
        //On Big Endian architectures, the bytes are stored in the order of high to low
        byte high, low;
#endif
    }BYTE;
}word;

#endif //CHIP8EMU_COMMON_H
