//
//  rendering.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_RENDERING
#define H_RENDERING

#include <SDL/SDL.h>
#include "../config/config.h"

/* Engine library overlay */
typedef SDL_Surface SRenderingSurface;

typedef struct sRendering {
    SRenderingSurface *screen;
} SRendering;

SRendering *Rendering_create (const SConfig *config);
SRenderingSurface *Rendering_loadImage (const char *fileName);
void Rendering_addSurface (SRendering *rendering, int idX, int idY, SRenderingSurface *surf);
void Rendering_render (SRendering *rendering);
void Rendering_resetScreen (void);
void Rendering_destroy (SRendering *rendering);

#endif