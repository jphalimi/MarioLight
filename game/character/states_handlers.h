//
//  states_handler.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_STATESHANDLERS
#define H_STATESHANDLERS

#include "character.h"
#include "../input/input.h"

void isWalking_Pos (SCharacter *, SInput *input, uint32_t elapsedTime);
void isWalking_Sprite (SCharacter *, SInput *input, uint32_t elapsedTime);

void isStanding_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

void isJumping_Pos (SCharacter *character, SInput *input, uint32_t elapsedTime);
void isJumping_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime);

#endif
