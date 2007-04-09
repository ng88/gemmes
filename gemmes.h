
#ifndef GEMMES_H
#define GEMMES_H



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
 * big : si non nul l'affichage gros est activé
 * silent : si non nul, seul la commande dump affichera qqch
 */
void start_game_loop(int nlines, int nrows, int ngemmes, char * s, int big, int silent);


/* demarre un nouveau jeu avec les options par defaut */
#define start_game_loop_defaut() start_game_loop(8, 8, 8, NULL, 0, 0)


#endif
