#include <unistd.h>

#include "assert.h"
#include "gemmes.h"

#include "SDL/SDL.h"
#include "sdl_draw.h"

#define RES_GEMMES "res/gemmes.bmp"
#define RES_FONT "res/font.bmp"


#define GRID_WIDTH 2
#define BGCOLOR 0xffffff
#define GRIDCOLOR 0x9f1f1f
#define OVERCOLOR 0xdddddd
#define SELCOLOR 0xaaaaaa

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

static int over_x;
static int over_y;
static int sel_x;
static int sel_y;
static int stop;

SDL_Surface *screen;
SDL_Surface *sgemmes;
SDL_Surface *font;

void render(board_t b);
void init(board_t);
void draw_gemme(char gemme, int x, int y, int mask);
void do_move(board_t b, int x, int y, int dir_x, int dir_y);
void show_hint(board_t b);

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

    int changed = 1;

    
    while(!stop)
    {
	if(changed)
	    render(b);

	changed = 0;

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
		case SDLK_h:
		    show_hint(b);
		    break;
		default:
		    break;
		}
	    }
	    break;
	    case SDL_MOUSEMOTION:
	        {
		    int old_x = over_x;
		    int old_y = over_y;

		    /* si on est sur le plateau */
		    if(event.button.x >= BOARD_START_X && event.button.x <= WIDTH - BOARD_RIGHT &&
		       event.button.y >= BOARD_START_Y && event.button.y <= HEIGHT - BOARD_BOTTOM)
		    {
			int x, y;
			x = (event.button.x - BOARD_START_X) / (GEMME_SIZE_X + GRID_WIDTH);
			y = (event.button.y - BOARD_START_Y) / (GEMME_SIZE_Y + GRID_WIDTH);

			/* si on a une case cliquee, on permet de cliquer que celles autour */
			if( (sel_x == -1) || 
			    (x == sel_x && y == sel_y) ||
			    (x == sel_x + 1 && y == sel_y) ||
			    (x == sel_x - 1 && y == sel_y) ||
			    (x == sel_x && y == sel_y + 1) ||
			    (x == sel_x && y == sel_y - 1) )
			{
			    over_x = x;
			    over_y = y;
			}
			else
			    over_x = over_y = -1;

		    }
		    else
			over_x = over_y = -1;

		    if(old_x != over_x || old_y != over_y)
			changed = 1;
	        }
		break;
	    case SDL_MOUSEBUTTONDOWN:
	    { 
		    /* si on est sur le plateau */
		    if(over_x != -1)
		    {
			/* on déslectionne si deja selectionné */
			if(over_x == sel_x && over_y == sel_y)
			    sel_x = sel_y = -1;
			else
			{
			    /* si on a deja selectionne une case*/
			    if(sel_x != -1)
			    {
				do_move(b, sel_x, sel_y, over_x, over_y);
				over_x = over_y = sel_x = sel_y = -1;
			    }
			    else
			    {
				sel_x = over_x;
				sel_y = over_y;
			    }
			}
			changed = 1;
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
    int board_size =  b->ysize * (GEMME_SIZE_X + GRID_WIDTH) + GRID_WIDTH;
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
    board_size =  b->xsize * (GEMME_SIZE_Y + GRID_WIDTH) + GRID_WIDTH;

    for(i = 0; i <= b->ysize; ++i)
    {
	draw_rect(screen, WIDTH, HEIGHT,
		  BOARD_START_X,
		  i * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y,
		  board_size,
		  GRID_WIDTH,
		  GRIDCOLOR
	    );
    }

    over_x = over_y = sel_x = sel_y = -1; 

    stop = 0;
}

void render(board_t b)
{
    if(SDL_MUSTLOCK(screen))
	if(SDL_LockSurface(screen) < 0) 
	    return;
    
    int x, y, c;
    
    /* on trace le plateau */
    for(x = 0; x < b->xsize; ++x)
	for(y = 0; y < b->ysize; ++y)
	{
	    if(x == sel_x && y == sel_y)
		c = SELCOLOR;
	    else if(x == over_x && y == over_y)
		c = OVERCOLOR;
	    else
		c = 0xffffff;

	    draw_gemme(board_pos(b, x, y), 
		       x * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X + GRID_WIDTH,
		       y * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y + GRID_WIDTH,
		       c);
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

void draw_gemme(char gemme, int x, int y, int mask)
{
	draw_tile_mask(screen, sgemmes,
		  ((gemme == ' ') ? 0 : gemme - 'A' + 1),
		  GEMME_SIZE_X,
		  GEMME_SIZE_Y,
		  x, y, mask);
}


void do_move(board_t b, int x, int y, int dir_x, int dir_y)
{
    dir_t d;

    if(x - dir_x == 1)
	d = left;
    else if(x - dir_x == -1)
	d = right;
    else if(y - dir_y == 1)
	d = up;
    else if(y - dir_y == -1)
	d = down;


    int ret = !board_move(b, x, y, d);

    if(ret && board_get_hint(b).x == -1) /* partie finie */
    {
	if(!b->silent)
	    fputs("Game over!\n", stderr);
	
	stop = 1;
    }

}

void show_hint(board_t b)
{
    coord_t c = board_get_hint(b);

    c_assert(c.x != -1 && c.y != -1);

    int old_sel_x = sel_x;
    int old_sel_y = sel_y;

    int i;
    for(i = 1; i < 15; ++i)
    {
	if(i % 2 == 0)
	    sel_x = sel_y = -1;
	else
	{
	    sel_x = c.x;
	    sel_y = c.y;
	}
	render(b);
	usleep(100000);
    }

    sel_x = old_sel_x;
    sel_y = old_sel_y;
}


