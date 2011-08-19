//
//  level.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include "level.h"
#include "levelstate.h"

SLevel *Level_create (const char *fileName) {
    assert(fileName != NULL);
    unsigned i;
    SLevel *level = malloc(sizeof(*level));
    assert(level != NULL);
    memset(level, 0, sizeof(*level));
    
    for (i = 0; i < LEVELSTATE_NB; i++) {
        LevelState_init(level->states+i, i);
    }
    
    Level_setSourceFile (level, fileName);
	
	Level_parseSourceFile (level);
    
    return level;
}

void Level_setSourceFile (SLevel *level, const char *fileName) {
    assert(level != NULL);
	
	if (fileName == NULL) { /* User wants the string to be reset */
		level->sourceFile[0] = '\0';
	} else { /* Copy the input string in the config struct */
		strncpy(level->sourceFile, fileName, STRBUF_MAXLEN);
	}
}

char const *Level_getSourceFile (const SLevel *level) {
	assert(level != NULL);
	return level->sourceFile;
}

void Level_setCharactersNumbers (SLevel *level, int charactersNumber) {
	assert(level != NULL);
	level->charactersNumber = charactersNumber;
}

int Level_getCharactersNumbers (const SLevel *level) {
	assert(level != NULL);
	return level->charactersNumber;
}

void Level_switchState (SLevel *level, int newState) {
	assert(level != NULL);
	assert(newState < LEVELSTATE_NB);
	level->currentLevelState = newState;
}

int Level_getCurrentLevelState (const SLevel *level) {
	assert(level != NULL);
	return level->currentLevelState;
}

void Level_parseSourceFile (SLevel *level) {
	assert(level != NULL);
	// TODO : everything :)
}

void Level_destroy (SLevel *level) {
	assert(level != NULL);
	unsigned i;
	unsigned nbCharacters = level->charactersNumber;
	
	for (i = 0; i < nbCharacters; i++) {
		Character_destroy(level->characters[i]), level->characters[i] = NULL;
	}
	free(level->characters), level->characters = 0;
	
	free(level), level = NULL;
}