#ifndef SDL_DRAW_H
#define SDL_DRAW_H

/* some useful SDL routines */

#include "SDL/SDL.h"

void draw_tile(SDL_Surface *screen, SDL_Surface *tiles, int tile, int tile_size_x, int tile_size_y, int x, int y);


void draw_rect(SDL_Surface *screen, int screen_width, int screen_height, int x, int y, int width, int height, int c);




#endif
