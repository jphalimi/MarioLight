//
//  game.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "game.h"
#include "character/character.h"
#include "character/character_state.h"
#include "character/states_handlers.h"
#include "config/config.h"
#include "rendering/rendering.h"
#include "time/time.h"
#include "input/input.h"
#include "../toolkit/log.h"
#include "data/characters/characters.h"

SGame *Game_create (void) {
    SGame *game = malloc(sizeof(*game));
    assert(game != NULL);
    memset(game, 0, sizeof(*game));
    
    game->config = Config_create();
    game->rendering = Rendering_create(game->config);
    
    return game;
}

int Game_launch (SGame *game) {
    SInput input;
	SCharacter *mario, *koopa;
	uint32_t time, elapsed;
    int fps = 0;
    uint32_t time_fps, last_fps = 60;
    
    Input_init(&input);
    
    mario = Mario_create ();
	
    time = time_fps = Time_getTicks();
	while (!Input_quitRequested(&input)) {
		/* Input detection */
        Input_handleEvents(&input);
		
		/* Reset screen */
		Rendering_resetScreen();
		
		/* Update mario sprite */
        elapsed = Time_getTicks() - time;
		if (elapsed > 17) { /* 1/60 (FPS) = 0.1666666s = 17ms */
			Character_update(mario, &input, elapsed);
			time = Time_getTicks();
            fps++;
            if (Time_getTicks() - time_fps > 1000) {
                last_fps = fps;
                Log_output(1, "FPS : %d\n", last_fps);
                fps = 0;
                time_fps = Time_getTicks();
            }
		} else {
            SDL_Delay(17 - elapsed);
        }
		
		/* Blitting surfaces and rendering */
        
		Rendering_addSurface(game->rendering,
							 Character_getX(mario),
							 Character_getY(mario),
							 Character_getCurrentSprite(mario));
		Rendering_render (game->rendering);
		
		/* Small pause */
		//SDL_Delay(100);
	}
	
	/* Character delete */
	Character_destroy(mario);
    
    return 0;
}

void Game_destroy (SGame *game) {
    assert(game != NULL);
    
    Config_destroy(game->config);
    Rendering_destroy(game->rendering);
    free(game), game = NULL;
}