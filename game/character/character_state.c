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

void CharacterState_init (SCharacterState *characterState, int initState) {
	assert(characterState != NULL);
	
	switch (initState) {
		case CHARACTER_ISWALKING:
		{
			unsigned schemeTab[] = {1, 3};
			characterState->schemeSize = sizeof(schemeTab) / sizeof(*schemeTab);
			characterState->updatePos = isWalking_Pos;
			characterState->updateSprite = isWalking_Sprite;
			if (characterState->scheme == NULL) {
				characterState->scheme = malloc(characterState->schemeSize
												* sizeof(*characterState->scheme));
				assert(characterState->scheme != NULL);
			} else {
				Log_output(1, "Warning: Attempt to init CharacterState already initialized\n");
			}
			memcpy(characterState->scheme, schemeTab,
				   characterState->schemeSize * sizeof(*characterState->scheme));
			break;
		}
		case CHARACTER_ISSTANDING:
		{
			unsigned schemeTab[] = {0};
			characterState->schemeSize = sizeof(schemeTab) / sizeof(*schemeTab);
			characterState->updatePos = NULL;
			characterState->updateSprite = isStanding_Sprite;
			if (characterState->scheme == NULL) {
				characterState->scheme = malloc(characterState->schemeSize
												* sizeof(*characterState->scheme));
				assert(characterState->scheme != NULL);
			} else {
				Log_output(1, "Warning: Attempt to init CharacterState already initialized\n");
			}
			memcpy(characterState->scheme, schemeTab,
				   characterState->schemeSize * sizeof(*characterState->scheme));
			break;
		}
		case CHARACTER_ISJUMPING:
		{
			unsigned schemeTab[] = {4};
			characterState->schemeSize = sizeof(schemeTab) / sizeof(*schemeTab);
			characterState->updatePos = isJumping_Pos;
			characterState->updateSprite = isJumping_Sprite;
			if (characterState->scheme == NULL) {
				characterState->scheme = malloc(characterState->schemeSize
												* sizeof(*characterState->scheme));
				assert(characterState->scheme != NULL);
			} else {
				Log_output(1, "Warning: Attempt to init CharacterState already initialized\n");
			}
			memcpy(characterState->scheme, schemeTab,
				   characterState->schemeSize * sizeof(*characterState->scheme));
			break;
		}
		default:
			break;
	}
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

characterState_fct CharacterState_getUpdatePosHandler (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->updatePos;
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

unsigned CharacterState_getCurrentScheme (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->currentScheme;
}

unsigned CharacterState_getSchemeSize (const SCharacterState *characterState) {
	assert(characterState != NULL);
	return characterState->schemeSize;
}
