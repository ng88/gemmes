
ifdef DEBUG
    DEBUGFLAGS=-g -ggdb -dH -D_DEBUG_=1
else
    DEBUGFLAGS=
endif

ifdef NOASSERT
    ASSERTFLAGS=-DDISABLE_ASSERT=1
else
    ASSERTFLAGS=
endif

ifdef SDL
    IHM_FILES=gemmes_sdl.c board_sdl.c
    IHMFLAGS=`sdl-config --cflags`
    LDFLAGS=`sdl-config --libs` -lSDLmain -lSDL
else
    IHM_FILES=gemmes_text.c board_text.c
    IHMFLAGS=
    LDFLAGS=
endif

CC=gcc
CFLAGS=-W -Wall  $(DEBUGFLAGS) $(ASSERTFLAGS) $(IHMFLAGS)
SRC=gemmes.c main.c board.c randseq.c font_text.c $(IHM_FILES)
OBJS= $(SRC:.c=.o)
EXE=gemmes

all: $(EXE)

gemmes.o: gemmes.h assert.h
gemmes_text.o: gemmes.h assert.h
gemmes_sdl.o: gemmes.h assert.h
main.o: gemmes.h
board.o: board.h assert.h
board_text.o: board.h assert.h
board_sdl.o: board.h assert.h
randseq.o: randseq.h assert.h
font_text.o: font_text.h assert.h

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)



.PHONY: clean 

clean:
	@rm -f *.o *~ core *.core core.* *.tmp

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


