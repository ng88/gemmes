#include <stdlib.h>

#include "gemmes.h"


int main(int argc, char ** argv)
{
    start_game_loop(8, 8, 0, 
		    "FDGECECAADGECCDEAGDBGACFCCBCFBCF"
		    "GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
		    ,0 , 1);

    return EXIT_SUCCESS;
}