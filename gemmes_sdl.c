#include <unistd.h>

#include "assert.h"
#include "gemmes.h"

#ifdef G_WINDOWS
# include "SDL.h"
# include "SDL_thread.h" /* depuis animation, rev > 76 */
#else
# include "SDL/SDL.h"
# include "SDL/SDL_thread.h" /* depuis animation, rev > 76 */
#endif

#include "sdl_draw.h"

#define RES_GEMMES "res/gemmes.bmp"
#define RES_FONT "res/font.bmp"
#define RES_SEL "res/selecteur.bmp"

#define GRID_WIDTH 2
#define BGCOLOR 0x000000
#define GRIDCOLOR 0xffffff

/* emplacement du plateau */
#define BOARD_START_X 10
#define BOARD_START_Y 10

/* emplacement du score depuis le bord droit */
static int SCORE_POS_X;
#define SCORE_POS_Y 20

/* espace apres le plateau */
static int BOARD_RIGHT;
#define BOARD_BOTTOM 10

/* taille d'une gemme */
#define GEMME_SIZE_X 52
#define GEMME_SIZE_Y 48
#define GEMME_ANIM_COUNT 10

#define RECT_COUNT 4


static volatile int over_x;
static volatile int over_y;
static volatile int sel_x;
static volatile int sel_y;
static volatile int stop;
static volatile unsigned int total_seg_count;
static SDL_Rect rects[RECT_COUNT];

volatile int current_frame;
volatile int last_frame;
volatile int changed;

SDL_Surface *screen;
SDL_Surface *sgemmes;
SDL_Surface *font;
SDL_Surface *sel;

void render(board_t b);
void init(board_t);
void draw_gemme(char gemme, int x, int y);
void do_move(board_t b, int x, int y, int dir_x, int dir_y);
void show_hint(board_t b);
int thread_draw(void* d);

void gemmes_start_ihm(board_t b)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
	fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	return;
    }

