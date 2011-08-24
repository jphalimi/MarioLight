//
//  characters.c
//  MarioLight
//
//  Created by Jean-Philippe HALIMI on 8/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "../../character/character.h"
#include "../../character/character_state.h"
#include "states_handlers.h"
#include "characters.h"

SCharacter *Mario_create (void) {
    //Character_create(<#const char *name#>, <#unsigned int nb_sprites#>, <#const char *sprites_folder#>,<#uint32_t sprite_duration#>, <#float max_speed#>, <#float acceleration#>, <#float speed#>)
    SCharacter *mario = Character_create("Mario", 13, "game/images/mario", 130, 4.27, 0.3, 0.0, 0.0);
    /* Walking handling */
    {
        unsigned scheme[] = {1, 3};
        Character_setScheme (mario, CHARACTER_ISWALKING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdatePosHandler   (mario, CHARACTER_ISWALKING, CS_playerWalkingPos);
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISWALKING, CS_playerWalkingSprite);
    }
    /* Jumping handling */
    {
        unsigned scheme[] = {4};
        Character_setScheme (mario, CHARACTER_ISJUMPING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdatePosHandler   (mario, CHARACTER_ISJUMPING, CS_playerJumpingPos);
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISJUMPING, CS_playerJumpingSprite);
    }
    /* Standing handling */
    {
        unsigned scheme[] = {0};
        Character_setScheme (mario, CHARACTER_ISSTANDING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISSTANDING, CS_standingSprite);
    }
    Character_enablePlayable(mario);
    
    return mario;
}

SCharacter *Koopa_create (void) {
    //Character_create(<#const char *name#>, <#unsigned int nb_sprites#>, <#const char *sprites_folder#>,<#uint32_t sprite_duration#>, <#float max_speed#>, <#float acceleration#>, <#float speed#>X, <#float speed#>Y)
    SCharacter *character = Character_create("Koopa", 4, "game/images/koopa", 130, 4.27, 0.3, -1, 0.0);
    /* Walking handling */
    {
        unsigned scheme[] = {2,3};
        Character_setScheme (character, CHARACTER_ISWALKING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdatePosHandler   (character, CHARACTER_ISWALKING, CS_characterWalkingPos);
        Character_setUpdateSpriteHandler(character, CHARACTER_ISWALKING, CS_characterWalkingSprite);
    }
    Character_setLastDirection(character, DIR_LEFT);
    Character_setCurrentState(character, CHARACTER_ISWALKING);
    Character_setX(character, 500);
    
    return character;
}