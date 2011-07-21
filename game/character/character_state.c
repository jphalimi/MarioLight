//
//  character_state.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "character_state.h"

void CharacterState_setHandlers (SCharacterState *characterState,
								 characterState_fct updatePos,
								 characterState_fct updateSprite) {
	assert(characterState != NULL);
	characterState->updatePos = updatePos;
	characterState->updateSprite = updateSprite;
}

characterState_fct CharacterState_getUpdatePosHandler (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->updatePos;
}

characterState_fct CharacterState_getUpdateSpriteHandler (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->updateSprite;
}
