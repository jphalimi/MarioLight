//
// character.h
// MarioLight
//
// Created by Jean-Philippe HALIMI on 7/16/11.
// Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CHARACTER
#define H_CHARACTER

#include <stdint.h>

#include "../config/config.h"
#include "../rendering/rendering.h"
#include "../input/input.h"
#include "character_state.h"

/* Directions enum */
enum { DIR_RIGHT, DIR_LEFT };

typedef struct sCharacter {
    char name[STRBUF_MAXLEN];
    SRenderingSurface **spriteTab;
    unsigned nbSprites;
    unsigned currentSprite;
    float spriteDuration;
    float maxSpeed;
    float acceleration;
    uint32_t lastUpdateTime;
    float speed;
    float x, y; /* Character position */
    SCharacterState states[CHARACTER_STATES_NB];
    unsigned currentState;
    int lastDirection;
} SCharacter;

SCharacter *Character_create (const char *name, unsigned nb_sprites,
                              const char *sprites_folder, float sprite_duration,
                              float max_speed, float acceleration, float speed);
void Character_setName (SCharacter *character, const char *name);
char const *Character_getName (const SCharacter *character);

void Character_setSprites (SCharacter *character, unsigned nb_sprites,
                           const char *sprites_folder);

void Character_setX (SCharacter *character, float x);
float Character_getX (const SCharacter *character);

void Character_setY (SCharacter *character, float y);
float Character_getY (const SCharacter *character);

void Character_setNbSprites (SCharacter *character, unsigned nb_sprites);
unsigned Character_getNbSprites (const SCharacter *character);

void Character_setSprite (SCharacter *character, SRenderingSurface *surf, unsigned idX);
SRenderingSurface *Character_getSprite (const SCharacter *character, unsigned idX);

void Character_setCurrentSpriteNumber (SCharacter *character, unsigned current_sprite);
unsigned Character_getCurrentSpriteNumber (const SCharacter *character);

SRenderingSurface *Character_getCurrentSprite (const SCharacter *character);

void Character_setSpriteDuration (SCharacter *character, uint32_t spriteDuraton);
uint32_t Character_getSpriteDuration (const SCharacter *character);

void Character_setMaxSpeed (SCharacter *character, float maxSpeed);
float Character_getMaxSpeed (const SCharacter *character);

void Character_setAcceleration (SCharacter *character, float acceleration);
float Character_getAcceleration (const SCharacter *character);

void Character_setLastUpdateTime (SCharacter *character, uint32_t time);
uint32_t Character_getLastUpdateTime (const SCharacter *character);

void Character_setSpeed (SCharacter *character, float speed);
float Character_getSpeed (const SCharacter *character);

void Character_update (SCharacter *character, SInput *input);
void Character_updateDirection (SCharacter *character, SInput *input);
void Character_updatePosition (SCharacter *character, SInput *input);
void Character_updateSprite (SCharacter *character, SInput *input);

void Character_setCurrentState (SCharacter *character, unsigned currentState);
unsigned Character_getCurrentState (const SCharacter *character);

void Character_setLastDirection (SCharacter *character, int value);
int Character_getLastDirection (const SCharacter *character);

void Character_destroy (SCharacter *character);

#endif