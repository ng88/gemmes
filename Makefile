gemmes : game.o gemmes.o
	gcc -o gemmes game.o gemmes.o

gemmes.o : gemmes.c gemmes.h
	gcc -c gemmes.c
game.o : game.c
	gcc -c game.c