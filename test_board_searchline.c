#include "gemmes.h"


int main()
{


    randseq_t rs = randseq_new_from_str(
	"FDGECECAADGECCDEAGDBGACFCCCCCCCCCCCBCFBCFGEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	
    board_t b = board_new(8,8,rs);

    board_print(b);

    printf("%d\n", board_searchline(b,1,2,left) );
    printf("%d\n", board_searchline(b,3,4,down) );
    printf("%d\n", board_searchline(b,3,3,right) );


    rs = randseq_new_from_str(
	"FDGECECAADGECCDEAGDBGACFCCBCFBCF"
	"GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	
    b = board_new(8,8,rs);

    board_print(b);
}
