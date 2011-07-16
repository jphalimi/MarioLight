//
//  character.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CHARACTER
#define H_CHARACTER

#include "../config/config.h"
#include "../rendering/rendering.h"

typedef struct sCharacter {
    char name[STRBUF_MAXLEN];
    SRenderingSurface **spriteTab;
    unsigned nbSprites;
    unsigned currentSprite;
    float spriteDuration;
    float maxSpeed;
    float acceleration;
} SCharacter;

SCharacter *Character_create (const char *name, unsigned nb_sprites,
                              const char *sprites_folder, float sprite_duration,
                              float max_speed, float acceleration);
void Character_setName (SCharacter *character, const char *name);
char const *Character_getName (const SCharacter *character);

void Character_setSprites (SCharacter *character, unsigned nb_sprites,
                           const char *sprites_folder);

void Character_setNbSprites (SCharacter *character, unsigned nb_sprites);
unsigned Character_getNbSprites (const SCharacter *character);

void Character_setSprite (SCharacter *character, SRenderingSurface *surf, unsigned idX);
SRenderingSurface *Character_getSprite (const SCharacter *character, unsigned idX);

void Character_setCurrentSprite (SCharacter *character, unsigned current_sprite);
unsigned Character_getCurrentSprite (const SCharacter *character);

void Character_setSpriteDuration (SCharacter *character, float spriteDuraton);
float Character_getSpriteDuration (const SCharacter *character);

void Character_setMaxSpeed (SCharacter *character, float maxSpeed);
float Character_getMaxSpeed (const SCharacter *character);

void Character_setAcceleration (SCharacter *character, float acceleration);
float Character_getAcceleration (const SCharacter *character);

void Character_destroy (SCharacter *character);

#endif