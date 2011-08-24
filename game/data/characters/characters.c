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
#include "../../character/states_handlers.h"
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
    
    return mario;
}

#if 0
SCharacter *Koopa_create (void) {
    //Character_create(<#const char *name#>, <#unsigned int nb_sprites#>, <#const char *sprites_folder#>,<#uint32_t sprite_duration#>, <#float max_speed#>, <#float acceleration#>, <#float speed#>)
    SCharacter *mario = Character_create("Mario", 13, "game/images/mario", 130, 5.0, 0.3, 0.0, 0.0);
    /* Walking handling */
    {
        unsigned scheme[] = {1, 3};
        Character_setScheme (mario, CHARACTER_ISWALKING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdatePosHandler   (mario, CHARACTER_ISWALKING, CS_isWalking_Pos);
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISWALKING, CS_isWalking_Sprite);
    }
    /* Jumping handling */
    {
        unsigned scheme[] = {4};
        Character_setScheme (mario, CHARACTER_ISJUMPING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdatePosHandler   (mario, CHARACTER_ISJUMPING, CS_isJumping_Pos);
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISJUMPING, CS_isJumping_Sprite);
    }
    /* Standing handling */
    {
        unsigned scheme[] = {0};
        Character_setScheme (mario, CHARACTER_ISSTANDING, scheme, sizeof(scheme) / sizeof(*scheme));
        Character_setUpdateSpriteHandler(mario, CHARACTER_ISSTANDING, CS_isStanding_Sprite);
    }
    
    return mario;
}
#endif