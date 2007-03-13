
#include <string.h>
#include <stdlib.h>

#include "gemmes.h"
#include "assert.h"


randseq_t randseq_new(int len)
{
    int i = 0;
    char * data = (char*)malloc(len + 1);

    while(i < len)
    {
	data[i++] = 'A' + (int)((double)('Z' - 'A' + 1) * (rand() / (double)RAND_MAX));



    }

    return randseq_new_from_str(data);
}

randseq_t randseq_new_from_str(char * seq)
{
    c_assert(seq);

    randseq_t ret = (randseq_t)malloc(sizeof(randseq_t));
    ret->len = strlen(seq);
    ret->pos = 0;
    ret->data = strdup(seq);

    return ret;
}

void randseq_free(randseq_t rs)
{
    c_assert(rs);

    free(rs->data);
    free(rs);
}

char randseq_next(randseq_t rs)
{
    c_assert(rs && rs->data);

    char ret = rs->data[rs->pos++];

    if(rs->pos == rs->len)
	rs->pos = 0;

    return ret;
}
