//
//  character.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include "character.h"
#include "../../toolkit/log.h"
#include "../time/time.h"

SCharacter *Character_create (const char *name, unsigned nb_sprites,
                              const char *sprites_folder, uint32_t sprite_duration,
                              float max_speed, float acceleration, float speed) {
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
    Character_setMaxSpeed(character, max_speed);
    Character_setAcceleration(character, acceleration);
    Character_setLastUpdateTime(character, Time_getTicks());
    Character_setSpeed(character, speed);
    Character_setCurrentSpriteNumber(character, 0);
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
        character->spriteTab[i] = Rendering_loadImage(spriteFileNameBuf);
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

void Character_setSpriteDuration (SCharacter *character, uint32_t duration) {
    assert(character != NULL);
    character->spriteDuration = duration;
}

uint32_t Character_getSpriteDuration (const SCharacter *character) {
    assert(character != NULL);
    return character->spriteDuration;
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

void Character_setSpeed (SCharacter *character, float speed) {
    assert(character != NULL);
    character->speed = speed;
}

float Character_getSpeed (const SCharacter *character) {
    assert(character != NULL);
    return character->speed;
}

void Character_updateSprite (SCharacter *character) {
    assert(character != NULL);
    uint32_t time_diff = Time_getTicks() - character->lastUpdateTime;
    
    if (character->speed < character->maxSpeed) {
        character->speed += character->acceleration;
        Log_output(1, "Info: CharSpeed: %f, CharAccel: %f, CharX: %f, CharY: %f\n",
                   character->speed, character->acceleration, character->x,
                   character->y);
        //character->spriteDuration -= character->spriteDuration;
    }
    
    character->x += character->speed;
    character->x = (int)(character->x)%(SDL_GetVideoSurface()->w);
    
    if (time_diff > character->spriteDuration) {
        character->currentSprite++;
        character->currentSprite %= character->nbSprites;
        character->lastUpdateTime = Time_getTicks();
    }
}

void Character_destroy (SCharacter *character) {
    unsigned i;
    
    for (i = 0; i < character->nbSprites; ++i) {
        Rendering_freeSurface(character->spriteTab[i]);
    }
    free(character->spriteTab), character->spriteTab = NULL;
    free(character), character = NULL;
}