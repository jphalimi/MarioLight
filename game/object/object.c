//
// object.c
// MarioLight
//
// Created by Jean-Philippe HALIMI on 7/16/11.
// Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include "object.h"
#include "object_state.h"
#include "states_handlers.h"
#include "../../toolkit/log.h"
#include "../time/time.h"

SObject *Object_create (const char *name, unsigned nb_sprites,
							  const char *sprites_folder, float sprite_duration,
							  float max_speed, float acceleration, float speedX, float speedY) {
	unsigned i;
	SObject *object = malloc(sizeof(*object));
	assert(object != NULL);
	memset(object, 0, sizeof(*object));
	
	/* Set struct variables */
	Object_setSprites(object, nb_sprites, sprites_folder);
	Object_setX(object, 0);
	Object_setY(object, 0);
	Object_setNbSprites(object, nb_sprites);
	Object_setName(object, name);
	Object_setSpriteDuration(object, sprite_duration);
	Object_setOriginalSpriteDuration(object, sprite_duration);
	Object_setMaxSpeed(object, max_speed);
	Object_setAcceleration(object, acceleration);
	Object_setLastUpdateTime(object, Time_getTicks());
	Object_setSpeed(object, speedX, speedY);
	Object_setCurrentSpriteNumber(object, 0);
	Object_setCurrentState(object, OBJECT_ISSTANDING);
	
	/* Init object states handlers */
	for (i = 0; i < OBJECT_STATES_NB; i++) {
		ObjectState_init(object->states+i, i);
	}
	return object;
}

void Object_setName (SObject *object, const char *name) {
	assert(object != NULL);
	
	if (name == NULL) { /* User wants the string to be reset */
		object->name[0] = '\0';
	} else { /* Copy the input string in the config struct */
		strncpy(object->name, name, STRBUF_MAXLEN);
	}
}

char const *Object_getName (const SObject *object) {
	assert(object != NULL);
	return object->name;
}

void Object_setSprites (SObject *object, unsigned nb_sprites,
						   const char *sprites_folder) {
	unsigned i;
	struct stat st;
	char spriteFileNameBuf[STRBUF_MAXLEN];
	assert(object != NULL);
	assert(nb_sprites != 0);
	
	/* Free the spriteTab in case it's already allocated */
	if (object->spriteTab != NULL) {
		Log_output(1, "Warning: Program tried to reload sprites data while it has been loaded previously\n");
		for (i = 0; i < object->nbSprites; ++i) {
			Rendering_freeSurface(object->spriteTab[i]);
		}
		free(object->spriteTab), object->spriteTab = NULL;
	}
	
	/* Check folder existence */
	assert(sprites_folder != NULL);
	if (stat(sprites_folder, &st) != 0) {
		Log_output(1, "Error: Cannot find sprites folder \"%s\"\n", sprites_folder);
		perror("");
		exit(EXIT_FAILURE);
	}
	/* Sprites table allocation */
	object->spriteTab = malloc(nb_sprites * sizeof(*(object->spriteTab)));
	assert(object->spriteTab != NULL);
	memset(object->spriteTab, 0, nb_sprites * sizeof(*(object->spriteTab)));
	
	/* Fetch and store data */
	for (i = 0; i < nb_sprites; ++i) {
		snprintf(spriteFileNameBuf, STRBUF_MAXLEN, "%s/%d.png", sprites_folder, i);
		Log_output(1, "Loading file \"%s\"... ", spriteFileNameBuf);
		object->spriteTab[i] = Rendering_loadImage(spriteFileNameBuf, 1);
		Log_output(1, "done\n");
	}
}

void Object_setX (SObject *object, float x) {
	assert(object != NULL);
	object->x = x;
}

float Object_getX (const SObject *object) {
	assert(object != NULL);
	return object->x;
}

void Object_setY (SObject *object, float y) {
	assert(object != NULL);
	object->y = y;
}

float Object_getY (const SObject *object) {
	assert(object != NULL);
	return object->y;
}

void Object_setNbSprites (SObject *object, unsigned nb_sprites) {
	assert(object != NULL);
	object->nbSprites = nb_sprites;
}

SRenderingSurface *Object_getSprite (const SObject *object, unsigned idX) {
	assert(object != NULL);
	assert(object->spriteTab != NULL);
	assert(idX < object->nbSprites);
	return object->spriteTab[idX];
}

void Object_setCurrentSpriteNumber (SObject *object, unsigned current_sprite) {
	assert(object != NULL);
	object->currentSprite = current_sprite;
}

