//
//  levelstate.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_LEVELSTATE
#define H_LEVELSTATE

struct sLevel;

enum {
    LEVEL_PAUSE,
    LEVEL_PLAY,
    LEVEL_LOOSE,
    LEVEL_WIN,
    LEVELSTATE_NB
};

typedef void (*levelHandler_fct) (struct sLevel *level);

typedef struct sLevelState {
    levelHandler_fct *levelHandler;
} SLevelState;

void LevelState_init (SLevelState *levelState, int initState);

#endif
