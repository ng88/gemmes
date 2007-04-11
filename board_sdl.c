#include "board.h"
#include "assert.h"


extern void render(board_t);

void board_print(board_t b)
{
    render(b);
}

