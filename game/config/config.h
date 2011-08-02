//
//  config.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CONFIG
#define H_CONFIG

#include <stdint.h>
#include <SDL/SDL.h>

/* Defines vars */
#define STRBUF_MAXLEN 512

typedef struct sConfig {
    unsigned windowWidth;
    unsigned windowHeight;
    char gameName[STRBUF_MAXLEN];
    uint32_t sdlFlags;
} SConfig;

SConfig *Config_create (void);
void Config_destroy (SConfig *config);

void Config_setWindowWidth (SConfig *config, unsigned value);
unsigned Config_getWindowWidth (const SConfig *config);

void Config_setWindowHeight (SConfig *config, unsigned value);
unsigned Config_getWindowHeight (const SConfig *config);

void Config_setGameName (SConfig *config, const char *name);
char const *Config_getGameName (const SConfig *config);

void Config_setSDLFlags (SConfig *config, uint32_t flags);
uint32_t Config_getSDLFlags (const SConfig *config);

#endif