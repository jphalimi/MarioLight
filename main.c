//
//  main.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "toolkit/linklist.h"
#include "toolkit/log.h"
#include "game/config/config.h"
#include "game/rendering/rendering.h"
#include "game/character/character.h"
#include "game/time/time.h"

void printer (void *data) {
	int value = *((int*)data);
	
	Log_output(1, "Value : %d\n", value);
}

int main (int argc, char *argv[])
{
	SConfig *config;
	SRendering *rendering;
	SDL_Event e;
	SCharacter *mario;
	uint32_t time;
	
	/* Log setup */
	Log_setOutput(stderr);
	Log_setVerbosity(3);
	
	/* Config setup */
	config = Config_create();
	
	/* Rendering setup */
	rendering = Rendering_create(config);
	
	/* Character setup */
	mario = Character_create("Mario", 13, "game/images/mario", 100, 5.0, 0.3, 0.0);
	
	time = Time_getTicks();
	while (e.key.keysym.sym != SDLK_ESCAPE) {
		/* Input detection */
		SDL_PollEvent(&e);
		
		/* Reset screen */
		Rendering_resetScreen();
		
		/* Update mario sprite */
		if (Time_getTicks()-time > 17) { /* 1/60 (FPS) = 0.1666666s = 17ms */
			Character_update(mario);
			time = Time_getTicks();
		}
		
		/* Blitting surfaces and rendering */
		Rendering_addSurface(rendering,
							 Character_getX(mario),
							 Character_getY(mario),
							 Character_getCurrentSprite(mario));
		Rendering_render (rendering);
		
		/* Small pause */
		SDL_Delay(1);
	}
	
	/* Character delete */
	Character_destroy(mario);
	
	/* Rendering delete */
	Rendering_destroy(rendering);
	
	/* Config delete */
	Config_destroy(config);
	
	(void) argc;
	(void) argv;
	return EXIT_SUCCESS;
}

