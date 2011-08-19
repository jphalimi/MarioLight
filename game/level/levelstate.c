//
//  levelstate.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <assert.h>
#include <stdlib.h>
#include "levelstate.h"
#include "level.h"

void LevelState_init (SLevelState *levelState, int initState) {
    assert(levelState != NULL);
    assert(initState < LEVELSTATE_NB);
    
    levelState->levelHandler = NULL;
}