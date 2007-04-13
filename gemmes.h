
#ifndef GEMMES_H
#define GEMMES_H

#include "board.h"



/* demarre un nouveau jeu
 * nlines : nombre de ligne (y)
 * nrows : nombre de colonnes (x)
 * ngemmes : nombre de gemmes
 * s : chaine aléatoire, peut être NULL
 * font : police a utiliser, peut etre NULL
 * silent : si non nul, seul la commande dump affichera qqch
 */
void gemmes_start_loop(int nlines, int nrows, int ngemmes, char * s, int silent);


/* demarre un nouveau jeu avec les options par defaut */
#define gemmes_start_loop_defaut() gemmes_start_loop(8, 8, 7, NULL, 0)


/* start ihm, can be the cli, the sdl gui...*/
void gemmes_start_ihm(board_t b);

void gemmes_dump(board_t b);

void gemmes_autoplay(board_t b);

#endif
