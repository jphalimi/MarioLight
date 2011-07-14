//
//  config.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/14/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <SDL/SDL.h>
#include "config.h"

SConfig *Config_create (void) {
    SConfig *config = malloc(sizeof(*config));
    assert(config != NULL);
    
    Config_setWindowWidth(config, 640);
    Config_setWindowHeight(config, 480);
    Config_setGameName(config, "MarioLight");
    Config_setSDLFlags(config, SDL_INIT_EVERYTHING);
    
    return config;
}

void Config_destroy (SConfig *config) {
    free(config), config = NULL;
}

void Config_setWindowWidth (SConfig *config, unsigned value) {
    assert(config != NULL);
    config->windowWidth = value;
}

unsigned Config_getWindowWidth (const SConfig *config) {
    assert(config != NULL);
    return config->windowWidth;
}


void Config_setWindowHeight (SConfig *config, unsigned value) {
    assert(config != NULL);
    config->windowHeight = value;
}

unsigned Config_getWindowHeight (const SConfig *config) {
    assert(config != NULL);
    return config->windowHeight;
}

void Config_setGameName (SConfig *config, const char *gameName) {
    assert(config != NULL);
    
    if (gameName == NULL) { /* User wants the string to be reset */
        config->gameName[0] = '\0';
    } else { /* Copy the input string in the config struct */
        strncpy(config->gameName, gameName, STRBUF_MAXLEN);
    }
}

char const *Config_getGameName (const SConfig *config) {
    assert(config != NULL);
    return config->gameName;
}

void Config_setSDLFlags (SConfig *config, uint32_t flags) {
    assert(config != NULL);
    config->sdlFlags = flags;
}

uint32_t Config_getSDLFlags (const SConfig *config) {
    assert(config != NULL);
    return config->sdlFlags;
}

