#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"

#include "gemmes.h"




void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, int big, int silent)
{

    c_assert(nlines > 0 && nlines < 10 && nrows > 0 && nrows < 27);
    c_assert( (s && strlen(s) > 2) || (!s && ngemmes > 2) );

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

	if(!silent && b->last_seg_count)
	    printf("This move created %d segment(s).\n", b->last_seg_count);

	entree = 0;
	while(!entree) /* tant que pas d'entree correct */
	{
	    if(!silent)
		puts("\nWhat's your move? (or ? for help, h for hint, d for dump, q to quit)");

	    read = getline(&line, &len, stdin); /* une ligne peut contenir plusieurs commandes */

	    char * cmd = line;
	    int i;
	    for(i = 0; i < read; ++i)
	    {
		if(line[i] == ' ' || i == read - 1)
		{
		    entree = gemmes_process_command(b, cmd, line + i - cmd, &stop);

		    if(i + 1 < read)
			cmd = line + i + 1;

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
    else if(read == 1) /* c'est peut �tre une commande */
    {
	switch(line[0])
	{
	case 'd': /* dump */
	    printf("%s %d\n", b->data, b->score);
	    return 1;
	case 'h': /* hint */
	    return 1;
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
    else if(read == 3) /* c'est peut �tre un coup */
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
		
	return !board_move(b, line[0] - 'a', line[1] - '1', dir);

    }
    else
    {
	if(!b->silent)
	    fputs("Invalid command\n", stderr);
	return 0;
    }
}

