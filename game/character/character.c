//
// character.c
// MarioLight
//
// Created by Jean-Philippe HALIMI on 7/16/11.
// Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include "character.h"
#include "character_state.h"
#include "../data/characters/states_handlers.h"
#include "../../toolkit/log.h"
#include "../time/time.h"

SCharacter *Character_create (const char *name, unsigned nb_sprites,
							  const char *sprites_folder, float sprite_duration,
							  float max_speed, float acceleration, float speedX, float speedY) {
	SCharacter *character = malloc(sizeof(*character));
	assert(character != NULL);
	memset(character, 0, sizeof(*character));
	
	/* Set struct variables */
	Character_setSprites(character, nb_sprites, sprites_folder);
	Character_setX(character, 0);
	Character_setY(character, 0);
	Character_setNbSprites(character, nb_sprites);
	Character_setName(character, name);
	Character_setSpriteDuration(character, sprite_duration);
	Character_setOriginalSpriteDuration(character, sprite_duration);
	Character_setMaxSpeed(character, max_speed);
	Character_setAcceleration(character, acceleration);
	Character_setLastUpdateTime(character, Time_getTicks());
	Character_setSpeed(character, speedX, speedY);
	Character_setCurrentSpriteNumber(character, 0);
	Character_setCurrentState(character, CHARACTER_ISSTANDING);
	Character_setLastDirection(character, DIR_RIGHT);
	Character_disablePlayable(character);
	
	return character;
}

void Character_setName (SCharacter *character, const char *name) {
	assert(character != NULL);
	
	if (name == NULL) { /* User wants the string to be reset */
		character->name[0] = '\0';
	} else { /* Copy the input string in the config struct */
		strncpy(character->name, name, STRBUF_MAXLEN);
	}
}

char const *Character_getName (const SCharacter *character) {
	assert(character != NULL);
	return character->name;
}

void Character_setSprites (SCharacter *character, unsigned nb_sprites,
						   const char *sprites_folder) {
	unsigned i;
	struct stat st;
	char spriteFileNameBuf[STRBUF_MAXLEN];
	assert(character != NULL);
	assert(nb_sprites != 0);
	
	/* Free the spriteTab in case it's already allocated */
	if (character->spriteTab != NULL) {
		Log_output(1, "Warning: Program tried to reload sprites data while it has been loaded previously\n");
		for (i = 0; i < character->nbSprites; ++i) {
			Rendering_freeSurface(character->spriteTab[i]);
		}
		free(character->spriteTab), character->spriteTab = NULL;
	}
	
	/* Check folder existence */
	assert(sprites_folder != NULL);
	if (stat(sprites_folder, &st) != 0) {
		Log_output(1, "Error: Cannot find sprites folder \"%s\"\n", sprites_folder);
		perror("");
		exit(EXIT_FAILURE);
	}
	/* Sprites table allocation */
	character->spriteTab = malloc(nb_sprites * sizeof(*(character->spriteTab)));
	assert(character->spriteTab != NULL);
	memset(character->spriteTab, 0, nb_sprites * sizeof(*(character->spriteTab)));
	
	/* Fetch and store data */
	for (i = 0; i < nb_sprites; ++i) {
		snprintf(spriteFileNameBuf, STRBUF_MAXLEN, "%s/%d.png", sprites_folder, i);
		Log_output(1, "Loading file \"%s\"... ", spriteFileNameBuf);
		character->spriteTab[i] = Rendering_loadImage(spriteFileNameBuf, 1);
		Log_output(1, "done\n");
	}
}

void Character_setX (SCharacter *character, float x) {
	assert(character != NULL);
	character->x = x;
}

float Character_getX (const SCharacter *character) {
	assert(character != NULL);
	return character->x;
}

void Character_setY (SCharacter *character, float y) {
	assert(character != NULL);
	character->y = y;
}

float Character_getY (const SCharacter *character) {
	assert(character != NULL);
	return character->y;
}

void Character_setNbSprites (SCharacter *character, unsigned nb_sprites) {
	assert(character != NULL);
	character->nbSprites = nb_sprites;
}

SRenderingSurface *Character_getSprite (const SCharacter *character, unsigned idX) {
	assert(character != NULL);
	assert(character->spriteTab != NULL);
	assert(idX < character->nbSprites);
	return character->spriteTab[idX];
}

void Character_setCurrentSpriteNumber (SCharacter *character, unsigned current_sprite) {
	assert(character != NULL);
	character->currentSprite = current_sprite;
}

unsigned Character_getCurrentSpriteNumber (const SCharacter *character) {
	assert(character != NULL);
	return character->currentSprite;
}

SRenderingSurface *Character_getCurrentSprite (const SCharacter *character) {
	assert(character != NULL);
	return character->spriteTab[character->currentSprite];
}

void Character_setSpriteDuration (SCharacter *character, float duration) {
	assert(character != NULL);
	character->spriteDuration = duration;
}

float Character_getSpriteDuration (const SCharacter *character) {
	assert(character != NULL);
	return character->spriteDuration;
}

void Character_resetSpriteDuration (SCharacter *character) {
	assert(character != NULL);
	character->spriteDuration = character->originalSpriteDuration;
}

void Character_setOriginalSpriteDuration (SCharacter *character, float duration) {
	assert(character != NULL);
	character->originalSpriteDuration = duration;
}

float Character_getOriginalSpriteDuration (const SCharacter *character) {
	assert(character != NULL);
	return character->originalSpriteDuration;
}

void Character_setMaxSpeed (SCharacter *character, float max_speed) {
	assert(character != NULL);
	character->maxSpeed = max_speed;
}

float Character_getMaxSpeed (const SCharacter *character) {
	assert(character != NULL);
	return character->maxSpeed;
}

