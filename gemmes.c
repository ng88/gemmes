#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    char * line = NULL;
    size_t len = 0;
    size_t read = 0;

    int stop = 0;
    int entree;

    while( read != -1 && !stop )
    {
	board_print(b);

	if(!silent && b->last_seg_count)
	    printf("This move created %d segment(s).\n", b->last_seg_count);

	entree = 0;
	while(!entree && read != -1 && !stop) /* tant que pas d'entree correct */
	{
	    if(!silent)
		puts("\nWhat's your move? (or ? for help, h for hint, d for dump, q to quit)");

	    read = getline(&line, &len, stdin); /* une ligne peut contenir plusieurs commandes */

	    if(read != -1)
	    {
		char * cmd = line;
		int i;
		for(i = 0; i < read; ++i)
		{
		    line[i] = tolower(line[i]);

		    if(line[i] == ' ' || i == read - 1)
		    {
			entree = gemmes_process_command(b, cmd, line + i - cmd, &stop);
			if(stop)
			    break;

			if(i + 1 < read)
			    cmd = line + i + 1;

		    }
		}
	    }

	}
    }

    if (line)
	free(line);

    board_free(b);
    randseq_free(rs);


}

int gemmes_process_command(board_t b, char * line, int read, int * stop)
{
    c_assert(stop);

    if(read == 0)
	return 0;
    else if(read == 1) /* c'est peut être une commande */
    {
	switch(line[0])
	{
	case 'd': /* dump */
	{
	    int i;
	    for(i = 0; i < b->xsize * b->ysize; ++i)
		putchar(b->data[i]);

	    printf(" %d\n", b->score);
	    return 1;
	}
	case 'h': /* hint */
	{
	    coord_t c = board_get_hint(b);

	    if(!b->silent && c.x != -1)
		printf("Have a look at %c%d\n", 'a' + c.x, 1 + c.y);

	    return 0;
	}
	case '?': /* help */
	    if(!b->silent)
		puts(HELP_MSG);
	    return 1;
	    break;
	case 'q': /* quit */
	    *stop = 1;
	    return 1;
	default:
	    if(!b->silent)
		fputs("Invalid command\n", stderr);
	    return 0;
	}
    }
    else if(read == 3) /* c'est peut être un coup */
    {
	dir_t dir;

	switch(line[2])
	{
	case 'u': dir = up;  break;
	case 'd': dir = down;  break;
	case 'l': dir = left;  break;
	case 'r': dir = right;  break;
	default:
	    if(!b->silent)
		fprintf(stderr, "Invalid direction specifier (%c): must be one of 'u' (up), 'd' (down), 'r' (right), 'l' (left)\n\n", line[2]);
	    return 0;
	}
		
	int ret = !board_move(b, line[0] - 'a', line[1] - '1', dir);

	if(ret && board_get_hint(b).x == -1) /* partie finie */
	{
	    if(!b->silent)
		fputs("Game over!\n", stderr);

	    *stop = 1;
	}

	return ret;

    }
    else
    {
	if(!b->silent)
	    fputs("Invalid command\n", stderr);
	return 0;
    }
}

