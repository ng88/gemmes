
#include "sdl_draw.h"



void draw_tile(SDL_Surface *screen, SDL_Surface *tiles, int tile, int tile_size_x, int tile_size_y, int x, int y)
{

    if (SDL_MUSTLOCK(tiles))
	if (SDL_LockSurface(tiles) < 0) 
	    return;

    int i, j;
    for (i = 0; i < tile_size_x; i++)
    {
	int screenofs = x + (y + i) * (screen->pitch / 4);
	int tileofs = (i + tile * tile_size_x) * (tiles->pitch / 4);
	for (j = 0; j < tile_size_y; j++)
	{
	    ((unsigned int*)screen->pixels)[screenofs] = 
		((unsigned int*)tiles->pixels)[tileofs];
	    screenofs++;
	    tileofs++;
	}
    }
    
    if (SDL_MUSTLOCK(tiles)) 
        SDL_UnlockSurface(tiles);
}


void draw_rect(SDL_Surface *screen, int screen_width, int screen_height, int x, int y, int width, int height, int c)
{
    int i, j;
    for (i = 0; i < height; i++)
    {
	if ((y + i) >= 0 && (y + i) < screen_height)
	{
	    int len = width;
	    int xofs = x;

	    if (xofs < 0)
	    {
		len += xofs;
		xofs = 0;
	    }


	    if (xofs + len >= screen_width)
	    {
		len -= (xofs + len) - screen_width;
	    }
	    int ofs = (i + y) * (screen->pitch / 4) + xofs;

	    for (j = 0; j < len; j++)
		((unsigned int*)screen->pixels)[ofs + j] = c;
	}
    }
}
