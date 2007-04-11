
#ifndef GEMMES_H
#define GEMMES_H

#include "board.h"
#include "font_text.h"

#define HELP_MSG  "Moves are on three positions:\n" \
                  " - First char specifies the column to move from\n" \
		  " - Second one specifies the line to move from\n" \
		  " - Third one specifies the direction: Up, Down, Left, Right\n" \
		  "Examples: c4u (from c4, up); d7l (from d7, left)\n\n" \
                  "The goal is to switch gems so that you get 3 or more aligned.\n"



/* demarre un nouveau jeu
 * nlines : nombre de ligne (y)
 * nrows : nombre de colonnes (x)
 * ngemmes : nombre de gemmes
 * s : chaine aléatoire, peut être NULL
 * font : police a utiliser, peut etre NULL
 * silent : si non nul, seul la commande dump affichera qqch
 */
void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, font_t * f, int silent);


/* demarre un nouveau jeu avec les options par defaut */
#define gemmes_start_loop_defaut() gemmes_start_loop(8, 8, 7, NULL, 0, 0)


/* start ihm, can be the cli, the sdl gui...*/
void gemmes_start_ihm(board_t b);


void gemmes_autoplay(board_t b);

#endif