unsigned Object_getCurrentSpriteNumber (const SObject *object) {
	assert(object != NULL);
	return object->currentSprite;
}

SRenderingSurface *Object_getCurrentSprite (const SObject *object) {
	assert(object != NULL);
	return object->spriteTab[object->currentSprite];
}

void Object_setSpriteDuration (SObject *object, float duration) {
	assert(object != NULL);
	object->spriteDuration = duration;
}

float Object_getSpriteDuration (const SObject *object) {
	assert(object != NULL);
	return object->spriteDuration;
}

void Object_setOriginalSpriteDuration (SObject *object, float duration) {
	assert(object != NULL);
	object->originalSpriteDuration = duration;
}

float Object_getOriginalSpriteDuration (const SObject *object) {
	assert(object != NULL);
	return object->originalSpriteDuration;
}

void Object_setMaxSpeed (SObject *object, float max_speed) {
	assert(object != NULL);
	object->maxSpeed = max_speed;
}

float Object_getMaxSpeed (const SObject *object) {
	assert(object != NULL);
	return object->maxSpeed;
}

void Object_setAcceleration (SObject *object, float acceleration) {
	assert(object != NULL);
	object->acceleration = acceleration;
}

float Object_getAcceleration (const SObject *object) {
	assert(object != NULL);
	return object->acceleration;
}

void Object_setLastUpdateTime (SObject *object, uint32_t time) {
	assert(object != NULL);
	object->lastUpdateTime = time;
}

uint32_t Object_getLastUpdateTime (const SObject *object) {
	assert(object != NULL);
	return object->lastUpdateTime;
}

void Object_setSpeed (SObject *object, float speedX, float speedY) {
	assert(object != NULL);
	object->speedX = speedX;
	object->speedY = speedY;
}

float Object_getSpeedX (const SObject *object) {
	assert(object != NULL);
	return object->speedX;
}

float Object_getSpeedY (const SObject *object) {
	assert(object != NULL);
	return object->speedY;
}

void Object_update (SObject *object, SInput *input, uint32_t elapsedTime) {
	Object_updateState (object, input);
	Object_updateDirection (object, input);
	Object_updatePosition(object, input, elapsedTime);
	Object_updateSprite(object, input, elapsedTime);
}

void Object_updateState (SObject *object, SInput *input) {
	assert(object != NULL && input != NULL);
	
	(void) object;
    (void) input;
}

void Object_updateDirection (SObject *object, SInput *input) {
	assert(object != NULL && input != NULL);
	
    (void) object;
    (void) input;
}

void Object_updatePosition (SObject *object, SInput *input, uint32_t elapsedTime) {
	objectState_fct updatePosition;
	assert(object != NULL);
	updatePosition = ObjectState_getUpdatePosHandler (&(object->states[object->currentState]));
	
	if (updatePosition != NULL) {
		updatePosition (object, input, elapsedTime);
	}
}

void Object_updateSprite (SObject *object, SInput *input, uint32_t elapsedTime) {
	objectState_fct updateSprite;
	assert(object != NULL);
	updateSprite = ObjectState_getUpdateSpriteHandler(&(object->states[object->currentState]));
	
	if (updateSprite != NULL) {
		updateSprite (object, input, elapsedTime);
	}
}

void Object_setCurrentState (SObject *object, unsigned currentState) {
	assert(object != NULL);
	object->currentState = currentState;
}

unsigned Object_getCurrentState (const SObject *object) {
	assert(object != NULL);
	return object->currentState;
}

void Object_switchState (SObject *object, unsigned newState) {
	assert(object != NULL);
	switch (newState) {
		case OBJECT_ISMOVING:
			object->spriteDuration = object->originalSpriteDuration;
			break;
		case OBJECT_ISSTANDING:
			object->speedY = 0;
            object->speedX = 0;
			break;
	}
	object->currentState = newState;
}

void Object_setLastDirection (SObject *object, int value) {
	assert(object != NULL);
	object->lastDirection = value;
}

int Object_getLastDirection (const SObject *object) {
	assert(object != NULL);
	return object->lastDirection;
}

void Object_destroy (SObject *object) {
	unsigned i;
	
	for (i = 0; i < object->nbSprites; ++i) {
		Rendering_freeSurface(object->spriteTab[i]);
	}
	free(object->spriteTab), object->spriteTab = NULL;
	
	for (i = 0; i < OBJECT_STATES_NB; ++i) {
		ObjectState_free(&object->states[i]);
	}
	free(object), object = NULL;
}