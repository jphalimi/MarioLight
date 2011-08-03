//
//  input.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_INPUT
#define H_INPUT

#include <stdio.h>

enum { INPUT_LEFT = 0, INPUT_RIGHT, INPUT_UP, INPUT_DOWN, INPUT_A, INPUT_B, INPUT_CLICK };

typedef struct sInput {
    SDL_Event e;
    int type;
} SInput;

void Input_init (SInput *input);
int Input_quitRequested (const SInput *input);
int Input_handleEvents (SInput *input);
int Input_isPushed (SInput *input, int type);
int Input_isClicked (SInput *input, int *x, int *y);

#endif
