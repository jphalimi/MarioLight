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
#include "../../toolkit/log.h"

void isWalking_Pos (void *vcharacter) {
    assert(vcharacter != NULL);
    SCharacter *character = vcharacter;
    
    if (character->speed < character->maxSpeed) {
		character->speed += character->acceleration;
		character->spriteDuration -= (1/character->speed);
	}
	
	character->x += character->speed;
	character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
}

void isWalking_Sprite (void *vcharacter) {
    assert(vcharacter != NULL);
    SCharacter *character = vcharacter;
    SCharacterState *currentState = &character->states[character->currentState];
    unsigned currentScheme = CharacterState_getCurrentScheme(currentState);
    unsigned schemeSize = CharacterState_getSchemeSize(currentState);
    
    /* As we're making a modulo operation, we have to be sure that this variable is not 0 */
    assert(schemeSize != 0);
    
    uint32_t time_diff = Time_getTicks() - character->lastUpdateTime;
	
	if (time_diff > character->spriteDuration) {
        currentScheme++;
        currentScheme %= schemeSize;
		character->currentSprite = currentState->scheme[currentScheme];
        CharacterState_setCurrentScheme(currentState, currentScheme);
		character->lastUpdateTime = Time_getTicks();
	}
}