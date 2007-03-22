#include <string.h>
#include <stdlib.h>

#include "gemmes.h"


randseq_t randseq_new(int len)
{
    int i = 0;
    char * data = (char*)malloc(len + 1);

    while(i < len)
	data[i++] = 'A' + (int)((double)('Z' - 'A' + 1) * (rand() / (double)RAND_MAX));

    randseq_t ret = (randseq_t)malloc(sizeof(randseq_t));
    ret->len = len;
    ret->pos = 0;
    ret->data = data;

    return ret;
}

randseq_t randseq_new_from_str(char * seq)
{
    c_assert(seq);

    randseq_t ret = (randseq_t)malloc(sizeof(randseq_t));
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
	board_t b = (board_t)malloc(sizeof(board_t));

	b->ysize=nlines;
	b->xsize=nrows;
	strcpy(b->data,randseq_t->data);
	b->score=0;
}


void board_t_print(board_t b)
{
	int i,j;

	printf("\t\t  ");
	for(i=0;i<b->xsize;i++)
		printf("%c",'a'+i);
	printf("\n");

	printf("board:\t +");
	for(i=0;i<b->xsize;i++)
		printf("--");
	printf("+\t Score: %d",b->score);
	
	for(i=0;i<(b->ysize);i++)
	{
		printf("\t\t%d|",i);
		for(j=0;j<(b->xsize);j++)
			printf("%c ",board_pos(b,j,i));
		printf("|%d\n",i);
	}
	printf("\t\t +----------------+");
	printf("\t\t  ");
	for(i=0;i<b->xsize;i++)
		printf("%c",'a'+i);
	printf("\n");
}
