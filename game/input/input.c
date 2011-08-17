//
//  input.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <SDL/SDL.h>
#include "input.h"

void Input_init (SInput *input) {
    assert(input != NULL);
    memset(input, 0, sizeof(*input));
}

int Input_quitRequested (const SInput *input) {
    assert(input != NULL);
    
    return (input->e.key.keysym.sym == SDLK_ESCAPE)
            || (input->e.type == SDL_QUIT);
}

int Input_handleEvents (SInput *input) {
    assert(input != NULL);
    unsigned i = 0;
    
    while (SDL_PollEvent(&(input->e))) {
        // If this is a keyboard press event
        if (input->e.type == SDL_KEYDOWN) {
            switch (input->e.key.keysym.sym) {
                case SDLK_LEFT:		input->isTriggered[INPUT_LEFT] = 1; break;
                case SDLK_RIGHT:	input->isTriggered[INPUT_RIGHT] = 1; break;
                case SDLK_DOWN:		input->isTriggered[INPUT_DOWN] = 1; break;
                case SDLK_UP:       input->isTriggered[INPUT_UP] = 1; break;
                case SDLK_w:        input->isTriggered[INPUT_A] = 1; break;
                case SDLK_x:        input->isTriggered[INPUT_B] = 1; break;
				default: break;
            }
        }
		// If this is a keyboard release event
        if (input->e.type == SDL_KEYUP) {
            switch (input->e.key.keysym.sym) {
                case SDLK_LEFT:		input->isTriggered[INPUT_LEFT] = 0; break;
                case SDLK_RIGHT:	input->isTriggered[INPUT_RIGHT] = 0; break;
                case SDLK_DOWN:		input->isTriggered[INPUT_DOWN] = 0; break;
                case SDLK_UP:       input->isTriggered[INPUT_UP] = 0; break;
                case SDLK_w:        input->isTriggered[INPUT_A] = 0; break;
                case SDLK_x:        input->isTriggered[INPUT_B] = 0; break;
				default: break;
            }
        }
        i++;
    }
    
    return i;
}

int Input_isPushed (SInput *input, int type) {
    assert(input != NULL);
    assert(type < INPUT_EVENT_LENGTH);
    return input->isTriggered[type];
}

int Input_isClicked (SInput *input, int *x, int *y) {
    assert(input != NULL);
    
    if (input->e.type != SDL_MOUSEBUTTONUP) {
        return 0;
    }
    
    if (x != NULL) {
        *x = input->e.button.x;
    }
    
    if (y != NULL) {
        *y = input->e.button.y;
    }
    
    return 1;
}