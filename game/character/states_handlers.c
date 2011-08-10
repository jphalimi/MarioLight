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
#include "../input/input.h"

#define GRAVITY 0.5

void isWalking_Pos (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    float newSpeed;
    float elapsedT = elapsedTime;
    
    /* If something is pushed, we update the speed and spriteDuration */
    if (isPushedRight) {
        if (character->speedX < character->maxSpeed) {
            character->speedX += character->acceleration;
            if (character->speedX <= 0) {
                character->spriteDuration = character->originalSpriteDuration;
            } else {
                character->spriteDuration -= character->acceleration*10;
            }
        }
    } else if (isPushedLeft) {
        if (-character->speedX < character->maxSpeed) {
            character->speedX -= character->acceleration;
            if (character->speedX >= 0) {
                character->spriteDuration = character->originalSpriteDuration;
            } else {
                character->spriteDuration -= character->acceleration*10;
            }
        }
    }
    /* If nothing is pushed, the mario decelerates */
     else if (!isPushedRight && !isPushedLeft) {
        if (character->speedX > 0) {
            newSpeed = character->speedX - character->acceleration;
            if (newSpeed > 0) {
                character->speedX = newSpeed;
                character->spriteDuration += character->acceleration*10;
            } else {
                Character_switchState(character, CHARACTER_ISSTANDING);
            }
        } else if (character->speedX < 0) {
            newSpeed = character->speedX + character->acceleration;
            if (newSpeed < 0) {
                character->speedX = newSpeed;
                character->spriteDuration += character->acceleration*10;
            } else {
                Character_switchState(character, CHARACTER_ISSTANDING);
            }
        }
    }
	
    if (character->speedX < 0) {
        elapsedT = -elapsedT;
    }
    character->x += character->speedX;
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
}

void isWalking_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    unsigned currentScheme = CharacterState_getCurrentScheme(currentState);
    unsigned schemeSize = CharacterState_getSchemeSize(currentState);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    
    /* As we're making a modulo operation, we have to be sure that this variable is not 0 */
    assert(schemeSize != 0);
    
    uint32_t time_diff = Time_getTicks() - character->lastUpdateTime;
	
    if (isPushedLeft && character->speedX > 0) {
        character->currentSprite = 11;
    } else if (isPushedRight && character->speedX < 0) {
        character->currentSprite = 5;
    } else if (time_diff > character->spriteDuration) {
        currentScheme++;
        currentScheme %= schemeSize;
        if (character->lastDirection == DIR_RIGHT) {
            character->currentSprite = currentState->scheme[currentScheme];
        } else {
            character->currentSprite = currentState->scheme[currentScheme]+7;
        }
        CharacterState_setCurrentScheme(currentState, currentScheme);
		character->lastUpdateTime = Time_getTicks();
	}
    
    (void) input;
}

void isStanding_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    
    if (character->lastDirection == DIR_RIGHT) {
        character->currentSprite = currentState->scheme[0];
    } else {
        character->currentSprite = currentState->scheme[0]+7;
    }
    
    (void) input;
}

void isJumping_Pos (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    int isPushedUp = Input_isPushed(input, INPUT_UP);
    float newPos;
    
    if (isPushedUp && character->speedY > 0) {
        character->speedY -= GRAVITY/3;
    } else {
        character->speedY -= GRAVITY;
    }
    
    newPos = character->y + character->speedY;
    if (newPos < 0) {
        character->y = 0;
        Character_switchState(character, CHARACTER_ISSTANDING);
    } else {
        character->y += character->speedY;
    }
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
}

void isJumping_Sprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    
    if (character->lastDirection == DIR_RIGHT) {
        character->currentSprite = currentState->scheme[0];
    } else {
        character->currentSprite = currentState->scheme[0]+8;
    }
    
    (void) input;
}