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
#include "../data/objects/states_handlers.h"
#include "../../toolkit/log.h"

void ObjectState_init (SObjectState *objectState) {
	assert(objectState != NULL);
	memset(objectState, 0, sizeof(*objectState));
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

void ObjectState_setUpdatePosHandler (SObjectState *objectState, objectState_fct handler) {
	assert(objectState != NULL);
	objectState->updatePos = handler;
}

objectState_fct ObjectState_getUpdatePosHandler (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->updatePos;
}

void ObjectState_setUpdateSpriteHandler (SObjectState *objectState, objectState_fct handler) {
	assert(objectState != NULL);
	objectState->updateSprite = handler;
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

void ObjectState_setScheme (SObjectState *objectState, unsigned *scheme, unsigned schemeSize) {
	assert(objectState != NULL);
	
	free(objectState->scheme), objectState->scheme = NULL;
	
	objectState->scheme = malloc(schemeSize * sizeof(*objectState->scheme));
	assert(objectState->scheme != NULL);
	memcpy(objectState->scheme, scheme, schemeSize * sizeof(*objectState->scheme));
	objectState->schemeSize = schemeSize;
    
    Log_output(1, "objectState->schemeSize = %u\n", objectState->schemeSize);
}

unsigned ObjectState_getCurrentScheme (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->currentScheme;
}

unsigned ObjectState_getSchemeSize (const SObjectState *objectState) {
	assert(objectState != NULL);
	return objectState->schemeSize;
}
