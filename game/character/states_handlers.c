//
//  states_handler.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "states_handlers.h"
#include "character.h"
#include "../time/time.h"

void isWalking_Pos (void *vcharacter) {
    SCharacter *character = vcharacter;
    assert(character != NULL);
    
    if (character->speed < character->maxSpeed) {
		character->speed += character->acceleration;
		character->spriteDuration = (1/character->speed)*500;
	}
	
	character->x += character->speed;
	character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
}

void isWalking_Sprite (void *vcharacter) {
    SCharacter *character = vcharacter;
    assert(character != NULL);
    uint32_t time_diff = Time_getTicks() - character->lastUpdateTime;
	
	if (time_diff > character->spriteDuration) {
		character->currentSprite++;
		character->currentSprite %= character->nbSprites;
		character->lastUpdateTime = Time_getTicks();
	}
}