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
#include "object.h"
#include "../time/time.h"
#include "../../toolkit/log.h"
#include "../input/input.h"

#define GRAVITY 0.6

void OS_isWalking_Pos (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    float newSpeed;
    float elapsedT = elapsedTime;
    
    /* If something is pushed, we update the speed and spriteDuration */
    if (isPushedRight && !isPushedLeft) {
        if (object->speedX < object->maxSpeed) {
            object->speedX += object->acceleration;
            if (object->speedX <= 0) {
                object->spriteDuration = object->originalSpriteDuration;
            } else {
                object->spriteDuration -= object->acceleration*10;
            }
        }
    } else if (isPushedLeft && !isPushedRight) {
        if (-object->speedX < object->maxSpeed) {
            object->speedX -= object->acceleration;
            if (object->speedX >= 0) {
                object->spriteDuration = object->originalSpriteDuration;
            } else {
                object->spriteDuration -= object->acceleration*10;
            }
        }
    }
    /* If nothing is pushed, the mario decelerates */
     else if ((!isPushedRight && !isPushedLeft) || (isPushedLeft && isPushedRight)) {
        if (object->speedX > 0) {
            newSpeed = object->speedX - object->acceleration;
            if (newSpeed > 0) {
                object->speedX = newSpeed;
                object->spriteDuration += object->acceleration*10;
            } else {
                Object_switchState(object, OBJECT_ISSTANDING);
            }
        } else if (object->speedX < 0) {
            newSpeed = object->speedX + object->acceleration;
            if (newSpeed < 0) {
                object->speedX = newSpeed;
                object->spriteDuration += object->acceleration*10;
            } else {
                Object_switchState(object, OBJECT_ISSTANDING);
            }
        }
    }
	
    if (object->speedX < 0) {
        elapsedT = -elapsedT;
    }
    object->x += object->speedX;
    object->x = (int)(object->x)%(SDL_GetVideoSurface()->w);
}

void OS_isWalking_Sprite (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    SObjectState *currentState = &object->states[object->currentState];
    unsigned currentScheme = ObjectState_getCurrentScheme(currentState);
    unsigned schemeSize = ObjectState_getSchemeSize(currentState);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    
    /* As we're making a modulo operation, we have to be sure that this variable is not 0 */
    assert(schemeSize != 0);
    
    uint32_t time_diff = Time_getTicks() - object->lastUpdateTime;
	
    if (isPushedLeft && object->speedX > 0) {
        object->currentSprite = 11;
    } else if (isPushedRight && object->speedX < 0) {
        object->currentSprite = 5;
    } else if (time_diff > object->spriteDuration) {
        currentScheme++;
        currentScheme %= schemeSize;
        if (object->speedX > 0) {
            object->currentSprite = currentState->scheme[currentScheme];
        } else {
            object->currentSprite = currentState->scheme[currentScheme]+7;
        }
        ObjectState_setCurrentScheme(currentState, currentScheme);
		object->lastUpdateTime = Time_getTicks();
	}
    
    (void) input;
}

void OS_isStanding_Sprite (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    SObjectState *currentState = &object->states[object->currentState];
    
    if (object->speedX > 0) {
        object->currentSprite = currentState->scheme[0];
    } else {
        object->currentSprite = currentState->scheme[0]+7;
    }
    
    (void) input;
}

void OS_isJumping_Pos (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedUp = Input_isPushed(input, INPUT_UP);
    float newPos, newSpeed;
    
    if (isPushedRight && !isPushedLeft) {
        if (object->speedX < object->maxSpeed) {
            object->speedX += object->acceleration;
        }
    } else if (isPushedLeft && !isPushedRight) {
        if (-object->speedX < object->maxSpeed) {
            object->speedX -= object->acceleration;
        }
    }
    /* If nothing is pushed, the mario decelerates */
    else if ((!isPushedRight && !isPushedLeft) || (isPushedLeft && isPushedRight)) {
        if (object->speedX > 0) {
            newSpeed = object->speedX - object->acceleration;
            if (newSpeed > 0) {
                object->speedX = newSpeed;
            }
        } else if (object->speedX < 0) {
            newSpeed = object->speedX + object->acceleration;
            if (newSpeed < 0) {
                object->speedX = newSpeed;
            }
        }
    }
    
    if (isPushedUp && object->speedY > 0) {
        object->speedY -= GRAVITY/3;
    } else {
        object->speedY -= GRAVITY;
    }
    
    newPos = object->y + object->speedY;
    if (newPos < 0) {
        object->y = 0;
        Input_disableTrigger(input, INPUT_UP);
        if (object->speedX != 0) {
            Object_switchState(object, OBJECT_ISSTANDING);
        } else {
            Object_switchState(object, OBJECT_ISSTANDING);
        }
    } else {
        object->y += object->speedY;
    }
    object->x += object->speedX;
    object->x = (int)(object->x)%(SDL_GetVideoSurface()->w);
}

void OS_isJumping_Sprite (SObject *object, SInput *input, uint32_t elapsedTime) {
    assert(object != NULL);
    SObjectState *currentState = &object->states[object->currentState];
    
    if (object->speedX > 0) {
        object->currentSprite = currentState->scheme[0];
    } else {
        object->currentSprite = currentState->scheme[0]+8;
    }
    
    (void) input;
}