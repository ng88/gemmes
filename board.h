#ifndef BOARD_H
#define BOARD_H

#include "randseq.h"


typedef enum { up=0, down=1, left=2, right=3 } dir_t;

const int dx[4];
const int dy[4];

typedef struct s_board
{
    randseq_t rs;
    int xsize;
    int ysize;
    char *data;
    unsigned int score;

    int silent;

    int last_seg_count;

}* board_t;

typedef struct s_coord
{
    int x;
    int y;
    dir_t d;
} coord_t;

/* get the gemmes at (x, y) */
#define board_pos(b, x, y) ((b)->data[(y) + (x)*((b)->ysize)])

#define board_neighbor(b, x, y, dir, dist) \
              board_pos((b), (x) + dx[(dir)] * (dist), (y) + dy[(dir)] * (dist))

/* get the x coord of the gemme which have i as index */
#define board_index_to_x(b, i) ((i) / (b)->ysize)

/* get the y coord of the gemme which have i as index */
#define board_index_to_y(b, i) ((i) % (b)->ysize)

/* return non-zero is this is a valid pos */
#define board_neighbor_valid(b, x, y, dir, dist) \
                (((x) + dx[(dir)] * (dist)) >= 0 && ((x) + dx[(dir)] * (dist)) < b->xsize && \
                ((y) + dy[(dir)] * (dist)) >= 0 && ((y) + dy[(dir)] * (dist)) < b->ysize)


/* only alloc a new board, does not initialize gemmes */
board_t board_alloc(int nlines, int nrows, randseq_t rs);

/* alloc a new board and initializes it */
board_t board_new(int nlines, int nrows, randseq_t rs);


/* print the board */
void board_print(board_t b);


/** do not free rs */
void board_free(board_t b);

int board_is_valid_move(board_t b, int x, int y, dir_t dir);

int board_searchline(board_t, int x, int y, dir_t dir);

/* return 1 if an error occurs */
int board_move(board_t b, int x, int y, dir_t dir);

/* swap gemme (x, y) with its neighbor in direction dir*/
void board_swap(board_t b, int x, int y, dir_t dir);

/* return the segment count around (x, y) */
int board_segment_count(board_t b, int x, int y);

/* update the board (remove the segments etc) */
#define board_update(b) board_update_helper((b), 1, 0)

/* used by board_update()
 * multiple_seg: score coefficient
 * sed_count: segment count
 */
void board_update_helper(board_t b,  unsigned int multiple_seg,  unsigned int seg_count);

/* return a hint, return (-1, -1, *) if no more move is possible*/
coord_t board_get_hint(board_t b);

/* returns "left" for left, "right", for right etc*/
char * dir_to_string(dir_t d);




#endif