/* plus il y a de case plus le score est grand !*/
    SCORE_POS_X = 140 + b->xsize * b->ysize / 5;
    BOARD_RIGHT = SCORE_POS_X + 10;

    screen = SDL_SetVideoMode(b->xsize * (GEMME_SIZE_X + GRID_WIDTH) + GRID_WIDTH + BOARD_START_X + BOARD_RIGHT,
			      b->ysize * (GEMME_SIZE_Y + GRID_WIDTH) + GRID_WIDTH + BOARD_START_Y + BOARD_BOTTOM,
			      32, SDL_SWSURFACE);

    SDL_WM_SetCaption("Gemmified", NULL);

    if (screen == NULL)
    {
	fprintf(stderr, "Unable to set %dx%d video: %s\n", screen->w, screen->h, SDL_GetError());
	return;
    }
 
    init(b);

    changed = 1;

    SDL_Thread * thread = SDL_CreateThread(thread_draw, b);
    
    while(!stop)
    {

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
		    if(event.button.x >= BOARD_START_X && event.button.x <= screen->w - BOARD_RIGHT &&
		       event.button.y >= BOARD_START_Y && event.button.y <= screen->h - BOARD_BOTTOM)
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

    SDL_WaitThread(thread, NULL);

    SDL_FreeSurface(font);
    SDL_FreeSurface(sel);
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

    /* on charge les selecteur */
    temp = SDL_LoadBMP(RES_SEL);
    c_assert2(temp, "unable to load " RES_SEL);
    sel = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
    c_assert(sel);
    SDL_FreeSurface(temp);


    draw_rect(screen, 0, 0, screen->w, screen->h, BGCOLOR);


    /* on trace la grille */

    /* traits verticaux */
    int board_size =  b->ysize * (GEMME_SIZE_Y + GRID_WIDTH) + GRID_WIDTH;
    int i;

    for(i = 0; i <= b->xsize; ++i)
    {
	draw_rect(screen,
		  i * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X,
		  BOARD_START_Y,
		  GRID_WIDTH,
		  board_size,
		  GRIDCOLOR
	    );
    }

    /* traits horizontaux */
    board_size =  b->xsize * (GEMME_SIZE_X + GRID_WIDTH) + GRID_WIDTH;

    for(i = 0; i <= b->ysize; ++i)
    {
	draw_rect(screen,
		  BOARD_START_X,
		  i * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y,
		  board_size,
		  GRID_WIDTH,
		  GRIDCOLOR
	    );
    }

    /* score */
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y, "Score:");

    over_x = over_y = sel_x = sel_y = -1; 

    /* nombre de segments */
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y + 3 * font->w, "Created\nsegments:");

    /* nombre de segments total */
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y + 7 * font->w, "Total:");

    stop = 0;
    total_seg_count = 0;

    /* rectangle du plateau */
    rects[0].x = BOARD_START_X;
    rects[0].y = BOARD_START_Y;
    rects[0].w = screen->w - BOARD_RIGHT - BOARD_START_X;
    rects[0].h = screen->h - BOARD_BOTTOM - BOARD_START_Y;

    /* rectangle du score */
    rects[1].x = screen->w - SCORE_POS_X;
    rects[1].y = SCORE_POS_Y + font->w;
    rects[1].w = SCORE_POS_X;
    rects[1].h = font->w;

    /* rectangle du nombre de segment */
    rects[2].x = screen->w - SCORE_POS_X;
    rects[2].y = SCORE_POS_Y + font->w * 5;
    rects[2].w = SCORE_POS_X;
    rects[2].h = font->w;

    /* rectangle du nombre de segment total*/
    rects[3].x = screen->w - SCORE_POS_X;
    rects[3].y = SCORE_POS_Y + font->w * 8;
    rects[3].w = SCORE_POS_X;
    rects[3].h = font->w;

    SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
    //printf("rand=%s\n", b->rs->data);
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

	    int xx = x * (GEMME_SIZE_X + GRID_WIDTH) + BOARD_START_X + GRID_WIDTH;
	    int yy = y * (GEMME_SIZE_Y + GRID_WIDTH) + BOARD_START_Y + GRID_WIDTH;

	    draw_gemme(board_pos(b, x, y), xx, yy);

	    if(x == sel_x && y == sel_y)
		draw_transparent_tile(screen, sel, 1,
				      GEMME_SIZE_Y, GEMME_SIZE_X,
				      xx, yy, 0x000000);
	    else if(x == over_x && y == over_y)
		draw_transparent_tile(screen, sel, 0,
				      GEMME_SIZE_Y, GEMME_SIZE_X,
				      xx, yy, 0x000000);

	}

    /* on trace le score etc */

    char s[30];

    sprintf(s, "%u", b->score);
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y + font->w, s);

    sprintf(s, "%u", b->last_seg_count);
    draw_rect(screen, rects[2].x, rects[2].y, rects[2].w, rects[2].h,  BGCOLOR);
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y + font->w * 5, s);

    sprintf(s, "%u", total_seg_count);
    draw_string(screen, font, screen->w - SCORE_POS_X,  SCORE_POS_Y + font->w * 8, s);

    if(SDL_MUSTLOCK(screen)) 
	SDL_UnlockSurface(screen);


    /* update score,  board... rects */
    SDL_UpdateRects(screen, RECT_COUNT, rects);

}

void draw_gemme(char gemme, int x, int y)
{
    /*if(gemme == ' ')
	printf("%d\n", current_frame);
    */
    /*if(gemme == ' ')
	draw_tile2(screen, sgemmes,
		  current_frame - last_frame, 0, 
		  GEMME_SIZE_Y,
		  GEMME_SIZE_X,
		  x, y);
		  else
	draw_tile2(screen, sgemmes,
		  current_frame, gemme - 'A' + 1,
		  GEMME_SIZE_Y,
		  GEMME_SIZE_X,
		  x, y);
*/

	draw_tile2(screen, sgemmes,
		  current_frame, ((gemme == ' ') ? 0 : (gemme - 'A' + 1)),
		  GEMME_SIZE_Y,
		  GEMME_SIZE_X,
		  x, y);
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

    //printf("%c%d%c\n", x + 'A', y + 1, dir_to_string(d)[0]);

    over_x = over_y = sel_x = sel_y = -1; 

    int ret = !board_move(b, x, y, d);

    total_seg_count += b->last_seg_count;

    if(ret && board_get_hint(b).x == -1) /* partie finie */
    {
	if(!b->silent)
	    fprintf(stderr,"Game over! Score %d\n", b->score);
	
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
	changed = 1;
	usleep(100000);
    }

    sel_x = old_sel_x;
    sel_y = old_sel_y;
}


int thread_draw(void* d)
{
    current_frame = 0;
    last_frame = 0;
    int i = 0;
    while(!stop)
    {
	if(changed)
	    render((board_t)d);

	usleep(1000);

	i++;

	if(i > 15)
	{
	    i = 0;
	    changed = 1;
	    current_frame++;
	    if(current_frame == GEMME_ANIM_COUNT)
		current_frame = 0;
	}
    }

    return 0;
}
