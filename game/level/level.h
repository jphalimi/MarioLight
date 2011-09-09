//
//  level.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_LEVEL
#define H_LEVEL

#include "../character/character.h"
#include "../object/object.h"
#include "../config/config.h"
#include "levelstate.h"

typedef struct sLevel {
    SCharacter **characters;
    SObject **objects;
    int charactersNumber;
    int objectsNumber;
    SLevelState states[LEVELSTATE_NB];
    int currentLevelState;
} SLevel;

SLevel *Level_create (const char *fileName);
void Level_setCharactersNumber (SLevel *level, int charactersNumber);
int Level_getCharactersNumber (const SLevel *level);
void Level_setObjectsNumber (SLevel *level, int objectsNumber);
int Level_getObjectsNumber (const SLevel *level);
void Level_switchState (SLevel *level, int newState);
int Level_getCurrentLevelState (const SLevel *level);

void Level_destroy (SLevel *level);

#endif
