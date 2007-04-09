#ifndef RANDSEQ_H
#define RANDSEQ_H


typedef struct s_randseq
{
    short len;
    short pos;
    char * data;
}* randseq_t;

/* len: seq length
 * diff: number of different item in the sequence
 */
randseq_t randseq_new(int len, int diff);
randseq_t randseq_new_from_str(char * seq);
void randseq_free(randseq_t rs);
char randseq_next(randseq_t rs);


#endif
