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
        i++;
    }
    
    return i;
}

int Input_isPushed (SInput *input, int type) {
    assert(input != NULL);
    
    if (input->e.type == SDL_KEYDOWN) {
        switch (type) {
            case INPUT_LEFT:
                return input->e.key.keysym.sym == SDLK_LEFT;
                break;
            case INPUT_RIGHT:
                return input->e.key.keysym.sym == SDLK_RIGHT;
                break;
            case INPUT_DOWN:
                return input->e.key.keysym.sym == SDLK_DOWN;
                break;
            case INPUT_UP:
                return input->e.key.keysym.sym == SDLK_UP;
                break;
            case INPUT_A:
                return input->e.key.keysym.sym == SDLK_w;
                break;
            case INPUT_B:
                return input->e.key.keysym.sym == SDLK_x;
                break;
        }
    }
    
    return 0;
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