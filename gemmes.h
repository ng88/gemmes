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



#ifndef GEMMES_H
#define GEMMES_H

#include "board.h"

/* Nombre d'essai maximum lors de la cr�ation d'un plateau */
#define MAX_TRY_COUNT 100

/* demarre un nouveau jeu
 * nlines : nombre de ligne (y)
 * nrows : nombre de colonnes (x)
 * ngemmes : nombre de gemmes
 * s : chaine al�atoire, peut �tre NULL
 * silent : si non nul, seul la commande dump affichera qqch
 */
void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, int silent);


/* demarre un nouveau jeu avec les options par defaut */
#define gemmes_start_loop_defaut() gemmes_start_loop(8, 8, 7, NULL, 0)


/* start ihm, can be the cli, the sdl gui...*/
void gemmes_start_ihm(board_t b);

void gemmes_dump(board_t b);

/* Autoplay  */
void gemmes_autoplay(board_t b);

/* Autoplay & create a test file on stdout */
void gemmes_autoplay_createtest(board_t b);

#endif
