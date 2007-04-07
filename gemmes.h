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

/* get the gemmes at (x, y) */
#define board_pos(b, x, y) ((b)->data[(x) + (y)*((b)->ysize)])

#define board_neighbor(b, x, y, dir, dist) \
              board_pos((b), (x) + dx[(dir)] * (dist), (y) + dy[(dir)] * (dist))

/* return non-zero is this is a valid pos */
#define board_neighbor_valid(b, x, y, dir, dist) \
                (((x) + dx[(dir)] * (dist)) >= 0 && ((x) + dx[(dir)] * (dist)) < b->xsize && \
                ((y) + dy[(dir)] * (dist)) >= 0 && ((y) + dy[(dir)] * (dist)) < b->ysize)
              

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

int board_is_valid_move(board_t b, int x, int y, dir_t dir);

int board_searchline(board_t, int x, int y, dir_t dir);

/* return 1 if an error occurs */
int board_move(board_t b, int x, int y, dir_t dir);

/* swap gemme (x, y) with its neighbor in direction dir*/
void board_swap(board_t b, int x, int y, dir_t dir);

/* return the segment count around (x, y) */
int board_segment_count(board_t b, int x, int y);

/* returns "left" for left, "right", for right etc*/
char * dir_to_string(dir_t d);



#endif
