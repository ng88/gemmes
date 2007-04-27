#include "board.h"
#include "assert.h"


extern void render(board_t);
extern volatile int current_frame;
extern volatile int changed;

void board_print(board_t b)
{
    (void)b;
    changed = 1;
}

