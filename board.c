#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "board.h"
#include "assert.h"


const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};


board_t board_alloc(int nlines, int nrows, randseq_t rs)
{
    c_assert(rs && nlines > 0 && nrows > 0);
   
    board_t b = (board_t)malloc(sizeof(struct s_board));

    c_assert2(b, "malloc failed");

    b->ysize = nlines;
    b->xsize = nrows;
    b->rs = rs;
    b->score = 0;

    b->silent = 0;
    b->font = NULL;

    b->last_seg_count = 0;

    b->data = (char*)malloc(nlines * nrows);

    c_assert2(b->data, "malloc failed");

    return b;
}

board_t board_new(int nlines, int nrows, randseq_t rs)
{

    board_t b = board_alloc(nlines, nrows, rs);

    int i;
    for(i = 0; i < nlines * nrows; ++i)
    {
	b->data[i] = randseq_next(rs);

	int x = board_index_to_x(b, i);
	int y = board_index_to_y(b, i);

	c_assert(b->data[i] == board_pos(b, x, y));

	while(board_searchline(b, x, y, left) >= 2 || board_searchline(b, x, y, up) >= 2)
	  b->data[i] = randseq_next(rs);

    }

    return b;

/*  


   Ne fournit pas le bon resultat (cf enonce, fig1)



    int i = 1;
    char c1=randseq_next(rs), c2=randseq_next(rs), c3;

    b->data[0]=c1;
    b->data[1]=c2;
	
    while(i < nlines * nrows){
	c3=randseq_next(rs);
	if ( (c1==c2) && (c2==c3) )	{
	    //do nothing
	}else{
	    b->data[i]=c3;
	    i++;
	}	
	c1=c2;
	c2=c3;
	}*/

}


void board_free(board_t b)
{
    if(!b)
	return;

//    randseq_free(b->rs);
    free(b->data);
    free(b);
}


int board_is_valid_move(board_t b, int col, int line, dir_t dir)
{
    c_assert(b);

    if(col < 0 || col >= b->xsize)
    {
	if(!b->silent)
	    fprintf(stderr, "Invalid column specifier:   not between 'a' and '%c'\n\n", 'a' + b->xsize - 1);
	return 0;
    }

    if(line < 0 || line >= b->ysize)
    {
	if(!b->silent)
	    fprintf(stderr, "Invalid line specifier:   not between '1' and '%d'\n\n", b->ysize);
	return 0;
    }

    int x = col + dx[dir];
    int y = line + dy[dir];

    if(x < 0 || y < 0 || x >= b->xsize || y >=  b->ysize)
    {
	if(!b->silent)
	    fprintf(stderr, "Invalid move %c%d %s (cannot switch against the walls)\n\n", col + 'a', line + 1, dir_to_string(dir));
	return 0;
    }
    

    return 1;
}

int board_searchline(board_t b, int x, int y, dir_t dir)
{
        c_assert(b && x >= 0 && x < b->xsize && y >=0 && y < b->ysize);

	int cpt = 0, dist = 1;
	char current = board_pos(b,x,y);

	while(board_neighbor_valid(b, x, y, dir, dist) && current == board_neighbor(b, x, y, dir, dist)) /*je teste par rapport à le case voisine dans la direction donnée*/
	{
	    cpt++;
	    dist++;
	}
	return cpt;
}


int board_move(board_t b, int x, int y, dir_t dir)
{
    c_assert(b);

    if(!board_is_valid_move(b, x, y, dir))
	return 1;

    /* on fait l'echange */
    board_swap(b, x, y, dir);

    /* combien on a de segment maintenant ? */
    int seg_count = board_segment_count(b, x, y) + board_segment_count(b, x + dx[dir], y + dy[dir]);

    if(!seg_count)
    { /* on a pas cree de segments */
	board_swap(b, x, y, dir);	/* on retablit */
	if(!b->silent)
	    fputs("Invalid move (move leads nowhere)\n", stderr);
	return 1;
    }

    board_update(b);

    return 0;
}

void board_swap(board_t b, int x, int y, dir_t dir)
{
    c_assert(b && x >= 0 && x < b->xsize && y >=0 && y < b->ysize);

    char tmp = board_pos(b, x, y);
    board_pos(b, x, y) =  board_neighbor(b, x, y, dir, 1);
    board_neighbor(b, x, y, dir, 1) = tmp;
}

int board_segment_count(board_t b, int x, int y)
{
    c_assert(b && x >= 0 && x < b->xsize && y >=0 && y < b->ysize);

    return (board_searchline(b, x, y, up) + board_searchline(b, x, y, down) >= 2) +
	 (board_searchline(b, x, y, left) + board_searchline(b, x, y, right) >= 2);
}


