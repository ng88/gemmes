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

#define board_pos(b, x, y) ((b)->data[(y) - 1 + (x)*((b)->ysize)])

#define board_neighbor(b, x, y, dir, dist) \
              board_pos((b), (x) + dx[(dir)] * (dist), (y) + dy[(dir)] * (dist))

typedef enum { up=0, down=1, left=2, right=3 } dir_t;

const int dx[4];
const int dy[4];

typedef struct s_board
{
    randseq_t rs;
	int xsize;
	int ysize;
	char *data;
	int score;
}* board_t;

board_t board_new(int nlines, int nrows, randseq_t rs);
void board_print(board_t b);

/** free the b->data, b->rs & b */
void board_free(board_t b);

int board_is_valid_move(board_t b, char *blow);

int board_searchline(board_t, int x, int y, dir_t dir);

#endif
