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


#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "randseq.h"
#include "assert.h"


randseq_t randseq_new(int len, int diff)
{
    c_assert(len > 0 && diff > 0 && diff <= ('Z' - 'A'));

    int i = 0;
    char * data = (char*)malloc(len + 1);

    c_assert2(data, "malloc failed");

    while(i < len)
	data[i++] = 'A' + (int)((double)diff * (rand() / (double)RAND_MAX));

    data[len] = '\0';

    randseq_t ret = (randseq_t)malloc(sizeof(struct s_randseq));

    c_assert2(ret, "malloc failed");

    ret->len = len;
    ret->pos = 0;
    ret->data = data;
    ret->ncolor = diff;

    return ret;
}

randseq_t randseq_new_from_str(char * seq)
{
    c_assert(seq);

    randseq_t ret = (randseq_t)malloc(sizeof(struct s_randseq));

    c_assert2(ret, "malloc failed");

    ret->len = strlen(seq);
    ret->pos = 0;
    ret->data = strdup(seq);

    c_assert2(ret->data, "strdup failed");

    ret->ncolor = 0;

    /* on calcule le nombre de gemme différentes */
    int i;
    for(i = 0; i < ret->len; ++i)
    {
	ret->data[i] = toupper(ret->data[i]);
	if(ret->data[i] - 'A' + 1 > ret->ncolor)
	    ret->ncolor = ret->data[i] - 'A' + 1;
    }

    if(ret->ncolor > 16)
    {
	randseq_free(ret);
	return NULL;
    }

    return ret;
}

void randseq_free(randseq_t rs)
{
    c_assert(rs);

    free(rs->data);
	
    free(rs);
}

char randseq_next(randseq_t rs)
{
    c_assert(rs && rs->data);

    char ret = rs->data[rs->pos++];

    if(rs->pos == rs->len)
	rs->pos = 0;

    return ret;
}





















