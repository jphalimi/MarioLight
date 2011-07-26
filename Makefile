all: marioLight

toolkit/linklist.o: toolkit/linklist.c
	gcc toolkit/linklist.c -c -o toolkit/linklist.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

toolkit/log.o: toolkit/log.c
	gcc toolkit/log.c -c -o toolkit/log.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/rendering/rendering.o: game/rendering/rendering.c
	gcc game/rendering/rendering.c -c -o game/rendering/rendering.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/config/config.o: game/config/config.c
	gcc game/config/config.c -c -o game/config/config.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/character/character.o: game/character/character.c
	gcc game/character/character.c -c -o game/character/character.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/character/character_state.o: game/character/character_state.c
	gcc game/character/character_state.c -c -o game/character/character_state.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/character/states_handlers.o: game/character/states_handlers.c
	gcc game/character/states_handlers.c -c -o game/character/states_handlers.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

game/time/time.o: game/time/time.c
	gcc game/time/time.c -c -o game/time/time.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

./main.o: ./main.c
	gcc ./main.c -c -o ./main.o -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g

marioLight:  toolkit/linklist.o toolkit/log.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/time/time.o ./main.o
	gcc  toolkit/linklist.o toolkit/log.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/time/time.o ./main.o -o marioLight -Wall -Wextra -O3 -I/opt/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -g -L/opt/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -lSDL_image
clean:
	rm -rf  toolkit/linklist.o toolkit/log.o game/rendering/rendering.o game/config/config.o game/character/character.o game/character/character_state.o game/character/states_handlers.o game/time/time.o ./main.o marioLight
