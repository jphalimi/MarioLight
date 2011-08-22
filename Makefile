all: marioLight

toolkit/linklist.o: toolkit/linklist.c
	gcc toolkit/linklist.c -c -o toolkit/linklist.o -Wall -Wextra -O3 `sdl-config --cflags` -g

toolkit/log.o: toolkit/log.c
	gcc toolkit/log.c -c -o toolkit/log.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/game.o: game/game.c
	gcc game/game.c -c -o game/game.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/rendering/rendering.o: game/rendering/rendering.c
	gcc game/rendering/rendering.c -c -o game/rendering/rendering.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/config/config.o: game/config/config.c
	gcc game/config/config.c -c -o game/config/config.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/character/character.o: game/character/character.c
	gcc game/character/character.c -c -o game/character/character.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/character/character_state.o: game/character/character_state.c
	gcc game/character/character_state.c -c -o game/character/character_state.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/character/states_handlers.o: game/character/states_handlers.c
	gcc game/character/states_handlers.c -c -o game/character/states_handlers.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/object/object.o: game/object/object.c
	gcc game/object/object.c -c -o game/object/object.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/object/object_state.o: game/object/object_state.c
	gcc game/object/object_state.c -c -o game/object/object_state.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/object/states_handlers.o: game/object/states_handlers.c
	gcc game/object/states_handlers.c -c -o game/object/states_handlers.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/time/time.o: game/time/time.c
	gcc game/time/time.c -c -o game/time/time.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/input/input.o: game/input/input.c
	gcc game/input/input.c -c -o game/input/input.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/level/level.o: game/level/level.c
	gcc game/level/level.c -c -o game/level/level.o -Wall -Wextra -O3 `sdl-config --cflags` -g

game/level/levelstate.o: game/level/levelstate.c
	gcc game/level/levelstate.c -c -o game/level/levelstate.o -Wall -Wextra -O3 `sdl-config --cflags` -g

./main.o: ./main.c
	gcc ./main.c -c -o ./main.o -Wall -Wextra -O3 `sdl-config --cflags` -g

marioLight:  toolkit/linklist.o toolkit/log.o game/game.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/object/object.o game/object/object_state.o game/object/states_handlers.o game/time/time.o game/input/input.o game/level/level.o game/level/levelstate.o ./main.o
	gcc  toolkit/linklist.o toolkit/log.o game/game.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/object/object.o game/object/object_state.o game/object/states_handlers.o game/time/time.o game/input/input.o game/level/level.o game/level/levelstate.o ./main.o -o marioLight -Wall -Wextra -O3 `sdl-config --cflags` -g `sdl-config --libs` -lSDL_image

count:
	@echo "Project count :"
	@wc -l `find . -iname "*.[ch]"`

clean:
	rm -rf  toolkit/linklist.o toolkit/log.o game/game.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/object/object.o game/object/object_state.o game/object/states_handlers.o game/time/time.o game/input/input.o game/level/level.o game/level/levelstate.o ./main.o marioLight
	@./generate.sh
