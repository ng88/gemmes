
#include "assert.h"
#include "gemmes.h"

#include "SDL/SDL.h"
#include "sdl_draw.h"

#define RES_GEMMES "res/gemmes.bmp"


#define GRID_WIDTH 1
#define BGCOLOR 0xffffff
#define GRIDCOLOR 0x9f1f1f

/* emplacement du plateau */
#define BOARD_START_X 10
#define BOARD_START_Y 10

/* espace apres le plateau */
#define BOARD_RIGHT 50
#define BOARD_BOTTOM 10

/* taille d'une gemme */
#define GEMME_SIZE_X 32
#define GEMME_SIZE_Y 32

/* taille totale de la fenetre */
static int WIDTH;
static int HEIGHT;


SDL_Surface *screen;
SDL_Surface *sgemmes;
SDL_Surface *grille;

void render(board_t);
void init();
void draw_gemme(char gemme, int x, int y);

void gemmes_start_ihm(board_t b)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	return;
    }

    WIDTH = b->xsize * (GEMME_SIZE_X + GRID_WIDTH) + GRID_WIDTH + BOARD_START_X + BOARD_RIGHT;
    HEIGHT = b->ysize * (GEMME_SIZE_Y + GRID_WIDTH) + GRID_WIDTH + BOARD_START_Y + BOARD_BOTTOM;

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
  
    if (screen == NULL)
    {
	fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
	return;
    }
 
    init();

    //gemmes_autoplay(b);

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

    SDL_FreeSurface(sgemmes);
    SDL_FreeSurface(screen);
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

    draw_rect(screen, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, BGCOLOR);

}

void render(board_t b)
{
    if(SDL_MUSTLOCK(screen))
	if(SDL_LockSurface(screen) < 0) 
	    return;
    

    /* on trace le plateau */
    int x, y;
    for(x = 0; x < b->xsize; ++x)
	for(y = 0; y < b->ysize; ++y)
	{

	    draw_gemme(board_pos(b, x, y), 
		       x * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X + GRID_WIDTH,
		       y * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y + GRID_WIDTH);
	}


    if(SDL_MUSTLOCK(screen)) 
	SDL_UnlockSurface(screen);
    
    SDL_UpdateRect(screen, 0, 0, WIDTH, HEIGHT);
}

void draw_gemme(char gemme, int x, int y)
{
    draw_tile(screen, sgemmes,
	      ((gemme == ' ') ? 0 : gemme - 'A' + 1),
	      GEMME_SIZE_X,
	      GEMME_SIZE_Y,
	      x, y);
}
