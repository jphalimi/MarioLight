//
//  object.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_OBJECTSTATE
#define H_OBJECTSTATE

#include <stdint.h>
#include "../input/input.h"

struct sObject;

enum {  OBJECT_ISSTANDING = 0,   /* Object is standing (no movement) */
		OBJECT_ISMOVING,	/* Object is moving */
        OBJECT_STATES_NB
};

typedef void (*objectState_fct)(struct sObject *object, SInput *input, uint32_t elapsedTime);

typedef struct sObjectState {
	objectState_fct updatePos;		/* callback function handling the position update */
	objectState_fct updateSprite;	/* callback function handling the sprite update */
	unsigned *scheme;
	unsigned currentScheme;	/* in Sprite scheme, what is the current position of the object */
	unsigned schemeSize;		/* what is the scheme table size ? */
} SObjectState;

void ObjectState_init (SObjectState *objectState, int initState);
void ObjectState_free (SObjectState *objectState);

/* If we're switching back to a specific current state already used in the past,
	then we want to re-init stuff into the struct */
void ObjectState_reInit (SObjectState *objectState);

objectState_fct ObjectState_getUpdatePosHandler (const SObjectState *objectState);
objectState_fct ObjectState_getUpdateSpriteHandler (const SObjectState *objectState);

void ObjectState_setCurrentScheme (SObjectState *objectState, unsigned value);
unsigned ObjectState_getCurrentScheme (const SObjectState *objectState);
unsigned ObjectState_getSchemeSize (const SObjectState *objectState);

#endif
