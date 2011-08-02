//
//  game.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_GAME
#define H_GAME

#include "config/config.h"
#include "rendering/rendering.h"

typedef struct sGame {
    SConfig *config;
    SRendering *rendering;
} SGame;

SGame *Game_create (void);
int Game_launch (SGame *game);
void Game_destroy (SGame *game);

#endif
