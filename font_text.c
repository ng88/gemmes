
#include "assert.h"
#include "font_text.h"

font_t BIG_FONT =
             {
		 {
		     "AAA",
		     "AAA",
		     "AAA",
		 },
		 {
		     "BBB",
		     "BBB",
		     "BBB",
		 },
		 {
		     "CCC",
		     "CCC",
		     "CCC",
		 },
		 {
		     "DDD",
		     "DDD",
		     "DDD",
		 },
		 {
		     "EEE",
		     "EEE",
		     "EEE",
		 },
		 {
		     "FFF",
		     "FFF",
		     "FFF",
		 },
		 {
		     "GGG",
		     "GGG",
		     "GGG",
		 },
		 {
		     "HHH",
		     "HHH",
		     "HHH",
		 },
		 {
		     "III",
		     "III",
		     "III",
		 },
		 {
		     "JJJ",
		     "JJJ",
		     "JJJ",
		 },
		 {
		     "KKK",
		     "KKK",
		     "KKK",
		 },
		 {
		     "LLL",
		     "LLL",
		     "LLL",
		 },
		 {
		     "MMM",
		     "MMM",
		     "MMM",
		 },
		 {
		     "NNN",
		     "NNN",
		     "NNN",
		 },
		 {
		     "OOO",
		     "OOO",
		     "OOO",
		 },
		 {
		     "PPP",
		     "PPP",
		     "PPP",
		 },
	     };

font_t FANCY_FONT =
             {
		 {
		     " # ",
		     "###",
		     " # ",
		 },
		 {
		     "\\ /",
		     " X ",
		     "/ \\",
		 },
		 {
		     " H ",
		     " H ",
		     " H ",
		 },
		 {
		     "   ",
		     "###",
		     "   ",
		 },
		 {
		     "@@@",
		     "@@@",
		     "@@@",
		 },
		 {
		     "o-o",
		     "|o|",
		     "o-o",
		 },
		 {
		     "~~~",
                     "~~~",
                     "~~~",
		 },
		 {
		     "   ",
		     "---",
		     "   ",
		 },
		 {
		     "  /",
		     " / ",
		     "/  ",
		 },
		 {
		     " | ",
		     "-+-",
		     " | ",
		 },
		 {
		     "...",
		     "...",
		     "...",
		 },
		 {
		     "\\  ",
		     " \\ ",
		     "  \\",
		 },
		 {
		     " # ",
		     " # ",
		     " # ",
		 },
		 {
		     " ^ ",
		     "(O)",
		     " v ",
		 },
		 {
		     "ooo",
		     "ooo",
		     "ooo",
		 },
		 {
		     "xxx",
		     "xxx",
		     "xxx",
		 },
	     };


char text_font_get_char(font_t f, int l, int x, int y)
{
    c_assert(f);
    c_assert(l >= 0 && l < LETTER_COUNT);
    c_assert(x >= 0 && x < LETTER_SIZE_X);
    c_assert(y >= 0 && y < LETTER_SIZE_Y);

    return f[l][y][x];

}

char* text_font_get_line(font_t f, int l, int y)
{
    c_assert(f);
    c_assert(l >= 0 && l < LETTER_COUNT);
    c_assert(y >= 0 && y < LETTER_SIZE_Y);

    return f[l][y];

}

