#include "gemmes.h"


int main()
{


    randseq_t rs = randseq_new_from_str(
	"FDGECECAADGECCCCCCCCCCCCCCCCCCCCCCCDEAGDBGACFCCBCFBCF"
	"GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB"
	);
	
    board_t b = board_new(8,8,rs);

	printf("%d",board_searchline(b,'b',5,down));
}//normalement ca devrai marcher
