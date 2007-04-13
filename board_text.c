#include "board.h"
#include "assert.h"
#include "font_text.h"

font_t * font = NULL;

/* print the board with small letters */
void board_print_small(board_t b);

/* print the board with big letters using font f */
void board_print_big(board_t b);


void board_print(board_t b)
{
    c_assert(b);

    if(b->silent)
	return;

    if(font)
	board_print_big(b);
    else
	board_print_small(b);

}

void board_print_big(board_t b)
{
    int x, y;

    fputs("\nBoard:  +", stdout);
    for(x = 0; x < b->xsize; ++x)
	printf("-%c-+", 'a' + x);

    printf("       Score: %d\n", b->score);

    for(y = 0; y < b->ysize; ++y)
    {
	int i;

	for(i = 0; i < 3; ++i)
	{
	    if(i == 1)
		printf("     %2d |", y + 1);
	    else
		fputs("        |", stdout);
	    for(x = 0; x < b->xsize; ++x)
	    {
		char c = board_pos(b, x, y);
		if(c == ' ')
		    fputs("   ", stdout);
		else
		    fputs(text_font_get_line(*font, c, i), stdout);
		putchar('|');
	    }
	    if(i == 1)
		printf(" %d", y + 1);
	    putchar('\n');
	}

	fputs("        +", stdout);
	for(x = 0; x < b->xsize; ++x)
	    printf("-%c-+", 'a' + x);
	putchar('\n');
    }

    putchar('\n');

}

void board_print_small(board_t b)
{

	int i,j;

	printf("\t\t   ");
	for(i=0;i<b->xsize;i++)
		printf("%c ",'a'+i);

	fputs("\nBoard:\t\t  +", stdout);
	for(i=0;i<b->xsize;i++)
		fputs("--", stdout);
	printf("+\t Score: %d\n",b->score);

	for(i=0;i<(b->ysize);i++)
	{
		printf("\t\t%2d|",i+1);
		for(j=0;j<(b->xsize);j++)
			printf("%c ",board_pos(b,j,i));
		printf("|%d\n",i+1);
	}
	fputs("\t\t  +", stdout);
	for(i=0;i<b->xsize;i++)
		fputs("--", stdout);
	fputs("+\n\t\t   ", stdout);

	for(i=0;i<b->xsize;i++)
		printf("%c ",'a'+i);

	fputs("\n", stdout);
}
