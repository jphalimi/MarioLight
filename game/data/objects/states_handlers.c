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
#include "../../object/object.h"
#include "../../character/character.h"
#include "../../time/time.h"
#include "../../../toolkit/log.h"
#include "../../input/input.h"

#define GRAVITY 0.6

void OS_interrogationStandingSprite (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    SObjectState *currentState = &object->states[object->currentState];
    unsigned currentScheme = ObjectState_getCurrentScheme(currentState);
    unsigned schemeSize = ObjectState_getSchemeSize(currentState);
    
    assert(schemeSize != 0);
    uint32_t time_diff = Time_getTicks() - object->lastUpdateTime;
    
    //Log_output(1, "spriteDuration : %f, currentScheme : %u\n", object->spriteDuration, currentScheme);
	
    if (time_diff > object->spriteDuration) {
        currentScheme++;
        currentScheme %= schemeSize;
        object->currentSprite = currentState->scheme[currentScheme];
        ObjectState_setCurrentScheme(currentState, currentScheme);
		object->lastUpdateTime = Time_getTicks();
	}
    
    (void) elapsedTime;
    (void) input;
    
}