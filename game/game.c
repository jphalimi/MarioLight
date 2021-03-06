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
#include "object/object.h"
#include "config/config.h"
#include "rendering/rendering.h"
#include "time/time.h"
#include "input/input.h"
#include "../toolkit/log.h"
#include "data/characters/characters.h"
#include "data/objects/objects.h"

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
    SObject *interr, *canon, *ground, *brick;
	uint32_t time, elapsed;
    int fps = 0;
    uint32_t time_fps, last_fps = 60;
    
    Input_init(&input);
    
    mario = Mario_create ();
    koopa = Koopa_create ();
    interr = InterrogationPoint_create ();
    canon = Canon_create();
    ground = Ground_create ();
    brick = Brick_create ();
	
    time = time_fps = Time_getTicks();
	while (!Input_quitRequested(&input)) {
		/* Input detection */
        Input_handleEvents(&input);
		
		/* Reset screen */
		Rendering_resetScreen();
		
		/* Update mario sprite */
        elapsed = Time_getTicks() - time;
		if (elapsed > 10) { /* 1/60 (FPS) = 0.1666666s = 17ms */
			Character_update(mario, &input, elapsed);
            Character_update(koopa, &input, elapsed);
            Object_update(interr, &input, elapsed);
            Object_update(canon, &input, elapsed);
            Object_update(ground, &input, elapsed);
            Object_update(brick, &input, elapsed);
			time = Time_getTicks();
            fps++;
            if (Time_getTicks() - time_fps > 1000) {
                last_fps = fps;
                Log_output(1, "FPS : %d\n", last_fps);
                fps = 0;
                time_fps = Time_getTicks();
            }
		} else {
            SDL_Delay(10 - elapsed);
        }
		
		/* Blitting surfaces and rendering */
        
		Rendering_addSurface(game->rendering,
							 Character_getX(mario),
							 Character_getY(mario),
							 Character_getCurrentSprite(mario));
        Rendering_addSurface(game->rendering,
                             Character_getX(koopa),
                             Character_getY(koopa),
                             Character_getCurrentSprite(koopa));
        Rendering_addSurface(game->rendering,
                             Object_getX(interr),
                             Object_getY(interr),
                             Object_getCurrentSprite(interr));
        Rendering_addSurface(game->rendering,
                             Object_getX(canon),
                             Object_getY(canon),
                             Object_getCurrentSprite(canon));
        Rendering_addSurface(game->rendering,
                             Object_getX(ground),
                             Object_getY(ground),
                             Object_getCurrentSprite(ground));
        Rendering_addSurface(game->rendering,
                             Object_getX(brick),
                             Object_getY(brick),
                             Object_getCurrentSprite(brick));
		Rendering_render (game->rendering);
		
		/* Small pause */
		//SDL_Delay(1000);
	}
	
	/* Character delete */
	Character_destroy (mario);
    Character_destroy (koopa);
    Object_destroy (interr);
    Object_destroy (canon);
    Object_destroy (ground);
    Object_destroy (brick);
    
    return 0;
}

void Game_destroy (SGame *game) {
    assert(game != NULL);
    
    Config_destroy(game->config);
    Rendering_destroy(game->rendering);
    free(game), game = NULL;
}