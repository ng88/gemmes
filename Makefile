
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

CC=gcc
CFLAGS=-W -Wall  $(DEBUGFLAGS) $(ASSERTFLAGS)

ifdef SDL
    SRC=$(wildcard *.c)
else
    SRC=gemmes.c main_text.c board.c randseq.c font_text.c
endif

OBJS= $(SRC:.c=.o)

EXE=gemmes

all: $(EXE)

gemmes.o: gemmes.h assert.h
main_text.o: gemmes.h
board.o: board.h assert.h
randseq.o: randseq.h assert.h
font_text.o: font_text.h assert.h

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)



.PHONY: clean 

clean:
	@rm -f *.o *~ core *.core core.* *.tmp

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