void board_update_helper(board_t b, int multiple_seg, int seg_count)
{
    c_assert(b);

    /* TAGGED indique une case marquee, ie la ou il y a plus de 3 gemmes
       identiques de suite et EMPTY indique une case ou ce n'est pas le cas */
    enum { TAGGED = '1', EMPTY = '0' };

    board_t buff =  board_alloc(b->ysize, b->xsize, b->rs);

    int ncase = buff->ysize * buff->xsize;

    int old_score = b->score;

    int i;

    for(i = 0; i < ncase; ++i)
	buff->data[i] = EMPTY;

    /* on va chercher les segments */

    int x, y;
    for(y = 0; y < b->ysize ; y++)
	for(x = 0; x < b->xsize ;x++)
	{
	    char current = board_pos(b, x, y);

	    if( board_pos(buff, x, y) == EMPTY ) /* si la case n'est pas marquee */
	    {
		if(board_searchline(b, x, y, left) == 2)
		{ /* alors on est dans un segment horizontal */

		    int x2 = x - 2;
		    while(x2 < buff->xsize && board_pos(b, x2, y) == current)
			board_pos(buff, x2++, y) = TAGGED;

		    b->score += (x2 - x + 2 - 1) * 5 * multiple_seg;
		    multiple_seg *= 2;
		    seg_count++;
		}

		if(board_searchline(b, x, y, up) == 2)
		{ /* alors on est dans un segment horizontal */

		    int y2 = y - 2;
		    while(y2 < buff->ysize && board_pos(b, x, y2) == current)
			board_pos(buff, x, y2++) = TAGGED;

		    b->score += (y2 - y + 2 - 1) * 5 * multiple_seg;
		    multiple_seg *= 2;
		    seg_count++;
		}
	    }
	}

    if(old_score != b->score) /* si on a eu des segments */
    {

	/* on va maintenant remplacer les segments par des espaces */
	
	for(i = 0; i < ncase; ++i)
	{
	    int x = board_index_to_x(buff, i);
	    int y = board_index_to_y(buff, i);
	    
	    if( board_pos(buff, x, y) == TAGGED )
		board_pos(b, x, y) = ' ';
	}
	
	board_print(b);
	if(!b->silent)
	    usleep(500000); /* sleep 0.5 second*/

	/* on fait tomber les gemmes */

	int x, y;
	for(x = 0; x < b->xsize; ++x)
	{
	    int col_changed = 1;
	    while(col_changed) /* car il peut y avoir plusieurs trous par colonne */
	    {
		col_changed = 0;
		for(y = b->ysize - 1; y >= 0; --y)
		{
		    if(board_pos(b, x, y) == ' ')
		    {
			col_changed = 1;
			/* on cherche la position de la premiere gemme au dessus */
			i = y - 1;
			while(i >= 0 && board_pos(b, x, i) == ' ')
			    i--;

			/* on fait tomber les gemmes du dessus */

			int h =  y - i; /* hauteur du trou */

			int t;
			for(t = y; t >= 0; --t)
			{
			    if(t - h < 0)
				board_pos(b, x, t) = randseq_next(b->rs);
			    else
				board_pos(b, x, t) = board_pos(b, x, t - h);
			}
		    }
		}
	    }
	}

	board_update_helper(b, multiple_seg, seg_count);
    }
    else
	b->last_seg_count = seg_count;

    board_free(buff);

}

coord_t board_get_hint(board_t b)
{
    coord_t ret;
    ret.x = ret.y = -1;

    int x, y;
    dir_t d;

    int old_silent = b->silent;
    b->silent = 1;

    for(y = 0; y < b->ysize ; y++)
	for(x = 0; x < b->xsize ;x++)
	    for(d = 0; d < 4 ;d++)
	    {
		/* si c'est un coup valide */
		if(board_is_valid_move(b, x, y, d))
		{		    

		    /* on essaye */
		    board_swap(b, x, y, d);

		    /* combien on a cree de segment */
		    int seg_count = board_segment_count(b, x, y) + 
			            board_segment_count(b, x + dx[d], y + dy[d]);

                    /* on retablit */
		    board_swap(b, x, y, d);

		    if(seg_count)
		    { /* c'est un coup qui abouti */
			ret.x = x;
			ret.y = y;
			ret.d = d;
			b->silent = old_silent;
			return ret;
		    }
		}
	    }

    b->silent = old_silent;
    return ret;
}

char * dir_to_string(dir_t d)
{
    switch(d)
    {
    case up: return "up";
    case down: return "down";
    case left: return "left";
    case right: return "right";
    default: return "unknow";
    }
}





















