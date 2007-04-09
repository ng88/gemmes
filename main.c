#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "gemmes.h"


void usage(const char * pname, int ev)
{
    fprintf(stderr, "usage: %s [option]\n"
	            "  Accepted options:\n"
	            "   -b                        big display\n"
	            "   -h                        print this help string\n"
	            "   -q                        quiet, only the dump command will display something\n"
                    "   -s randseq                use randseq as random sequence\n"
                    "   -x <number>, -y <number>  change the board dimensions\n"
                    "   -c <number>               change amount of colors\n"
		    , pname);
    exit(ev);
}

int main(int argc, char ** argv)
{
    char * pname = strrchr(argv[0], '/');
    if( !pname )
        pname = argv[0];
    else
	pname++;

    int optch;

    int x = 8;
    int y = 8;
    int ncolor = 8;
    char * s = NULL;
    int big = 0;
    int silent = 0;

    while( (optch = getopt(argc, argv, "bhqs:x:y:c:")) != -1 )
    {
	switch(optch)
	{
	case 'b':
	    big = 1;
	    break;
	case 'h':
	    usage(pname, EXIT_SUCCESS);
	    break;
	case 'q':
	    silent = 1;
	    break;
	case 's':
	    s = optarg;
	    break;
	case 'x':
	    x = atoi(optarg);
	    break;
	case 'y':
	    y = atoi(optarg);
	    break;
	case 'c':
	    ncolor = atoi(optarg);
	    break;
	default:
	    usage(pname, EXIT_FAILURE);
	    break;
	}
    }

    if(argc - optind)
	usage(pname, EXIT_FAILURE);

    if(y <= 0 || y >= 10 || x <= 0 || x >= 27)
    {
	fprintf(stderr, "%s: invalid size", pname);
	return EXIT_FAILURE;
    }

    if((s && strlen(s) <= 2) || (!s && ncolor <= 2))
    {
	fprintf(stderr, "%s: invalid number of color (<= 2)", pname);
	return EXIT_FAILURE;
    }

    gemmes_start_loop(y, x, ncolor, s, big, silent);

    return EXIT_SUCCESS;
}
