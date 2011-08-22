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

void CS_isWalking_Pos (SCharacter *, SInput *input, uint32_t elapsedTime);
void CS_isWalking_Sprite (SCharacter *, SInput *input, uint32_t elapsedTime);

void CS_isStanding_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

void CS_isJumping_Pos (SCharacter *character, SInput *input, uint32_t elapsedTime);
void CS_isJumping_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

#endif
