
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gemmes.h"



int main()
{
    srand(time(0));


    randseq_t fstr = randseq_new_from_str("AADBVCDVDDEFVGJHMIJKLMOPDJHJSDH"
					  "KQSDdfHPLNBNAESTYUIXPOIQKHUAYEV");

    board_t b=board_new(8,8,fstr);

    board_print(b);

    printf("up=%c\n", board_neighbor(b, 5, 5, up, 1));

    board_free(b);


    return EXIT_SUCCESS;
}
