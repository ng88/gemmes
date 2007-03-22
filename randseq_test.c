
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gemmes.h"



int main()
{
    srand(time(0));

    randseq_t alea = randseq_new(5);
    randseq_t alea2 = randseq_new(5000);

    randseq_t fstr = randseq_new_from_str("ABCDE");


    int i;
    for(i = 0; i < 10; ++i)
	putchar(randseq_next(alea));

    putchar('\n');


    for(i = 0; i < 10; ++i)
	putchar(randseq_next(fstr));

    putchar('\n');

    for(i = 0; i < 5000; ++i)
	putchar(randseq_next(alea2));

    putchar('\n');

    board_t b=board_new(8,8,fstr);

    board_t_print(b);


    randseq_free(alea2);
    randseq_free(alea);
    randseq_free(fstr);


    return EXIT_SUCCESS;
}
