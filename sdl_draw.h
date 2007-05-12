/***************************************************************************
 *   This file is part of the 'gemmes' project                             *
 *                                                                         *
 *                                                                         *
 *   Copyright (C) 2007 by                                                 *
 *         GARCH Soufiane                                                  *
 *         GUILLAUME Nicolas <ng@ngsoft-fr.com>                            *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License only.          *
 *   See the COPYING file.                                                 *
 ***************************************************************************/


#ifndef SDL_DRAW_H
#define SDL_DRAW_H

/* some useful SDL routines */

#ifdef G_WINDOWS
# include "SDL.h"
#else
# include "SDL/SDL.h"
#endif


void draw_tile(SDL_Surface *screen, SDL_Surface *tiles, int tile, int tile_size_x, int tile_size_y, int x, int y);

void draw_transparent_tile(SDL_Surface *screen, SDL_Surface *tiles, int tile, int tile_size_x, int tile_size_y, int x, int y, unsigned int transparent_color);

void draw_tile2(SDL_Surface *screen, SDL_Surface *tiles, int tilex, int tiley, int tile_size_x, int tile_size_y, int x, int y);

void draw_rect(SDL_Surface *screen, int x, int y, int width, int height, int c);


void draw_string(SDL_Surface *screen, SDL_Surface * font, int x, int y, char * s);

#endif
