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

    int i = 1;
	board_t b = (board_t)malloc(sizeof(struct s_board));

	b->ysize=nlines;
	b->xsize=nrows;
	b->rs = rs;
	b->score=0;

	char c1=randseq_next(rs), c2=randseq_next(rs), c3;

	b->data = (char*)malloc(nlines * nrows);

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
	}
/*
	for(i = 0; i < nlines * nrows; ++i)
	    b->data[i] = randseq_next(rs);
*/	
	return b;
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


int board_is_valid_move(board_t b, char * cmd)
{
    c_assert(strlen(cmd) == 4 && b);

    int col = cmd[0] - 'a';
    int line = cmd[1] - '1';
    dir_t dir;

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

    switch(cmd[2])
    {
    case 'u': dir = up;  break;
    case 'd': dir = down;  break;
    case 'l': dir = left;  break;
    case 'r': dir = right;  break;
    default:
	fprintf(stderr, "Invalid direction specifier (%c): must be one of 'u' (up), 'd' (down), 'r' (right), 'l' (left)\n\n", cmd[2]);
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

	while(board_neighbor_valid(b, x, y, dir, dist) && current == board_neighbor(b, x, y, dir, dist)) /*je teste par rapport à le case voisine dans la direction donnée*/
	{
	    cpt++;
	    dist++;
	}
	return cpt;
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





















