//
//  game.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game.h"

SGame *Game_create (void) {
    SGame *game = malloc(sizeof(*game));
    assert(game != NULL);
    memset(game, 0, sizeof(*game));
    
    game->config = Config_create();
    game->rendering = Rendering_create(game->config);
    
    
    /* Todo before next commit :
        - Are all the characters in the same array ?
        - Do we have to use a LinkList instead ?
        - Think about the difference between the characters that are
    currently visible and/or handled by the physical engine and/or the display and those who
     aren't.
     */
}