
#include "assert.h"
#include "gemmes.h"

#include "SDL/SDL.h"
#include "sdl_draw.h"

#define RES_GEMMES "res/gemmes.bmp"
#define RES_FONT "res/font.bmp"


#define GRID_WIDTH 2
#define BGCOLOR 0xffffff
#define GRIDCOLOR 0x9f1f1f

/* emplacement du plateau */
#define BOARD_START_X 10
#define BOARD_START_Y 10

/* emplacement du score depuis le bord droit */
#define SCORE_POS_X 140
#define SCORE_POS_Y 20

/* espace apres le plateau */
#define BOARD_RIGHT 150
#define BOARD_BOTTOM 10

/* taille d'une gemme */
#define GEMME_SIZE_X 32
#define GEMME_SIZE_Y 32

/* taille totale de la fenetre */
static int WIDTH;
static int HEIGHT;


SDL_Surface *screen;
SDL_Surface *sgemmes;
SDL_Surface *font;

void render(board_t);
void init(board_t);
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
 
    init(b);

    

    int stop = 0;
    while(!stop)
    {
	render(b);

	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
	    switch (event.type) 
	    {
	    case SDL_KEYUP:
	    {
		switch(event.key.keysym.sym)
		{
		case SDLK_a:
		    gemmes_autoplay(b);
		    stop = 1;
		    break;
		case SDLK_d:
		    gemmes_dump(b);
		    break;
		case SDLK_ESCAPE:
		case SDLK_q:
		    stop = 1;
		    break;
		default:
		    break;
		}
	    }
	    break;
	    case SDL_QUIT:
		stop = 1;
		break;
	    }
	}
    }

    SDL_FreeSurface(font);
    SDL_FreeSurface(sgemmes);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

void init(board_t b)
{
    /* on charge les gemmes */
    SDL_Surface *temp = SDL_LoadBMP(RES_GEMMES);
    c_assert2(temp, "unable to load " RES_GEMMES);
    sgemmes = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
    c_assert(sgemmes);
    SDL_FreeSurface(temp);

    /* on charge la police */
    temp = SDL_LoadBMP(RES_FONT);
    c_assert2(temp, "unable to load " RES_FONT);
    font = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
    c_assert(font);
    SDL_FreeSurface(temp);


    draw_rect(screen, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, BGCOLOR);


    /* on trace la grille */

    /* traits verticaux */
    int board_size =  b->xsize * (GEMME_SIZE_X + GRID_WIDTH) + GRID_WIDTH;
    int i;

    for(i = 0; i <= b->xsize; ++i)
    {
	draw_rect(screen, WIDTH, HEIGHT,
		  i * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X,
		  BOARD_START_Y,
		  GRID_WIDTH,
		  board_size,
		  GRIDCOLOR
	    );
    }

    /* traits horizontaux */
    board_size =  b->ysize * (GEMME_SIZE_Y + GRID_WIDTH) + GRID_WIDTH;

    for(i = 0; i <= b->xsize; ++i)
    {
	draw_rect(screen, WIDTH, HEIGHT,
		  BOARD_START_X,
		  i * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y,
		  board_size,
		  GRID_WIDTH,
		  GRIDCOLOR
	    );
    }

}

void render(board_t b)
{
    if(SDL_MUSTLOCK(screen))
	if(SDL_LockSurface(screen) < 0) 
	    return;
    
    int x, y;
    
    /* on trace le plateau */
    for(x = 0; x < b->xsize; ++x)
	for(y = 0; y < b->ysize; ++y)
	{
	    draw_gemme(board_pos(b, x, y), 
		       x * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X + GRID_WIDTH,
		       y * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y + GRID_WIDTH);
	}

    /* on trace le score */

    char s[30];

    sprintf(s, "%d", b->score);

    draw_string(screen, font, WIDTH - SCORE_POS_X,  SCORE_POS_Y, "Score:");
    draw_string(screen, font, WIDTH - SCORE_POS_X,  SCORE_POS_Y + font->w, s);


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
