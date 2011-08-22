//
//  character_state.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "character_state.h"
#include "states_handlers.h"
#include "../../toolkit/log.h"

void CharacterState_init (SCharacterState *characterState) {
	assert(characterState != NULL);
	memset(characterState, 0, sizeof(*characterState));
}

void CharacterState_free (SCharacterState *characterState) {
	assert(characterState != NULL);
	if (characterState->scheme != NULL) {
		free(characterState->scheme), characterState->scheme = NULL;
	}
}

void CharacterState_reInit (SCharacterState *characterState) {
	assert(characterState != NULL);
	characterState->currentScheme = 0;
}

void CharacterState_setUpdatePosHandler (SCharacterState *characterState, characterState_fct handler) {
	assert(characterState != NULL);
	characterState->updatePos = handler;
}

characterState_fct CharacterState_getUpdatePosHandler (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->updatePos;
}

void CharacterState_setUpdateSpriteHandler (SCharacterState *characterState, characterState_fct handler) {
	assert(characterState != NULL);
	characterState->updateSprite = handler;
}

characterState_fct CharacterState_getUpdateSpriteHandler (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->updateSprite;
}

void CharacterState_setCurrentScheme (SCharacterState *characterState, unsigned value) {
	assert(characterState != NULL);
	if (value >= characterState->schemeSize) {
		Log_output(1, "Error: Attempt to set %u value to current index of a %u-sized table\n",
				   value, characterState->schemeSize);
		exit (EXIT_FAILURE);
	}
	characterState->currentScheme = value;
}

void CharacterState_setScheme (SCharacterState *characterState, unsigned *scheme, unsigned schemeSize) {
	assert(characterState != NULL);
	
	free(characterState->scheme), characterState->scheme = NULL;
	
	characterState->scheme = malloc(schemeSize * sizeof(*characterState->scheme));
	assert(characterState->scheme != NULL);
	memcpy(characterState->scheme, scheme, schemeSize * sizeof(*characterState->scheme));
	characterState->schemeSize = schemeSize;
}

unsigned CharacterState_getCurrentScheme (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->currentScheme;
}

unsigned CharacterState_getSchemeSize (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->schemeSize;
}
