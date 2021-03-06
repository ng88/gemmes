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


font_t COLORED_FONT =
             {
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },

	     };



font_t COLORED_FONT2 =
             {
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '5',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '6',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '1',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '2',';', '4', '0', 'm', ' ', '@', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', '#', '#', '#',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '3',';', '4', '0', 'm', ' ', '#', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },
		 {
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '\\', ' ', '/',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', ' ', 'x', ' ',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		     {0x1B ,'[', '1',';', '3', '4',';', '4', '0', 'm', '/', ' ', '\\',  0x1B ,'[', '0',';', '3', '7',';', '4', '0', 'm',  '\0'},
		 },


	     };



char text_font_get_char(font_t f, char l, int x, int y)
{
    c_assert(f);
    c_assert(l >= 'A' && l < 'A' + LETTER_COUNT);
    c_assert(x >= 0 && x < LETTER_SIZE_X);
    c_assert(y >= 0 && y < LETTER_SIZE_Y);

    return f[l - 'A'][y][x];

}

char* text_font_get_line(font_t f, char l, int y)
{
    c_assert(f);
    c_assert(l >= 'A' && l < 'A' + LETTER_COUNT);
    c_assert(y >= 0 && y < LETTER_SIZE_Y);

    return f[l - 'A'][y];

}

