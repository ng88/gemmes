#include "gemmes.h"
int main() {
   randseq_t rs = randseq_new_from_str(
    "FDGECECAADGECCDEAGDBGACFCCBCFBCF"
    "GEDBFDEAEEDBEDEGDFBCBECGDABGFAEB");
   board_t b = board_new(8,8,rs);
   board_print(b);
   return 0;
}