void Character_setAcceleration (SCharacter *character, float acceleration) {
	assert(character != NULL);
	character->acceleration = acceleration;
}

float Character_getAcceleration (const SCharacter *character) {
	assert(character != NULL);
	return character->acceleration;
}

void Character_setLastUpdateTime (SCharacter *character, uint32_t time) {
	assert(character != NULL);
	character->lastUpdateTime = time;
}

uint32_t Character_getLastUpdateTime (const SCharacter *character) {
	assert(character != NULL);
	return character->lastUpdateTime;
}

void Character_setSpeed (SCharacter *character, float speedX, float speedY) {
	assert(character != NULL);
	character->speedX = speedX;
	character->speedY = speedY;
}

float Character_getSpeedX (const SCharacter *character) {
	assert(character != NULL);
	return character->speedX;
}

float Character_getSpeedY (const SCharacter *character) {
	assert(character != NULL);
	return character->speedY;
}

void Character_update (SCharacter *character, SInput *input, uint32_t elapsedTime) {
	if (!Character_isPlayable(character)) {
		input = NULL;
	}
	Character_updateState (character, input);
	Character_updateDirection (character, input);
	Character_updatePosition(character, input, elapsedTime);
	Character_updateSprite(character, input, elapsedTime);
}

void Character_updateState (SCharacter *character, SInput *input) {
	assert(character != NULL);
	
	switch (character->currentState) {
		case CHARACTER_ISWALKING:
			if (Input_isPushed(input, INPUT_A)) {
				Character_switchState(character, CHARACTER_ISJUMPING);
			}
			break;
		case CHARACTER_ISSTANDING:
			if (Input_isPushed(input, INPUT_LEFT)) {
				Character_switchState(character, CHARACTER_ISWALKING);
			}
			if (Input_isPushed(input, INPUT_RIGHT)) {
				Character_switchState(character, CHARACTER_ISWALKING);
			}
			if (Input_isPushed(input, INPUT_A)) {
				Character_switchState(character, CHARACTER_ISJUMPING);
			}
			break;
	}
}

void Character_updateDirection (SCharacter *character, SInput *input) {
	assert(character != NULL);
	
	if (Input_isPushed(input, INPUT_LEFT)) {
		character->lastDirection = DIR_LEFT;
	}
	if (Input_isPushed(input, INPUT_RIGHT)) {
		character->lastDirection = DIR_RIGHT;
	}
}

void Character_updatePosition (SCharacter *character, SInput *input, uint32_t elapsedTime) {
	characterState_fct updatePosition;
	assert(character != NULL);
	updatePosition = CharacterState_getUpdatePosHandler (&(character->states[character->currentState]));
	
	if (updatePosition != NULL) {
		updatePosition (character, input, elapsedTime);
	}
}

void Character_updateSprite (SCharacter *character, SInput *input, uint32_t elapsedTime) {
	characterState_fct updateSprite;
	assert(character != NULL);
	updateSprite = CharacterState_getUpdateSpriteHandler(&(character->states[character->currentState]));
	
	if (updateSprite != NULL) {
		updateSprite (character, input, elapsedTime);
	}
}

void Character_setCurrentState (SCharacter *character, unsigned currentState) {
	assert(character != NULL);
	character->currentState = currentState;
}

unsigned Character_getCurrentState (const SCharacter *character) {
	assert(character != NULL);
	return character->currentState;
}

void Character_setUpdatePosHandler (SCharacter *character, int state, characterState_fct handler) {
	assert(character != NULL);
	assert(state < CHARACTER_STATES_NB);
	CharacterState_setUpdatePosHandler(character->states+state, handler);
}

void Character_setUpdateSpriteHandler (SCharacter *character, int state, characterState_fct handler) {
	assert(character != NULL);
	assert(state < CHARACTER_STATES_NB);
	CharacterState_setUpdateSpriteHandler(character->states+state, handler);
}

void Character_setScheme (SCharacter *character, int state, unsigned *scheme, unsigned schemeSize) {
	assert(character != NULL);
	assert(state < CHARACTER_STATES_NB);
	CharacterState_setScheme(character->states + state, scheme, schemeSize);
}

void Character_switchState (SCharacter *character, unsigned newState) {
	assert(character != NULL);
	Character_resetSpriteDuration(character);
	switch (newState) {
		case CHARACTER_ISSTANDING:
			character->speedX = 0;
			character->speedY = 0;
			break;
		case CHARACTER_ISWALKING:
			character->speedY = 0;
		case CHARACTER_ISJUMPING:
			character->speedY = 6.0f;
			break;
	}
	Character_setCurrentState(character, newState);
}

void Character_setLastDirection (SCharacter *character, int value) {
	assert(character != NULL);
	character->lastDirection = value;
}

int Character_getLastDirection (const SCharacter *character) {
	assert(character != NULL);
	return character->lastDirection;
}

void Character_enablePlayable (SCharacter *character) {
	assert(character != NULL);
	character->isPlayable = 1;
}

void Character_disablePlayable (SCharacter *character) {
	assert(character != NULL);
	character->isPlayable = 0;
}

int Character_isPlayable (const SCharacter *character) {
	assert(character != NULL);
	return character->isPlayable;
}

void Character_destroy (SCharacter *character) {
	unsigned i;
	
	for (i = 0; i < character->nbSprites; ++i) {
		Rendering_freeSurface(character->spriteTab[i]);
	}
	free(character->spriteTab), character->spriteTab = NULL;
	
	for (i = 0; i < CHARACTER_STATES_NB; ++i) {
		CharacterState_free(&character->states[i]);
	}
	free(character), character = NULL;
}