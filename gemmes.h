#ifndef GEMMES_H
#define GEMMES_H


typedef struct s_randseq
{
    short len;
    short pos;
    char * data;
}* randseq_t;


randseq_t randseq_new(int len);
randseq_t randseq_new_from_str(char * seq);
void randseq_free(randseq_t rs);
char randseq_next(randseq_t rs);

#define board_pos(b, x, y) ((b)->data[(y) + (x)*ysize])

enum dir_t { up=0, down=1, left=2, right=3 };

const int dx[4], dy[4];

typedef struct board
{
	int xsize;
	int ysize;
	char *data;
	int score;
}* board_t;

board_t board_new(int nlines, int nrows, randseq_t rs);
void board_t_print(board_t b);


#endif
