
ifdef DEBUG
    DEBUGFLAGS=-g -ggdb -dH -D_DEBUG_=1
    STRIP=@echo
else
    DEBUGFLAGS=
    STRIP=strip
endif

ifdef NOASSERT
    ASSERTFLAGS=-DDISABLE_ASSERT=1
else
    ASSERTFLAGS=
endif

ifdef SDL
    IHM_FILES=gemmes_sdl.c board_sdl.c sdl_draw.c
    IHMFLAGS=`sdl-config --cflags` -DGEMMES_SDL=1
    LDFLAGS=`sdl-config --libs`
else
    IHM_FILES=gemmes_text.c board_text.c font_text.c
    IHMFLAGS=-DGEMMES_TXT=1
    LDFLAGS=
endif

ifdef WIN_PORT
    WIN_FILES=win_port.c
    SYSFLAGS=-DG_WINDOWS
else
    WIN_FILES=
    SYSFLAGS=-DG_LINUX
endif

CC=gcc
CFLAGS=-W -Wall  $(DEBUGFLAGS) $(ASSERTFLAGS) $(IHMFLAGS) $(SYSFLAGS)
SRC=gemmes.c main.c board.c randseq.c $(IHM_FILES) $(WIN_FILES)
OBJS= $(SRC:.c=.o)
EXE=gemmes

all: $(EXE)

gemmes.o: gemmes.h assert.h
gemmes_text.o: gemmes.h assert.h
gemmes_sdl.o: gemmes.h assert.h sdl_draw.h
main.o: gemmes.h
board.o: board.h assert.h
board_text.o: board.h assert.h
board_sdl.o: board.h assert.h
randseq.o: randseq.h assert.h
font_text.o: font_text.h assert.h
sdl_draw.o: sdl_draw.h

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@ > /dev/null
	@echo Done.



.PHONY: clean sdl mrproper

clean:
	@rm -f *.o *~ core *.core core.* *.tmp

mrproper: clean
	@rm -f gemmes xgemmes

sdl:
	@$(MAKE) SDL=1

both:
	@$(MAKE) clean
	@$(MAKE) SDL=1
	@mv $(EXE) x$(EXE)
	@$(MAKE) clean
	@$(MAKE)
	@echo 'Text & SDL version built.'

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


