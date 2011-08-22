//
//  object_state.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "object_state.h"
#include "states_handlers.h"
#include "../../toolkit/log.h"

void ObjectState_init (SObjectState *objectState, int initState) {
	assert(objectState != NULL);
	assert(initState < OBJECT_STATES_NB);
	
	switch (initState) {
		case OBJECT_ISMOVING:
		{
			unsigned schemeTab[] = {1, 3};
			objectState->schemeSize = sizeof(schemeTab) / sizeof(*schemeTab);
			objectState->updatePos = OS_isWalking_Pos;
			objectState->updateSprite = OS_isWalking_Sprite;
			if (objectState->scheme == NULL) {
				objectState->scheme = malloc(objectState->schemeSize
												* sizeof(*objectState->scheme));
				assert(objectState->scheme != NULL);
			} else {
				Log_output(1, "Warning: Attempt to init CharacterState already initialized\n");
			}
			memcpy(objectState->scheme, schemeTab,
				   objectState->schemeSize * sizeof(*objectState->scheme));
			break;
		}
		case OBJECT_ISSTANDING:
		{
			unsigned schemeTab[] = {0};
			objectState->schemeSize = sizeof(schemeTab) / sizeof(*schemeTab);
			objectState->updatePos = NULL;
			objectState->updateSprite = OS_isStanding_Sprite;
			if (objectState->scheme == NULL) {
				objectState->scheme = malloc(objectState->schemeSize
												* sizeof(*objectState->scheme));
				assert(objectState->scheme != NULL);
			} else {
				Log_output(1, "Warning: Attempt to init CharacterState already initialized\n");
			}
			memcpy(objectState->scheme, schemeTab,
				   objectState->schemeSize * sizeof(*objectState->scheme));
			break;
		}
		default:
			break;
	}
}

void ObjectState_free (SObjectState *objectState) {
	assert(objectState != NULL);
	if (objectState->scheme != NULL) {
		free(objectState->scheme), objectState->scheme = NULL;
	}
}

void ObjectState_reInit (SObjectState *objectState) {
	assert(objectState != NULL);
	objectState->currentScheme = 0;
}

objectState_fct ObjectState_getUpdatePosHandler (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->updatePos;
}

objectState_fct ObjectState_getUpdateSpriteHandler (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->updateSprite;
}

void ObjectState_setCurrentScheme (SObjectState *objectState, unsigned value) {
	assert(objectState != NULL);
	if (value >= objectState->schemeSize) {
		Log_output(1, "Error: Attempt to set %u value to current index of a %u-sized table\n",
				   value, objectState->schemeSize);
		exit (EXIT_FAILURE);
	}
	objectState->currentScheme = value;
}

unsigned ObjectState_getCurrentScheme (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->currentScheme;
}

unsigned ObjectState_getSchemeSize (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->schemeSize;
}
