
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gemmes.h"



int main()
{
    srand(time(0));


    randseq_t fstr = randseq_new_from_str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    board_t b=board_new(9,9,fstr);

    board_print(b);

    printf("case=%c\n", board_pos(b, 5, 5));

    printf("up1=%c\n", board_neighbor(b, 5, 5, up, 1));
    printf("up2=%c\n", board_neighbor(b, 5, 5, up, 2));
    printf("up3=%c\n", board_neighbor(b, 5, 5, up, 3));

    printf("down1=%c\n", board_neighbor(b, 5, 5, down, 1));
    printf("down2=%c\n", board_neighbor(b, 5, 5, down, 2));
    printf("down3=%c\n", board_neighbor(b, 5, 5, down, 3));

    printf("left1=%c\n", board_neighbor(b, 5, 5, left, 1));
    printf("left2=%c\n", board_neighbor(b, 5, 5, left, 2));
    printf("left3=%c\n", board_neighbor(b, 5, 5, left, 3));

    printf("right1=%c\n", board_neighbor(b, 5, 5, right, 1));
    printf("right2=%c\n", board_neighbor(b, 5, 5, right, 2));
    printf("right3=%c\n", board_neighbor(b, 5, 5, right, 3));




    board_free(b);


    return EXIT_SUCCESS;
}
