
#include "assert.h"
#include "gemmes.h"


#include "SDL/SDL.h"


void gemmes_start_ihm(board_t b)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	return;
    }



    SDL_Quit();
}
