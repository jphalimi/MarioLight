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
#include "../../character/character.h"
#include "../../time/time.h"
#include "../../../toolkit/log.h"
#include "../../input/input.h"

#define GRAVITY 0.6

void CS_playerWalkingPos (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    int isPushedB = Input_isPushed(input, INPUT_B);
    float newSpeed, maxSpeedX;
    
    if (isPushedB) {
        maxSpeedX = character->maxSpeed*1.5;
    } else {
        maxSpeedX = character->maxSpeed;
    }
    
    /* If something is pushed, we update the speed and spriteDuration */
    if (isPushedRight && !isPushedLeft) {
        if (character->speedX < maxSpeedX) {
            character->speedX += character->acceleration;
            if (character->speedX <= 0) {
                character->spriteDuration = character->originalSpriteDuration;
            } else {
                character->spriteDuration -= character->acceleration*10;
            }
        } else if (character->speedX > maxSpeedX) {
            character->speedX -= character->acceleration;
            character->spriteDuration += character->acceleration*10;
        }
    } else if (isPushedLeft && !isPushedRight) {
        if (-character->speedX < maxSpeedX) {
            character->speedX -= character->acceleration;
            if (character->speedX >= 0) {
                character->spriteDuration = character->originalSpriteDuration;
            } else {
                character->spriteDuration -= character->acceleration*10;
            }
        } else if (-character->speedX > maxSpeedX) {
            character->speedX += character->acceleration;
            character->spriteDuration += character->acceleration*10;
        }
    }
    /* If nothing is pushed, the mario decelerates */
     else if ((!isPushedRight && !isPushedLeft) || (isPushedLeft && isPushedRight)) {
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
    
    character->x += character->speedX;
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
    if (character->x < 0) {
        character->x = SDL_GetVideoSurface()->w;
    }
    
    (void) elapsedTime;
}

void CS_playerWalkingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
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
    
    (void) elapsedTime;
    (void) input;
}

void CS_standingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    
    if (character->lastDirection == DIR_RIGHT) {
        character->currentSprite = currentState->scheme[0];
    } else {
        character->currentSprite = currentState->scheme[0]+7;
    }
    
    (void) elapsedTime;
    (void) input;
}

void CS_playerJumpingPos (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    int isPushedLeft = Input_isPushed(input, INPUT_LEFT);
    int isPushedRight = Input_isPushed(input, INPUT_RIGHT);
    int isPushedA = Input_isPushed(input, INPUT_A);
    int isPushedB = Input_isPushed(input, INPUT_B);
    float newPos, newSpeed;
    float maxSpeedX;
    
    if (isPushedB) {
        maxSpeedX = character->maxSpeed;
    } else {
        maxSpeedX = character->maxSpeed/1.5;
    }
    
    if (isPushedRight && !isPushedLeft) {
        if (character->speedX < maxSpeedX) {
            character->speedX += character->acceleration;
        }
    } else if (isPushedLeft && !isPushedRight) {
        if (-character->speedX < maxSpeedX) {
            character->speedX -= character->acceleration;
        }
    }
    /* If nothing is pushed, the mario decelerates */
    else if ((!isPushedRight && !isPushedLeft) || (isPushedLeft && isPushedRight)) {
        if (character->speedX > 0) {
            newSpeed = character->speedX - character->acceleration;
            if (newSpeed > 0) {
                character->speedX = newSpeed;
            }
        } else if (character->speedX < 0) {
            newSpeed = character->speedX + character->acceleration;
            if (newSpeed < 0) {
                character->speedX = newSpeed;
            }
        }
    }
    
    if (isPushedA && character->speedY > 0) {
        character->speedY -= GRAVITY/3;
    } else {
        character->speedY -= GRAVITY;
    }
    
    newPos = character->y + character->speedY;
    if (newPos < 0) {
        character->y = 0;
        Input_disableTrigger(input, INPUT_A);
        if (character->speedX != 0) {
            Character_resetSpriteDuration(character);
            Character_switchState(character, CHARACTER_ISWALKING);
        } else {
            Character_switchState(character, CHARACTER_ISSTANDING);
        }
    } else {
        character->y += character->speedY;
    }
    character->x += character->speedX;
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
    
    (void) elapsedTime;
}

void CS_playerJumpingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    
    if (character->lastDirection == DIR_RIGHT) {
        character->currentSprite = currentState->scheme[0];
    } else {
        character->currentSprite = currentState->scheme[0]+8;
    }
    
    (void) elapsedTime;
    (void) input;
}

void CS_characterWalkingPos (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    
    character->x += character->speedX;
    
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
    if (character->x < 0) {
        character->x = SDL_GetVideoSurface()->w;
    }
    
    (void) input;
    (void) elapsedTime;
}

void CS_characterWalkingSprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
    assert(character != NULL);
    SCharacterState *currentState = &character->states[character->currentState];
    unsigned currentScheme = CharacterState_getCurrentScheme(currentState);
    unsigned schemeSize = CharacterState_getSchemeSize(currentState);

    assert(schemeSize != 0);
    uint32_t time_diff = Time_getTicks() - character->lastUpdateTime;
    
    //Log_output(1, "spriteDuration : %f, currentScheme : %u\n", character->spriteDuration, currentScheme);
	
    if (time_diff > character->spriteDuration) {
        currentScheme++;
        currentScheme %= schemeSize;
        if (character->lastDirection == DIR_RIGHT) {
            character->currentSprite = currentState->scheme[currentScheme]-2;
        } else {
            character->currentSprite = currentState->scheme[currentScheme];
        }
        CharacterState_setCurrentScheme(currentState, currentScheme);
		character->lastUpdateTime = Time_getTicks();
	}
    
    (void) elapsedTime;
    (void) input;
    
}