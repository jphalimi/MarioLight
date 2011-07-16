CC=gcc
CFLAGS=`sdl-config --cflags` `sdl-config --libs` -g -Wall -Wextra -O3
EXE=marioLight
SRC=main.c toolkit/linklist.c toolkit/log.c game/rendering/rendering.c game/config/config.c game/character/character.c

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(SRC) -o $(EXE) $(CFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf *.o
