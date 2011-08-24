//
//  states_handler.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CHARACTER_STATESHANDLERS
#define H_CHARACTER_STATESHANDLERS

#include "character.h"
#include "../input/input.h"

void CS_playerWalkingPos (SCharacter *, SInput *input, uint32_t elapsedTime);
void CS_playerWalkingSprite (SCharacter *, SInput *input, uint32_t elapsedTime);

void CS_standingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

void CS_playerJumpingPos (SCharacter *character, SInput *input, uint32_t elapsedTime);
void CS_playerJumpingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

#endif
