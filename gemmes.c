#include <stdio.h>
#include <string.h>

#include "assert.h"

#include "gemmes.h"


void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, font_t * f, int silent)
{
    c_assert(nlines > 0 && nlines < 10 && nrows > 0 && nrows < 27);
    c_assert( (s && strlen(s) > 2) || (!s && (ngemmes > 2 || ngemmes <= 16 )) );

    randseq_t rs;
    
    if(s)
	rs = randseq_new_from_str(s);
    else
	rs = randseq_new(30, ngemmes);

    board_t b = board_new(nlines, nrows, rs);

    b->font = f;
    b->silent = silent;

    gemmes_start_ihm(b);

    board_free(b);
    randseq_free(rs);

}


void gemmes_autoplay(board_t b)
{
    coord_t c;
    while((c = board_get_hint(b)).x != -1 )
    {
	if(!b->silent)
	    printf("Autoplay %c%d %s\n", 'a' + c.x, 1 + c.y, dir_to_string(c.d));

	board_move(b, c.x, c.y, c.d);
    }

    board_print(b);

    if(!b->silent)
	fputs("Game over!\n", stderr);

}

void gemmes_dump(board_t b)
{
    int i;
    for(i = 0; i < b->xsize * b->ysize; ++i)
	putchar(b->data[i]);
    
    printf(" %d\n", b->score);
}
