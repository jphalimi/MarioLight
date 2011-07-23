//
//  character_state.h
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 7/21/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef H_CHARACTERSTATE
#define H_CHARACTERSTATE

enum {  CHARACTER_ISSTANDING = 0,   /* Character is standing (no movement) */
		CHARACTER_ISWALKING,	/* Character is walking */
		CHARACTER_ISJUMPING,	/* Character is jumping */
		CHARACTER_ISCLIMBING,   /* Character is climbing */
		CHARACTER_ISSWIMMING,   /* Character is swimming */
		CHARACTER_ISCROUCHING,	/* Character is crouching */
		CHARACTER_STATES_NB		/* Character states number (max) */
};

typedef void (*characterState_fct)(void *);

typedef struct sCharacterState {
	characterState_fct updatePos;		/* callback function handling the position update */
	characterState_fct updateSprite;	/* callback function handling the sprite update */
	characterState_fct initState;		/* callback function handling to re-init of the state */
	unsigned *scheme;
	unsigned currentScheme;	/* in Sprite scheme, what is the current position of the character */
	unsigned schemeSize;		/* what is the scheme table size ? */
} SCharacterState;

void CharacterState_init (SCharacterState *characterState, int initState);
void CharacterState_free (SCharacterState *characterState);

characterState_fct CharacterState_getUpdatePosHandler (const SCharacterState *characterState);
characterState_fct CharacterState_getUpdateSpriteHandler (const SCharacterState *characterState);
characterState_fct CharacterState_getInitHandler (const SCharacterState *characterState);

void CharacterState_setCurrentScheme (SCharacterState *characterState, unsigned value);
unsigned CharacterState_getCurrentScheme (const SCharacterState *characterState);
unsigned CharacterState_getSchemeSize (const SCharacterState *characterState);

#endif
