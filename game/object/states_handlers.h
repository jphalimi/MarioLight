//
//  states_handler.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_OBJECT_STATESHANDLERS
#define H_OBJECT_STATESHANDLERS

#include "object.h"
#include "../input/input.h"

void OS_isWalking_Pos (SObject *, SInput *input, uint32_t elapsedTime);
void OS_isWalking_Sprite (SObject *, SInput *input, uint32_t elapsedTime);

void OS_isStanding_Sprite (SObject *object, SInput *input, uint32_t elapsedTime);

void OS_isJumping_Pos (SObject *object, SInput *input, uint32_t elapsedTime);
void OS_isJumping_Sprite (SObject *object, SInput *input, uint32_t elapsedTime);

#endif
