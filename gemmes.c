#include <string.h>
#include <stdlib.h>

#include "gemmes.h"
#include "assert.h"

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};

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
    c_assert(rs);

   
    board_t b = (board_t)malloc(sizeof(struct s_board));

    b->ysize = nlines;
    b->xsize = nrows;
    b->rs = rs;
    b->score=0;

    b->data = (char*)malloc(nlines * nrows);

    int i;
    for(i = 0; i < nlines * nrows; ++i)
    {
	b->data[i] = randseq_next(rs);

	int x = i % nrows;
	int y = i / nrows;

	c_assert(b->data[i] == board_pos(b, x, y));

	while(board_searchline(b, x, y, left) >= 2 || board_searchline(b, x, y, up) >= 2)
	  b->data[i] = randseq_next(rs);

    }

    return b;

/*  


   Ne fournit pas le bon resultat (cf enonce, fig1)



    int i = 1;
    char c1=randseq_next(rs), c2=randseq_next(rs), c3;

    b->data[0]=c1;
    b->data[1]=c2;
	
    while(i < nlines * nrows){
	c3=randseq_next(rs);
	if ( (c1==c2) && (c2==c3) )	{
	    //do nothing
	}else{
	    b->data[i]=c3;
	    i++;
	}	
	c1=c2;
	c2=c3;
	}*/

}


void board_print(board_t b)
{
       c_assert(b);

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
	fputs("\t\t +", stdout);
	for(i=0;i<b->xsize;i++)
		fputs("--", stdout);
	fputs("+\n\t\t  ", stdout);

	for(i=0;i<b->xsize;i++)
		printf("%c ",'a'+i);

	fputs("\n", stdout);
}

void board_free(board_t b)
{
    if(!b)
	return;

    randseq_free(b->rs);
    free(b->data);
    free(b);
}


int board_is_valid_move(board_t b, int col, int line, dir_t dir)
{
    c_assert(b);

    if(col < 0 || col >= b->xsize)
    {
	fprintf(stderr, "Invalid column specifier:   not between 'a' and '%c'\n\n", 'a' + b->xsize - 1);
	return 0;
    }

    if(line < 0 || line >= b->ysize)
    {
	fprintf(stderr, "Invalid line specifier:   not between '1' and '%d'\n\n", b->ysize);
	return 0;
    }

    int x = col + dx[dir];
    int y = line + dy[dir];

    if(x < 0 || y < 0 || x >= b->xsize || y >=  b->ysize)
    {
	fprintf(stderr, "Invalid move %c%d %s (cannot switch against the walls)\n\n", col + 'a', line + 1, dir_to_string(dir));
	return 0;
    }
    

    return 1;
}

int board_searchline(board_t b, int x, int y, dir_t dir)
{
	int cpt = 0, dist = 1;
	char current = board_pos(b,x,y);

	while(board_neighbor_valid(b, x, y, dir, dist) && current == board_neighbor(b, x, y, dir, dist)) /*je teste par rapport � le case voisine dans la direction donn�e*/
	{
	    cpt++;
	    dist++;
	}
	return cpt;
}


int board_move(board_t b, int x, int y, dir_t dir)
{
    if(!board_is_valid_move(b, x, y, dir))
	return 1;

    /* on fait l'echange */
    board_swap(b, x, y, dir);

    /* combien on a de segment maintenant ? */
    int seg_count = board_segment_count(b, x, y) + board_segment_count(b, x + dx[dir], y + dy[y]);

    if(!seg_count)
    { /* on a pas cree de segments */
	board_swap(b, x, y, dir);	/* on retablit */
	fputs("Invalid move (move leads nowhere)\n", stderr);
	return 1;
    }

    return 0;
}

void board_swap(board_t b, int x, int y, dir_t dir)
{
    char tmp = board_pos(b, x, y);
    board_pos(b, x, y) =  board_neighbor(b, x, y, dir, 1);
    board_neighbor(b, x, y, dir, 1) = tmp;
}

int board_segment_count(board_t b, int x, int y)
{
    return (board_searchline(b, x, y, up) >= 2) +
	 (board_searchline(b, x, y, down) >= 2) +
	 (board_searchline(b, x, y, left) >= 2) +
	 (board_searchline(b, x, y, right) >= 2);
}

char * dir_to_string(dir_t d)
{
    switch(d)
    {
    case up: return "up";
    case down: return "down";
    case left: return "left";
    case right: return "right";
    default: return "unknow";
    }
}





















