gemmes : game.o gemmes.o
	gcc -Wall -o gemmes game.o gemmes.o

gemmes.o : gemmes.c gemmes.h
	gcc -Wall -c gemmes.c
game.o : game.c
	gcc -Wall -c game.c