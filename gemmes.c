#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"

#include "gemmes.h"
#include "board.h"



void start_game_loop(int nlines, int nrows, int ngemmes, char * s, int big, int silent)
{

    c_assert(nlines > 0 && nlines < 10 && nrows > 0 && nrows < 27);
    c_assert( (s && strlen(s) > 2) || ngemmes > 2 );

    randseq_t rs;
    
    if(s)
	rs = randseq_new_from_str(s);
    else
	rs = randseq_new(30, ngemmes);

    board_t b = board_new(nlines, nrows, rs);

    b->big = big;
    b->silent = silent;

    char * line = NULL;
    size_t len = 0;
    size_t read = 0;

    int stop = 0;
    int entree;

    while( read != -1 && !stop )
    {
	board_print(b);
	entree = 0;
	while(!entree) /* tant que pas d'entree correct */
	{
	    if(!silent)
		puts("\nWhat's your move? (or ? for help, h for hint, d for dump, q to quit)");

	    read = getline(&line, &len, stdin);
	    
	    if(read == 2) /* c'est peut être une commande */
	    {
		switch(line[0])
		{
		case 'd': /* dump */
		    printf("%s %d\n", b->data, b->score);
		    entree = 1;
		    break;
		case 'h': /* hint */
		    entree = 1;
		    break;
		case '?': /* help */
		    if(!silent)
			puts(HELP_MSG);
		    entree = 1;
		    break;
		case 'q': /* quit */
		    stop = 1;
		    entree = 1;
		    break;
		default:
		    if(!silent)
			fputs("Invalid command\n", stderr);
		    break;
		}
	    }
	    else if(read == 4) /* c'est peut être un coup */
	    {
		dir_t dir;

		switch(line[2])
		{
		case 'u': dir = up;  break;
		case 'd': dir = down;  break;
		case 'l': dir = left;  break;
		case 'r': dir = right;  break;
		default:
		    if(!silent)
			fprintf(stderr, "Invalid direction specifier (%c): must be one of 'u' (up), 'd' (down), 'r' (right), 'l' (left)\n\n", line[2]);
		    entree = 0;
		    continue;
		}
		
		entree = !board_move(b, line[0] - 'a', line[1] - '1', dir);
	    }
	    else
	    {
		if(!silent)
		    fputs("Invalid command\n", stderr);
	    }
	}
    }

    if (line)
	free(line);

    board_free(b);
    randseq_free(rs);


}

