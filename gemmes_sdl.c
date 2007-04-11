
#include "assert.h"
#include "gemmes.h"


#include "SDL/SDL.h"

#define RES_GEMMES "res/gemmes.bmp"

#define BOARD_SIZE_X 400
#define BOARD_SIZE_Y 300

#define GEMME_SIZE_X 32
#define GEMME_SIZE_Y 32

#define WIDTH BOARD_SIZE_X
#define HEIGHT BOARD_SIZE_Y

#define PITCH (screen->pitch / 4)

SDL_Surface *screen;
SDL_Surface *sgemmes;

void init();
void render(board_t);
void drawtile(char gemme, int x, int y);


void gemmes_start_ihm(board_t b)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	return;
    }


    screen = SDL_SetVideoMode(BOARD_SIZE_X, BOARD_SIZE_Y, 32, SDL_SWSURFACE);
  
    if (screen == NULL)
    {
	fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
	return;
    }
 
    init();

    int stop = 0;
    while(!stop)
    {
	render(b);

	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
	    switch (event.type) 
	    {
	    case SDL_KEYDOWN:
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		    stop = 1;
		break;
	    case SDL_QUIT:
		stop = 1;
		break;
	    }
	}
    }


    SDL_Quit();
}

void init()
{
    /* on charge les gemmes */
    SDL_Surface *temp = SDL_LoadBMP(RES_GEMMES);
    c_assert2(temp, "unable to load " RES_GEMMES);
    sgemmes = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
    c_assert(sgemmes);
    SDL_FreeSurface(temp);
}

void render(board_t b)
{
    if(SDL_MUSTLOCK(screen))
	if(SDL_LockSurface(screen) < 0) 
	    return;
    

    
    drawtile('A', 0, 0);


    if(SDL_MUSTLOCK(screen)) 
	SDL_UnlockSurface(screen);
    
    SDL_UpdateRect(screen, 0, 0, WIDTH, HEIGHT);
}

void drawtile(char gemme, int x, int y)
{
    if (SDL_MUSTLOCK(sgemmes))
	if (SDL_LockSurface(sgemmes) < 0) 
	    return;

    int tile = gemme - 'A';
    int i, j;
    for (i = 0; i < GEMME_SIZE_X; i++)
    {
	int screenofs = x + (y + i) * PITCH;
	int tileofs = (i + tile * GEMME_SIZE_Y) * (sgemmes->pitch / 4);
	for (j = 0; j < GEMME_SIZE_Y; j++)
	{
	    ((unsigned int*)screen->pixels)[screenofs] = 
		((unsigned int*)sgemmes->pixels)[tileofs];
	    screenofs++;
	    tileofs++;
	}
    }
    
    if (SDL_MUSTLOCK(sgemmes)) 
        SDL_UnlockSurface(sgemmes);
}
