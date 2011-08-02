//
//  main.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "toolkit/log.h"
#include "game/game.h"

int main (int argc, char *argv[])
{
	/* Game structure creation */
	SGame *game = Game_create ();
	
	/* Log setup */
	Log_setOutput(stderr);
	Log_setVerbosity(3);
	
	/* Game is starting right now */
	Game_launch (game);
	
	/* Quit and freeing everything else */
	Game_destroy (game);
	
	(void) argc;
	(void) argv;
	return EXIT_SUCCESS;
}

