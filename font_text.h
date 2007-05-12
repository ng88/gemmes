/***************************************************************************
 *   This file is part of the 'gemmes' project                             *
 *                                                                         *
 *                                                                         *
 *   Copyright (C) 2007 by                                                 *
 *         GARCH Soufiane                                                  *
 *         GUILLAUME Nicolas <ng@ngsoft-fr.com>                            *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License only.          *
 *   See the COPYING file.                                                 *
 ***************************************************************************/



#ifndef FONT_TEXT_H
#define FONT_TEXT_H


/* Contains text fonts for text mode of the game*/



#define LETTER_SIZE_X 3
#define LETTER_SIZE_Y 3
#define LETTER_COUNT 16

#define LETTER_EXTRA 22

typedef char font_t[LETTER_COUNT][LETTER_SIZE_Y][LETTER_SIZE_X + LETTER_EXTRA];


/* big font */
font_t BIG_FONT;

/* fancy font */
font_t FANCY_FONT;

/* colored font */
font_t COLORED_FONT;

/* colored font */
font_t COLORED_FONT2;


/* Get the char (x, y) of the letter l of the font f*/
char text_font_get_char(font_t f, char l, int x, int y);

/* Get the line number y of letter l (return a null terminated string)*/
char* text_font_get_line(font_t f, char l, int y);












#endif

