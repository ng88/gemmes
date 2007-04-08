#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>


#include "gemmes.h"


int main() {


    randseq_t rs = randseq_new_from_str(
	"FDGECECAADGECCDEAGDBGACFCCBCFBCF"
	"GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	

    
    board_t b = board_new(8,8,rs);

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
	    puts("\nWhat's your move? (or ? for help, h for hint, d for dump, q to quit)");
	    read = getline(&line, &len, stdin);
	    
	    if(read == 2) /* c'est peut être une commande */
	    {
		switch(line[0])
		{
		case 'd': /* dump */
		    entree = 1;
		    break;
		case 'h': /* hint */
		    entree = 1;
		    break;
		case '?': /* help */
		    entree = 1;
		    break;
		case 'q': /* quit */
		    stop = 1;
		    entree = 1;
		    break;
		default:
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
		    fprintf(stderr, "Invalid direction specifier (%c): must be one of 'u' (up), 'd' (down), 'r' (right), 'l' (left)\n\n", line[2]);
		    entree = 0;
		    continue;
		}
		
		entree = !board_move(b, line[0] - 'a', line[1] - '1', dir);
	    }
	    else
	    {
		fputs("Invalid command\n", stderr);
	    }
	}
    }

    if (line)
	free(line);

    board_free(b);
    randseq_free(rs);

    return EXIT_SUCCESS;
}
