game : game.o gemmes.o
	gcc -o game game.o gemmes.o

gemmes.o : gemmes.c
	gcc -c gemmes.c
game.o : game.c
	gcc -c game.c