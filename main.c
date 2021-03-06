/***************************************************************************
 *   This file is part of the 'gemmes' project                             *
 *                                                                         *
 *                                                                         *
 *   Copyright (C) 2007 by                                                 *
 *         GARCH Soufiane                                                  *
 *         GUILLAUME Nicolas <ng@ngsoft-fr.com>                            *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License only.          *
 *   See the COPYING file.                                                 *
 ***************************************************************************/


#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "gemmes.h"

/* compilation conditionnelle seulement utilis�e dans ce fichier */

#ifdef GEMMES_TXT /* on a de police seulement en mode texte */

#include "font_text.h"
extern font_t *  font;

#endif


void usage(const char * pname, int ev)
{
    fprintf(stderr, "usage: %s [option]\n"
	            "  Accepted options:\n"
#ifdef GEMMES_TXT
	            "   -b                        big display\n"
	            "   -f                        big display (ASCII Art)\n"
	            "   -g                        big display (colored ASCII Art, does not pretend to be fully portable.\n"
	            "                                          you can use -gg for another color disposition)\n"
#endif
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
    int ncolor = 7;
    char * s = NULL;
    int silent = 0;

    while( (optch = getopt(argc, argv, "bfghqs:x:y:c:")) != -1 )
    {
	switch(optch)
	{
#ifdef GEMMES_TXT
	case 'f':
	    font = &FANCY_FONT;
	    break;
	case 'b':
	    font = &BIG_FONT;
	    break;
	case 'g':
	    if(font == &COLORED_FONT)
		font = &COLORED_FONT2;
	    else
		font = &COLORED_FONT;
	    break;
#endif
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


    if(y <= 0 || y >= 27 || x <= 0 || x >= 27)
    {
	fprintf(stderr, "%s: invalid size, max 26x26\n", pname);
	return EXIT_FAILURE;
    }

    if((s && strlen(s) <= 2) || (!s && (ncolor <= 2 || ncolor > 16 ) ))
    {
	fprintf(stderr, "%s: invalid number of color (must be between 2 and 16)\n", pname);
	return EXIT_FAILURE;
    }

    srand(time(0));
    gemmes_start_loop(y, x, ncolor, s, silent);

    return EXIT_SUCCESS;
}
