#include <stdio.h>
#include <string.h>

#include "assert.h"

#include "gemmes.h"

#

void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, int silent)
{
    c_assert(nlines > 0 && nlines < 27 && nrows > 0 && nrows < 27);
    c_assert( (s && strlen(s) > 2) || (!s && (ngemmes > 2 || ngemmes <= 16 )) );

    randseq_t rs = NULL;
    board_t b = NULL;
    
    if(s) /* l'utilisateur force l'utilisation d'une sequence (option -s) */
    {
	rs = randseq_new_from_str(s, ngemmes);
	b = board_new(nlines, nrows, rs);
    }
    else
    {
	int i = 0;

	while(!b && i < MAX_TRY_COUNT) /* tant qu'on arrive pas a creer un plateau,
					  on retire au hasard une sequence */
	{
	    if(rs)
		randseq_free(rs);

	    rs = randseq_new(nrows * nlines, ngemmes);
	    b = board_new(nlines, nrows, rs);

	    i++;
	}
    }



    if(!b) /* La creation n'est pas possible (il n'existe plus de coup) */
    {
	
	if(!silent)
	    fputs("Unable to create the board with this rand sequence.\n", stderr);
	
	
	randseq_free(rs);
	return;
	
    }


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
	fprintf(stderr,"Game over! Score %d\n", b->score);

}

void gemmes_dump(board_t b)
{
    int i;
    for(i = 0; i < b->xsize * b->ysize; ++i)
	putchar(b->data[i]);
    
    printf(" %d\n", b->score);
}


void gemmes_autoplay_createtest(board_t b)
{
    puts("#! ./testsuite");
    puts("p Ce fichier fait une (longue) partie jusqu'au bout");

    char * dump = strdup(b->data);
    int i = 0;
    coord_t c;
    while((c = board_get_hint(b)).x != -1 )
    {
	if(i % 20 == 0)
	    fputs("\n< ", stdout);

	printf("%c%d%c ", 'a' + c.x, 1 + c.y, dir_to_string(c.d)[0]);

	board_move(b, c.x, c.y, c.d);

	++i;
    }

    fputs("\n> ", stdout); gemmes_dump(b);
    

    printf("$ ./gemmes -q -x %d -y %d -c %d -s", b->xsize, b->ysize, b->rs->ncolor);


    for(i = 0; i < b->xsize * b->ysize; ++i)
	putchar(dump[i]);

    puts("");

    free(dump);


}
