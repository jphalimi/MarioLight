//
// object.h
// MarioLight
//
// Created by Jean-Philippe HALIMI on 7/16/11.
// Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_OBJECT
#define H_OBJECT

#include <stdint.h>

#include "../config/config.h"
#include "../rendering/rendering.h"
#include "../input/input.h"
#include "object_state.h"

typedef struct sObject {
    char name[STRBUF_MAXLEN];
    SRenderingSurface **spriteTab;
    unsigned nbSprites;
    unsigned currentSprite;
    float spriteDuration;
    float originalSpriteDuration;
    float maxSpeed;
    float acceleration;
    uint32_t lastUpdateTime;
    float speedX, speedY;
    float x, y; /* Object position */
    SObjectState states[OBJECT_STATES_NB];
    unsigned currentState;
    int lastDirection;
    int isPlayable;
} SObject;

SObject *Object_create (const char *name, unsigned nb_sprites,
                              const char *sprites_folder, float sprite_duration,
                              float max_speed, float acceleration, float speedX, float speedY);
void Object_setName (SObject *object, const char *name);
char const *Object_getName (const SObject *object);

void Object_setSprites (SObject *object, unsigned nb_sprites,
                           const char *sprites_folder);

void Object_setX (SObject *object, float x);
float Object_getX (const SObject *object);

void Object_setY (SObject *object, float y);
float Object_getY (const SObject *object);

void Object_setNbSprites (SObject *object, unsigned nb_sprites);
unsigned Object_getNbSprites (const SObject *object);

void Object_setSprite (SObject *object, SRenderingSurface *surf, unsigned idX);
SRenderingSurface *Object_getSprite (const SObject *object, unsigned idX);

void Object_setCurrentSpriteNumber (SObject *object, unsigned current_sprite);
unsigned Object_getCurrentSpriteNumber (const SObject *object);

SRenderingSurface *Object_getCurrentSprite (const SObject *object);

void Object_setSpriteDuration (SObject *object, float spriteDuration);
float Object_getSpriteDuration (const SObject *object);

void Object_resetSpriteDuration (SObject *object);

void Object_setOriginalSpriteDuration (SObject *object, float spriteDuration);
float Object_getOriginalSpriteDuration (const SObject *object);

void Object_setMaxSpeed (SObject *object, float maxSpeed);
float Object_getMaxSpeed (const SObject *object);

void Object_setAcceleration (SObject *object, float acceleration);
float Object_getAcceleration (const SObject *object);

void Object_setLastUpdateTime (SObject *object, uint32_t time);
uint32_t Object_getLastUpdateTime (const SObject *object);

void Object_setSpeed (SObject *object, float speedX, float speedY);
float Object_getSpeedX (const SObject *object);
float Object_getSpeedY (const SObject *object);

void Object_update (SObject *object, SInput *input, uint32_t elapsedTime);
void Object_updateState (SObject *object, SInput *input);
void Object_updateDirection (SObject *object, SInput *input);
void Object_updatePosition (SObject *object, SInput *input, uint32_t elapsedTime);
void Object_updateSprite (SObject *object, SInput *input, uint32_t elapsedTime);

void Object_setCurrentState (SObject *object, unsigned currentState);
unsigned Object_getCurrentState (const SObject *object);

void Object_setUpdatePosHandler (SObject *object, int state, objectState_fct handler);
void Object_setUpdateSpriteHandler (SObject *object, int state, objectState_fct handler);

void Object_setScheme (SObject *object, int state, unsigned *scheme, unsigned schemeSize);

void Object_switchState (SObject *object, unsigned newState);

void Object_setLastDirection (SObject *object, int value);
int Object_getLastDirection (const SObject *object);

void Object_enablePlayable (SObject *object);
void Object_disablePlayable (SObject *object);
int Object_isPlayable (const SObject *object);

void Object_destroy (SObject *object);

#endif