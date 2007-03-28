#include "gemmes.h"

int main() {
	randseq_t rs = randseq_new_from_str(
    "FDGECECAADGECCDEAGDBGACFCCBCFBCF"
    "GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB");
	
	int choix=0;
	char move[4];

	board_t b = board_new(8,8,rs);

	while(choix!=2)
	{
		board_print(b);
		puts("Donner un mouvement : ");
		fgets(move,4,stdin);
		choix=board_move_s(b,move);
		if (choix==0) puts("good move");
		else puts("bad move");
	}
	return 0;
}
