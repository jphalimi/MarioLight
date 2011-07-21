//
//  character_state.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CHARACTERSTATE
#define H_CHARACTERSTATE

enum {  CHARACTER_ISSTANDING,   /* Character is standing (no movement) */
        CHARACTER_ISWALKING,    /* Character is walking */
        CHARACTER_ISJUMPING,    /* Character is jumping */
        CHARACTER_ISCLIMBING,   /* Character is climbing */
        CHARACTER_ISSWIMMING,   /* Character is swimming */
        CHARACTER_ISCROUCHING   /* Character is crouching */
};

typedef void (*characterState_fct)(void *);

typedef struct sCharacterState {
    characterState_fct updatePos;
    characterState_fct updateSprite;
} SCharacterState;

void CharacterState_setHandlers (SCharacterState *characterState,
                          characterState_fct updatePos,
                          characterState_fct updateSprite);

characterState_fct CharacterState_getUpdatePosHandler (const SCharacterState *characterState);
characterState_fct CharacterState_getUpdateSpriteHandler (const SCharacterState *characterState);


#endif
