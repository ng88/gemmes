#include <string.h>
#include <stdlib.h>

#include "gemmes.h"
#include "assert.h"

randseq_t randseq_new(int len)
{
    int i = 0;
    char * data = (char*)malloc(len + 1);

    while(i < len)
	data[i++] = 'A' + (int)((double)('Z' - 'A' + 1) * (rand() / (double)RAND_MAX));

    randseq_t ret = (randseq_t)malloc(sizeof(struct s_randseq));
    ret->len = len;
    ret->pos = 0;
    ret->data = data;

    return ret;
}

randseq_t randseq_new_from_str(char * seq)
{
    c_assert(seq);

    randseq_t ret = (randseq_t)malloc(sizeof(struct s_randseq));
    ret->len = strlen(seq);
    ret->pos = 0;
    ret->data = strdup(seq);

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

board_t board_new(int nlines, int nrows, randseq_t rs)
{
        int i;
        board_t b = (board_t)malloc(sizeof(struct s_board));

	b->ysize=nlines;
	b->xsize=nrows;
	b->rs = rs;
	b->score=0;

	b->data = (char*)malloc(nlines * nrows);
	for(i = 0; i < nlines * nrows; ++i)
	    b->data[i] = randseq_next(rs);
	
	return b;
}


void board_print(board_t b)
{
	int i,j;

	printf("\t\t  ");
	for(i=0;i<b->xsize;i++)
		printf("%c ",'a'+i);

	fputs("\nboard:\t\t +", stdout);
	for(i=0;i<b->xsize;i++)
		fputs("--", stdout);
	printf("+\t Score: %d\n",b->score);

	for(i=0;i<(b->ysize);i++)
	{
		printf("\t\t%d|",i+1);
		for(j=0;j<(b->xsize);j++)
			printf("%c ",board_pos(b,j,i));
		printf("|%d\n",i+1);
	}
	fputs("\t\t +----------------+\n\t\t  ", stdout);
	for(i=0;i<b->xsize;i++)
		printf("%c ",'a'+i);

	fputs("\n", stdout);
}

void board_free(board_t b)
{
    randseq_free(b->rs);
    free(b->data);
    free(b);
}
