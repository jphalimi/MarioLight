CC=gcc
CLIBS=`sdl-config --libs` -lSDL_image
CFLAGS=`sdl-config --cflags` -g -Wall -Wextra -O3
EXE=marioLight

# Paths to sources
TOOLKIT_PATH=toolkit
RENDERING_PATH=game/rendering
CONFIG_PATH=game/config
CHARACTER_PATH=game/character
TIME_PATH=game/time

SRCDIRS=toolkit game/rendering game/config game/character game/time .
SRC=$(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))
HEADERS=$(foreach d,$(SRCDIRS),$(wildcard $(d)/*.h))
OBJ=$(wildcard *.o)

all: $(EXE)

$(EXE): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $@ $(CFLAGS) $(CLIBS)

clean:
	rm -rf $(EXE)
	rm -rf *.o

count:
	wc -l `find . -iname "*.[ch]"`