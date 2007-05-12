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


#include "gemmes.h"


int main()
{


    randseq_t rs = randseq_new_from_str(
	"FDGECECAADGECCDEAGDBGACFCCCCCCCCCCCBCFBCFGEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	
    board_t b = board_new(8,8,rs);

    board_print(b);

    printf("%d\n", board_searchline(b,1,2,left) );
    printf("%d\n", board_searchline(b,3,4,down) );
    printf("%d\n", board_searchline(b,3,3,right) );


    rs = randseq_new_from_str(
	"FDGECECAADGECCDEAGDBGACFCCBCFBCF"
	"GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	
    b = board_new(8,8,rs);

    board_print(b);
}
