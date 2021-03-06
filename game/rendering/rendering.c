//
//  rendering.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../config/config.h"
#include "../../toolkit/log.h"
#include "rendering.h"

SRendering *Rendering_create (const SConfig *config) {
    SRendering *rendering = malloc(sizeof(*rendering));
    assert(config != NULL);
    assert(rendering != NULL);
    memset(rendering, 0, sizeof(*rendering));
    
    /* Init SDL stuff */
    if (SDL_Init(Config_getSDLFlags(config)) != 0) {
        Log_output (1, "Error: Cannot initialize SDL : %s\n", SDL_GetError());
        exit (EXIT_FAILURE);
    }
    
    SDL_WM_SetCaption(Config_getGameName(config), NULL);
    
    rendering->screen = SDL_SetVideoMode( Config_getWindowWidth(config),
                               Config_getWindowHeight(config),
                               32,
                               SDL_HWSURFACE | SDL_DOUBLEBUF );
    
    if (rendering->screen == NULL) {
        Log_output (1, "Error: Cannot set SDL video mode : %s\n", SDL_GetError());
        exit (EXIT_FAILURE);
    }
    
    return rendering;
}

SRenderingSurface *Rendering_loadImage (const char *fileName, int alpha) {
    SDL_Surface *first, *optimized;
    
    assert(fileName != NULL);
    
    first = IMG_Load(fileName);
    if (first == NULL) {
        Log_output(1, "Error: Failed to load image \"%s\" : %s\n", fileName, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    if (alpha) {
        optimized = SDL_DisplayFormatAlpha(first);
    } else {
        optimized = SDL_DisplayFormat(first);
    }
    
    if (optimized == NULL) {
        Log_output(1, "Error: Failed to optimized image \"%s\" blitting : %s\n", fileName,
                   SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    SDL_FreeSurface(first);
    return optimized;
}

void Rendering_freeSurface (SRenderingSurface *surf) {
    SDL_FreeSurface(surf);
}

void Rendering_addSurface (SRendering *rendering, int idX, int idY,
                           SRenderingSurface *surf) {
    SDL_Rect rect;
    assert(rendering != NULL);
    assert(rendering->screen != NULL);
    assert(surf != NULL);
    
    rect.x = idX;
    rect.y = rendering->screen->h - surf->h - idY;
    
    if (SDL_BlitSurface(surf, NULL, rendering->screen, &rect) < 0) {
        Log_output(1, "Error: Cannot blit surface to screen : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Rendering_render (SRendering *rendering) {
    if (SDL_Flip(rendering->screen) != 0) {
        Log_output(1, "Error: Cannot flip screen : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Rendering_resetScreen (void) {
    if (SDL_FillRect(SDL_GetVideoSurface(), NULL, 0) != 0) {
        Log_output(1, "Error: Cannot reset screen : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void Rendering_destroy (SRendering *rendering) {
    SDL_Quit();
    free(rendering), rendering = NULL;
}