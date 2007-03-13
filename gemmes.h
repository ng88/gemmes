#ifndef GEMMES_H
#define GEMMES_H


typedef struct s_randseq
{
    short len;
    short pos;
    char * data;
}* randseq_t;


randseq_t randseq_new(int len);
randseq_t randseq_new_from_str(char * seq);
void randseq_free(randseq_t rs);
char randseq_next(randseq_t rs);

#endif
