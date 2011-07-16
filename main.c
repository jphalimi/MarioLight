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
	SCharacter *mario;
	unsigned i = 0, j = 0;
	uint32_t time;
	
	/* Log setup */
	Log_setOutput(stderr);
	Log_setVerbosity(3);
	
	/* Config setup */
	config = Config_create();
	
	/* Rendering setup */
	rendering = Rendering_create(config);
	
	/* Character setup */
	mario = Character_create("Mario", 2, "game/images/mario", 250, 2.5, 2);
	
	time = Time_getTicks();
	while (i < 200) {
		Rendering_resetScreen();
		Rendering_addSurface(rendering, i, 0, Character_getSprite(mario, j%2));
		if (Time_getTicks() - time > Character_getSpriteDuration(mario)) {
			j++;
			time = Time_getTicks();
		}
		Rendering_render (rendering);
		SDL_Delay(20);
		i++;
	}
	
	SDL_Delay(2000);
	
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

