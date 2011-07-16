//
//  time.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <SDL/SDL.h>
#include <stdint.h>
#include "time.h"

uint32_t Time_getTicks (void) {
    return SDL_GetTicks();
}