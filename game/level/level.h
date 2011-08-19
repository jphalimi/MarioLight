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
#include "../config/config.h"
#include "levelstate.h"

typedef struct sLevel {
    char sourceFile[STRBUF_MAXLEN];
    SCharacter **characters;
    int charactersNumber;
    SLevelState states[LEVELSTATE_NB];
    int currentLevelState;
} SLevel;

SLevel *Level_create (const char *fileName);
void Level_setSourceFile (SLevel *level, const char *fileName);
char const *Level_getSourceFile (const SLevel *level);
void Level_setCharactersNumber (SLevel *level, int charactersNumber);
int Level_getCharactersNumber (const SLevel *level);
void Level_switchState (SLevel *level, int newState);
int Level_getCurrentLevelState (const SLevel *level);

void Level_parseSourceFile (SLevel *level);

void Level_destroy (SLevel *level);

#endif
